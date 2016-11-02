using namespace std;
#define EPSILON 1e-12
#define dbl float
#define ENABLE_CUDA

#include <cmath>
#include <algorithm>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/time.h>

//#include "cuda.h"
#include "cuda_runtime.h"
#include "vector_types.h"
#include "vector_functions.h"

#include "box.h"

#include "gpubox.h"
#include "gpuarray.h"
#include "gpucell.cuh"
#include "gpucell.h"

#include "DelaunayMD.cuh"
#include "DelaunayMD.h"



void DelaunayMD::randomizePositions(float boxx, float boxy)
    {
    int randmax = 100000000;
    ArrayHandle<float2> h_points(points,access_location::host, access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        float x =EPSILON+boxx/(dbl)(randmax+1)* (dbl)(rand()%randmax);
        float y =EPSILON+boxy/(dbl)(randmax+1)* (dbl)(rand()%randmax);
        h_points.data[ii].x=x;
        h_points.data[ii].y=y;
        printf("%i; {%f,%f}\n",ii,x,y);
        };
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("randomizePos GPUassert: %s \n", cudaGetErrorString(code));
    };

void DelaunayMD::resetDelLocPoints()
    {
    ArrayHandle<float2> h_points(points,access_location::host, access_mode::read);
    for (int ii = 0; ii < N; ++ii)
        {
        pts[ii].x=h_points.data[ii].x;
        pts[ii].y=h_points.data[ii].y;
        };
    delLoc.setPoints(pts);
    delLoc.initialize(cellsize);

    };

void DelaunayMD::initialize(int n)
    {
    //set cellsize to about unity
    cellsize = 1.25;

    //set particle number and box
    N = n;
    float boxsize = sqrt(N);
    Box.setSquare(boxsize,boxsize);
    printf("Boxsize is %f\n",boxsize);

    //set circumcenter array size
    circumcenters.resize(6*N);

    //set particle positions (randomly)
    points.resize(N);
    pts.resize(N);
    repair.resize(N);
    randomizePositions(boxsize,boxsize);

    //cell list initialization
    celllist.setNp(N);
    celllist.setBox(Box);
    celllist.setGridSize(cellsize);

    //DelaunayLoc initialization
    box Bx(boxsize,boxsize);
    delLoc.setBox(Bx);
    resetDelLocPoints();

    //make a full triangulation
    fullTriangulation();
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("delMD initialization GPUassert: %s \n", cudaGetErrorString(code));
    };

void DelaunayMD::updateCellList()
    {
    celllist.setNp(N);
    celllist.setBox(Box);
    celllist.setGridSize(cellsize);

    cudaError_t code1 = cudaGetLastError();
    if(code1!=cudaSuccess)
        printf("cell list preliminary computation GPUassert: %s \n", cudaGetErrorString(code1));
    //celllist.computeGPU(points);
    celllist.compute(points);
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("cell list computation GPUassert: %s \n", cudaGetErrorString(code));
    };

void DelaunayMD::reportCellList()
    {
    ArrayHandle<unsigned int> h_cell_sizes(celllist.cell_sizes,access_location::host,access_mode::read);
    ArrayHandle<int> h_idx(celllist.idxs,access_location::host,access_mode::read);
    int numCells = celllist.getXsize()*celllist.getYsize();
    for (int nn = 0; nn < numCells; ++nn)
        {
        cout << "cell " <<nn <<":     ";
        for (int offset = 0; offset < h_cell_sizes.data[nn]; ++offset)
            {
            int clpos = celllist.cell_list_indexer(offset,nn);
            cout << h_idx.data[clpos] << "   ";
            };
        cout << endl;
        };
    };

void DelaunayMD::reportPos(int i)
    {
    ArrayHandle<float2> hp(points,access_location::host,access_mode::read);
    printf("particle %i\t{%f,%f}\n",i,hp.data[i].x,hp.data[i].y);
    };

void DelaunayMD::movePoints(GPUArray<float2> &displacements)
    {
    ArrayHandle<float2> d_p(points,access_location::device,access_mode::readwrite);
    ArrayHandle<float2> d_d(displacements,access_location::device,access_mode::readwrite);
    gpu_move_particles(d_p.data,d_d.data,N,Box);
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("movePoints GPUassert: %s \n", cudaGetErrorString(code));
    };

void DelaunayMD::fullTriangulation()
    {
    cout << "Resetting complete triangulation" << endl;
    //get neighbors of each cell in CW order
    neigh_num.resize(N);

    ArrayHandle<int> neighnum(neigh_num,access_location::host,access_mode::overwrite);

    ArrayHandle<int> h_repair(repair,access_location::host,access_mode::overwrite);

    vector< vector<int> > allneighs(N);
    int nmax = 0;
    for(int nn = 0; nn < N; ++nn)
        {
        vector<int> neighTemp;
        delLoc.getNeighbors(nn,neighTemp);
        allneighs[nn]=neighTemp;
        neighnum.data[nn] = neighTemp.size();
        if (neighTemp.size() > nmax) nmax= neighTemp.size();
        h_repair.data[nn]=0;
        };
    neighMax = nmax; cout << "new Nmax = " << nmax << endl;
    neighs.resize(neighMax*N);

    //store data in gpuarray
    n_idx = Index2D(neighMax,N);
    ArrayHandle<int> ns(neighs,access_location::host,access_mode::overwrite);

    for (int nn = 0; nn < N; ++nn)
        {
        int imax = neighnum.data[nn];
        for (int ii = 0; ii < imax; ++ii)
            {
            int idxpos = n_idx(ii,nn);
            ns.data[idxpos] = allneighs[nn][ii];
//printf("particle %i (%i,%i)\n",nn,idxpos,allneighs[nn][ii]);
            };
        };

    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("FullTriangulation  GPUassert: %s \n", cudaGetErrorString(code));


    getCircumcenterIndices();
    };

void DelaunayMD::getCircumcenterIndices()
    {
    ArrayHandle<int> neighnum(neigh_num,access_location::host,access_mode::read);
    ArrayHandle<int> ns(neighs,access_location::host,access_mode::read);
    ArrayHandle<int> h_ccs(circumcenters,access_location::host,access_mode::overwrite);

    int cidx = 0;
    for (int nn = 0; nn < N; ++nn)
        {
        int nmax = neighnum.data[nn];
        for (int jj = 0; jj < nmax; ++jj)
            {
            int n1 = ns.data[n_idx(jj,nn)];
            int ne2 = jj + 1;
            if (jj == nmax-1)  ne2=0;
            int n2 = ns.data[n_idx(ne2,nn)];

            if (nn < n1 && nn < n2)
                {
                h_ccs.data[3*cidx] = nn;
                h_ccs.data[3*cidx+1] = n1;
                h_ccs.data[3*cidx+2] = n2;
                cidx+=1;
                };
            };

        };
    cout << cidx << " total circumcenters" << endl;
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("getCCIndices GPUassert: %s \n", cudaGetErrorString(code));
    };


void DelaunayMD::repairTriangulation(vector<int> &fixlist)
    {
    };

void DelaunayMD::testTriangulation()
    {
    //first, update the cell list
    updateCellList();

    //access data handles
    ArrayHandle<float2> d_pt(points,access_location::device,access_mode::readwrite);

    ArrayHandle<unsigned int> d_cell_sizes(celllist.cell_sizes,access_location::device,access_mode::read);
    ArrayHandle<int> d_c_idx(celllist.idxs,access_location::device,access_mode::read);

    ArrayHandle<int> d_repair(repair,access_location::device,access_mode::readwrite);
    ArrayHandle<int> d_ccs(circumcenters,access_location::device,access_mode::read);

    int NumCircumCenters = N*2;
    gpu_test_circumcenters(d_repair.data,
                           d_ccs.data,
                           NumCircumCenters,
                           d_pt.data,
                           d_cell_sizes.data,
                           d_c_idx.data,
                           N,
                           celllist.getXsize(),
                           celllist.getYsize(),
                           celllist.getBoxsize(),
                           Box,
                           celllist.cell_indexer,
                           celllist.cell_list_indexer
                           );
    };


void DelaunayMD::testAndRepairTriangulation()
    {

    testTriangulation();
    vector<int> NeedsFixing;
    ArrayHandle<int> h_repair(repair,access_location::host,access_mode::readwrite);
    cudaError_t code = cudaGetLastError();
    if(code!=cudaSuccess)
        printf("testAndRepair preliminary GPUassert: %s \n", cudaGetErrorString(code));
    for (int nn = 0; nn < N; ++nn)
        {
        if (h_repair.data[nn] == 1)
            {
            cout << nn << " needs fixin'" << endl;
            h_repair.data[nn]=0;
            };

        };


    repairTriangulation(NeedsFixing);
    };


