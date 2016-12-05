using namespace std;

//definitions needed for DelaunayLoc, and all GPU functions, respectively

#define EPSILON 1e-16
#define ENABLE_CUDA

#include "spv2d.h"
#include "spv2d.cuh"
#include "cuda_profiler_api.h"

SPV2D::SPV2D(int n)
    {
    printf("Initializing %i cells with random positions in a square box\n",n);
    Initialize(n);
    };

SPV2D::SPV2D(int n,Dscalar A0, Dscalar P0)
    {
    printf("Initializing %i cells with random positions in a square box\n",n);
    Initialize(n);
    setCellPreferencesUniform(A0,P0);
    setCellTypeUniform(0);
    };

void SPV2D::Initialize(int n)
    {
    N=n;
    gamma = 0.;
    useTension = false;
    particleExclusions=false;
    Timestep = 0;
    triangletiming = 0.0; forcetiming = 0.0;
    setDeltaT(0.01);
    initialize(n);
    setModuliUniform(1.0,1.0);
    sortPeriod = 1000;


    setv0Dr(0.05,1.0);
    forces.resize(n);
    external_forces.resize(n);
    AreaPeri.resize(n);

    cellDirectors.resize(n);
    cellDirectors_initial.resize(n);
    displacements.resize(n);

    vector<int> baseEx(n,0);
    setExclusions(baseEx);
    particleExclusions=false;


    ArrayHandle<Dscalar> h_cd(cellDirectors,access_location::host, access_mode::overwrite);
    ArrayHandle<Dscalar> h_cdi(cellDirectors_initial,access_location::host, access_mode::overwrite);

    int randmax = 100000000;
    for (int ii = 0; ii < N; ++ii)
        {
        Dscalar theta = 2.0*PI/(Dscalar)(randmax)* (Dscalar)(rand()%randmax);
        h_cd.data[ii] = theta;
        h_cdi.data[ii] = theta;
        };
    //setCurandStates(n);
    allDelSets();
    };

void SPV2D::spatialSorting()
    {
    spatiallySortPoints();
    globalTriangulationCGAL();
    allDelSets();

    ArrayHandle<Dscalar2> h_mot(Motility,access_location::host,access_mode::readwrite);
    ArrayHandle<Dscalar2> h_mod(Moduli,access_location::host,access_mode::readwrite);
    ArrayHandle<Dscalar2> h_pref(AreaPeriPreferences,access_location::host,access_mode::readwrite);
    ArrayHandle<Dscalar> h_cd(cellDirectors,access_location::host,access_mode::readwrite);
    ArrayHandle<int> h_ct(CellType,access_location::host,access_mode::readwrite);
    ArrayHandle<int> h_ex(exclusions,access_location::host,access_mode::readwrite);


    //motility
    GPUArray<Dscalar2> sd2(N);
    {
    ArrayHandle<Dscalar2> hsd2(sd2,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        hsd2.data[ii].x = h_mot.data[idxToTag[ii]].x;
        hsd2.data[ii].y = h_mot.data[idxToTag[ii]].y;
        };
    };
    Motility = sd2;

    //moduli
    {
    ArrayHandle<Dscalar2> hsd2(sd2,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        if (idxToTag[ii] >=N) printf("Asda");
        hsd2.data[ii].x = h_mod.data[idxToTag[ii]].x;
        hsd2.data[ii].y = h_mod.data[idxToTag[ii]].y;
        };
    };
    Moduli = sd2;

    //preference
    {
    ArrayHandle<Dscalar2> hsd2(sd2,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        hsd2.data[ii].x = h_pref.data[idxToTag[ii]].x;
        hsd2.data[ii].y = h_pref.data[idxToTag[ii]].y;
        };
    };
    AreaPeriPreferences = sd2;


    //director
    GPUArray<Dscalar> sd(N);
    {
    ArrayHandle<Dscalar> hss(sd,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        hss.data[ii] = h_cd.data[idxToTag[ii]];
    };
    cellDirectors = sd;

    //exclusions
    GPUArray<int> swap(N);
    {
    ArrayHandle<int> ss(swap,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        ss.data[ii] = h_ex.data[idxToTag[ii]];
    };
    exclusions = swap;

    //cellType
    {
    ArrayHandle<int> ss(swap,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        ss.data[ii] = h_ct.data[idxToTag[ii]];
    };
    CellType = swap;


    };


void SPV2D::allDelSets()
    {
    delSets.resize(neighMax*N);
    delOther.resize(neighMax*N);
    forceSets.resize(neighMax*N);
    for (int ii = 0; ii < N; ++ii)
        getDelSets(ii);
    };

void SPV2D::setModuliUniform(Dscalar KA, Dscalar KP)
    {
    Moduli.resize(N);
    ArrayHandle<Dscalar2> h_m(Moduli,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        h_m.data[ii].x = KA;
        h_m.data[ii].y = KP;
        };
    };


void SPV2D::setCellPreferencesUniform(Dscalar A0, Dscalar P0)
    {
    AreaPeriPreferences.resize(N);
    ArrayHandle<Dscalar2> h_p(AreaPeriPreferences,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        h_p.data[ii].x = A0;
        h_p.data[ii].y = P0;
        };
    };

void SPV2D::setCellTypeUniform(int i)
    {
    CellType.resize(N);
    ArrayHandle<int> h_ct(CellType,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        h_ct.data[ii] = i;
        };
    };

void SPV2D::setCellType(vector<int> &types)
    {
    CellType.resize(N);
    ArrayHandle<int> h_ct(CellType,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        h_ct.data[ii] = types[ii];
        };
    };

void SPV2D::setCellTypeEllipse(Dscalar frac, Dscalar aspectRatio)
    {
    Dscalar x11,x12,x21,x22;
    Box.getBoxDims(x11,x12,x21,x22);
    Dscalar xc = x11*0.5;
    Dscalar yc = x22*0.5;

    Dscalar ry = sqrt(x11*x22*frac/(3.14159*aspectRatio));
    Dscalar rx = aspectRatio*ry;

    CellType.resize(N);
    ArrayHandle<int> h_ct(CellType,access_location::host,access_mode::overwrite);
    ArrayHandle<Dscalar2> h_p(points,access_location::host,access_mode::read);

    for (int ii = 0; ii < N; ++ii)
        {
        Dscalar px = h_p.data[ii].x;
        Dscalar py = h_p.data[ii].y;
        Dscalar test = (px-xc)*(px-xc)/(rx*rx) + (py-yc)*(py-yc)/(ry*ry);
        if (test <=1.0)
            h_ct.data[ii] = 0;
        else
            h_ct.data[ii] = 1;
        };
    };

void SPV2D::setv0Dr(Dscalar v0new,Dscalar drnew)
    {
    Motility.resize(N);
    if (true)
        {
        ArrayHandle<Dscalar2> h_mot(Motility,access_location::host,access_mode::overwrite);
        for (int ii = 0; ii < N; ++ii)
            {
            h_mot.data[ii].x = v0new;
            h_mot.data[ii].y = drnew;
            };
        };
    };
void SPV2D::setCellMotility(vector<Dscalar> &v0s,vector<Dscalar> &drs)
    {
    Motility.resize(N);
    ArrayHandle<Dscalar2> h_mot(Motility,access_location::host,access_mode::overwrite);
    for (int ii = 0; ii < N; ++ii)
        {
        h_mot.data[ii].x = v0s[ii];
        h_mot.data[ii].y = drs[ii];
        };
    };


void SPV2D::setExclusions(vector<int> &exes)
    {
    particleExclusions=true;
    external_forces.resize(N);
    exclusions.resize(N);
    ArrayHandle<Dscalar2> h_mot(Motility,access_location::host,access_mode::readwrite);
    ArrayHandle<int> h_ex(exclusions,access_location::host,access_mode::overwrite);

    for (int ii = 0; ii < N; ++ii)
        {
        h_ex.data[ii] = 0;
        if( exes[ii] != 0)
            {
            //set v0 to zero and Dr to zero
            h_mot.data[ii].x = 0.0;
            h_mot.data[ii].y = 0.0;
            h_ex.data[ii] = 1;
            };
        };
    };
/*
void SPV2D::setCurandStates(int i)
    {
    gpu_init_curand(devStates,i,N);

    };
*/

/////////////////
//Utility
/////////////////

void SPV2D::getDelSets(int i)
    {
    ArrayHandle<int> neighnum(neigh_num,access_location::host,access_mode::read);
    ArrayHandle<int> ns(neighs,access_location::host,access_mode::read);
    ArrayHandle<int4> ds(delSets,access_location::host,access_mode::readwrite);
    ArrayHandle<int> dother(delOther,access_location::host,access_mode::readwrite);

    int iNeighs = neighnum.data[i];
    int nm2,nm1,n1,n2;
    nm2 = ns.data[n_idx(iNeighs-3,i)];
    nm1 = ns.data[n_idx(iNeighs-2,i)];
    n1 = ns.data[n_idx(iNeighs-1,i)];

    for (int nn = 0; nn < iNeighs; ++nn)
        {
        n2 = ns.data[n_idx(nn,i)];
        int nextNeighs = neighnum.data[n1];
        for (int nn2 = 0; nn2 < nextNeighs; ++nn2)
            {
            int testPoint = ns.data[n_idx(nn2,n1)];
            if(testPoint == nm1)
                {
                dother.data[n_idx(nn,i)] = ns.data[n_idx((nn2+1)%nextNeighs,n1)];
                break;
                };
            };
        ds.data[n_idx(nn,i)].x= nm2;
        ds.data[n_idx(nn,i)].y= nm1;
        ds.data[n_idx(nn,i)].z= n1;
        ds.data[n_idx(nn,i)].w= n2;

        nm2=nm1;
        nm1=n1;
        n1=n2;
        };
/*
    for (int nn = 0; nn < iNeighs; ++nn)
        {
        printf("%i  %i   %i   %i   ;  %i \n",ds.data[n_idx(nn,i)].x,ds.data[n_idx(nn,i)].y, ds.data[n_idx(nn,i)].z,ds.data[n_idx(nn,i)].w,dother.data[n_idx(nn,i)]);

        };
*/
    };


/////////////////
//Dynamics
/////////////////

void SPV2D::performTimestep()
    {
    Timestep += 1;
    if(GPUcompute)
        performTimestepGPU();
    else
        performTimestepCPU();

    if (Timestep % sortPeriod == 0 && Timestep != 0) spatialSorting();
    };

void SPV2D::DisplacePointsAndRotate()
    {

    ArrayHandle<Dscalar2> d_p(points,access_location::device,access_mode::readwrite);
    ArrayHandle<Dscalar2> d_f(forces,access_location::device,access_mode::read);
    ArrayHandle<Dscalar> d_cd(cellDirectors,access_location::device,access_mode::readwrite);
    ArrayHandle<Dscalar2> d_motility(Motility,access_location::device,access_mode::read);

    gpu_displace_and_rotate(d_p.data,
                            d_f.data,
                            d_cd.data,
                            d_motility.data,
                            N,
                            deltaT,
                            Timestep,
//                            devStates,
                            Box);

    };

void SPV2D::centerCells()
    {
    ArrayHandle<Dscalar2> h_p(points,access_location::host,access_mode::read);
    Dscalar x11,x12,x21,x22;
    Box.getBoxDims(x11,x12,x21,x22);
    Dscalar xcm, ycm;
    xcm = 0.0; ycm = 0,0;
    for (int ii = 0; ii < N; ++ii)
        {
        Dscalar2 pos = h_p.data[ii];
        xcm+=pos.x;
        ycm+=pos.y;
        };
    xcm /= (Dscalar)N;
    ycm /= (Dscalar)N;
    if(true)
        {
        ArrayHandle<Dscalar2> h_disp(displacements,access_location::host,access_mode::overwrite);
        for (int ii = 0; ii < N; ++ii)
            {
            h_disp.data[ii].x = -(xcm-x11*0.5);
            h_disp.data[ii].y = -(ycm-x22*0.5);
            };
        };
    movePoints(displacements);
    };

void SPV2D::calculateDispCPU()
    {
    ArrayHandle<Dscalar2> h_f(forces,access_location::host,access_mode::read);
    ArrayHandle<Dscalar> h_cd(cellDirectors,access_location::host,access_mode::readwrite);
    ArrayHandle<Dscalar2> h_disp(displacements,access_location::host,access_mode::overwrite);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> normal(0.0,sqrt(2.0*deltaT*Dr));
    for (int ii = 0; ii < N; ++ii)
        {
        Dscalar dx,dy;
        Dscalar directorx = cos(h_cd.data[ii]);
        Dscalar directory = sin(h_cd.data[ii]);

        dx= deltaT*(v0*directorx+h_f.data[ii].x);
        dy= deltaT*(v0*directory+h_f.data[ii].y);
        h_disp.data[ii].x = dx;
        h_disp.data[ii].y = dy;

        //rotate each director a bit
        h_cd.data[ii] +=normal(gen);
        };

    //vector of displacements is forces*timestep + v0's*timestep


    };

void SPV2D::performTimestepCPU()
    {
    //clock_t t1,t2;
    //t1=clock();
    computeGeometryCPU();
    if(useTension)
        {
        for (int ii = 0; ii < N; ++ii)
            computeSPVForceWithTensionsCPU(ii,gamma);
        }
    else
        {
        for (int ii = 0; ii < N; ++ii)
            computeSPVForceCPU(ii);
        };

    calculateDispCPU();

    movePointsCPU(displacements);
    //t2=clock();
    //forcetiming += t2-t1;
    //t1=clock();
    testAndRepairTriangulation();
    //t2=clock();
    //triangletiming += t2-t1;
    };

void SPV2D::performTimestepGPU()
    {
//    clock_t t1,t2;
//    printf("computing geometry for timestep %i\n",Timestep);
//    t1=clock();
    computeGeometryGPU();
//    t2=clock();
//    triangletiming += (t2-t1);
//    gputiming += (t2-t1);
//    printf("computing forces\n");
//    t1=clock();
    if(!useTension)
        computeSPVForceSetsGPU();
    else
        computeSPVForceSetsWithTensionsGPU();

    if(!particleExclusions)
        sumForceSets();
    else
        sumForceSetsWithExclusions();

//    t2=clock();
//    forcetiming += t2-t1;
//    gputiming += (t2-t1);
//    t1=clock();

//    printf("displacing particles\n");
    DisplacePointsAndRotate();
//    t2=clock();
//    gputiming += (t2-t1);


//    printf("recomputing triangulation\n");
    testAndRepairTriangulation();

//    t1=clock();
    if(Fails == 1)
        {
        //maintain the auxilliary lists for computing forces
        if(FullFails || neighMaxChange)
            {
            allDelSets();
            neighMaxChange = false;
            }
        else
            {
            for (int jj = 0;jj < NeedsFixing.size(); ++jj)
                getDelSets(NeedsFixing[jj]);
            };
        };
//    t2=clock();
//    cputiming += (t2-t1);
    };

void SPV2D::computeGeometryGPU()
    {
    ArrayHandle<Dscalar2> d_p(points,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_AP(AreaPeri,access_location::device,access_mode::readwrite);
    ArrayHandle<int> d_nn(neigh_num,access_location::device,access_mode::read);
    ArrayHandle<int> d_n(neighs,access_location::device,access_mode::read);

    gpu_compute_geometry(
                        d_p.data,
                        d_AP.data,
                        d_nn.data,
                        d_n.data,
                        N, n_idx,Box);


    };

void SPV2D::sumForceSets()
    {

    ArrayHandle<int> d_nn(neigh_num,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forceSets(forceSets,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forces(forces,access_location::device,access_mode::overwrite);

    gpu_sum_force_sets(
                    d_forceSets.data,
                    d_forces.data,
                    d_nn.data,
                    N,n_idx);
    };


void SPV2D::sumForceSetsWithExclusions()
    {

    ArrayHandle<int> d_nn(neigh_num,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forceSets(forceSets,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forces(forces,access_location::device,access_mode::overwrite);
    ArrayHandle<Dscalar2> d_external_forces(external_forces,access_location::device,access_mode::overwrite);
    ArrayHandle<int> d_exes(exclusions,access_location::device,access_mode::read);

    gpu_sum_force_sets_with_exclusions(
                    d_forceSets.data,
                    d_forces.data,
                    d_external_forces.data,
                    d_exes.data,
                    d_nn.data,
                    N,n_idx);
    };



void SPV2D::computeSPVForceSetsGPU()
    {
    ArrayHandle<Dscalar2> d_p(points,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_AP(AreaPeri,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_APpref(AreaPeriPreferences,access_location::device,access_mode::read);
    ArrayHandle<int4> d_delSets(delSets,access_location::device,access_mode::read);
    ArrayHandle<int> d_delOther(delOther,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forceSets(forceSets,access_location::device,access_mode::overwrite);
    ArrayHandle<int2> d_nidx(NeighIdxs,access_location::device,access_mode::read);


    Dscalar KA = 1.0;
    Dscalar KP = 1.0;
    gpu_force_sets(
                    d_p.data,
                    d_AP.data,
                    d_APpref.data,
                    d_delSets.data,
                    d_delOther.data,
                    d_forceSets.data,
                    d_nidx.data,
                    KA,
                    KP,
                    NeighIdxNum,n_idx,Box);
    };


void SPV2D::computeSPVForceSetsWithTensionsGPU()
    {
    ArrayHandle<Dscalar2> d_p(points,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_AP(AreaPeri,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_APpref(AreaPeriPreferences,access_location::device,access_mode::read);
    ArrayHandle<int4> d_delSets(delSets,access_location::device,access_mode::read);
    ArrayHandle<int> d_delOther(delOther,access_location::device,access_mode::read);
    ArrayHandle<Dscalar2> d_forceSets(forceSets,access_location::device,access_mode::overwrite);
    ArrayHandle<int2> d_nidx(NeighIdxs,access_location::device,access_mode::read);
    ArrayHandle<int> d_ct(CellType,access_location::device,access_mode::read);


    Dscalar KA = 1.0;
    Dscalar KP = 1.0;
    gpu_force_sets_tensions(
                    d_p.data,
                    d_AP.data,
                    d_APpref.data,
                    d_delSets.data,
                    d_delOther.data,
                    d_forceSets.data,
                    d_nidx.data,
                    d_ct.data,
                    KA,
                    KP,
                    gamma,
                    NeighIdxNum,n_idx,Box);


    };


void SPV2D::computeGeometryCPU()
    {
    for (int i = 0; i < N; ++i)
        {
        //read in all the data we'll need
        ArrayHandle<Dscalar2> h_p(points,access_location::host,access_mode::read);
        ArrayHandle<Dscalar2> h_AP(AreaPeri,access_location::host,access_mode::readwrite);

        ArrayHandle<int> h_nn(neigh_num,access_location::host,access_mode::read);
        ArrayHandle<int> h_n(neighs,access_location::host,access_mode::read);

        //get Delaunay neighbors of the cell
        int neigh = h_nn.data[i];
        vector<int> ns(neigh);
        for (int nn = 0; nn < neigh; ++nn)
            {
            ns[nn]=h_n.data[n_idx(nn,i)];
            };

        //compute base set of voronoi points, and the derivatives of those points w/r/t cell i's position
        vector<Dscalar2> voro(neigh);
        Dscalar2 circumcent;
        Dscalar2 nnextp,nlastp;
        Dscalar2 pi = h_p.data[i];
        Dscalar2 rij, rik;

        nlastp = h_p.data[ns[ns.size()-1]];
        Box.minDist(nlastp,pi,rij);
        for (int nn = 0; nn < neigh;++nn)
            {
            nnextp = h_p.data[ns[nn]];
            Box.minDist(nnextp,pi,rik);
            Circumcenter(rij,rik,circumcent);
            voro[nn] = circumcent;
            rij=rik;
            };

        Dscalar2 vlast,vnext;
        //compute Area and perimeter
        Dscalar Varea = 0.0;
        Dscalar Vperi = 0.0;
        vlast = voro[neigh-1];
        for (int nn = 0; nn < neigh; ++nn)
            {
            vnext=voro[nn];
            Varea += TriangleArea(vlast,vnext);
            Dscalar dx = vlast.x-vnext.x;
            Dscalar dy = vlast.y-vnext.y;
            Vperi += sqrt(dx*dx+dy*dy);
            vlast=vnext;
            };
        h_AP.data[i].x = Varea;
        h_AP.data[i].y = Vperi;
        };
    };

void SPV2D::computeSPVForceCPU(int i)
    {
    Dscalar Pthreshold = 1e-8;

    //read in all the data we'll need
    ArrayHandle<Dscalar2> h_p(points,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> h_f(forces,access_location::host,access_mode::readwrite);
    ArrayHandle<Dscalar2> h_AP(AreaPeri,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> h_APpref(AreaPeriPreferences,access_location::host,access_mode::read);

    ArrayHandle<int> h_nn(neigh_num,access_location::host,access_mode::read);
    ArrayHandle<int> h_n(neighs,access_location::host,access_mode::read);

    //get Delaunay neighbors of the cell
    int neigh = h_nn.data[i];
    vector<int> ns(neigh);
    for (int nn = 0; nn < neigh; ++nn)
        {
        ns[nn]=h_n.data[n_idx(nn,i)];
        };

    //compute base set of voronoi points, and the derivatives of those points w/r/t cell i's position
    vector<Dscalar2> voro(neigh);
    vector<Matrix2x2> dhdri(neigh);
    Matrix2x2 Id;
    Dscalar2 circumcent;
    Dscalar2 rij,rik;
    Dscalar2 nnextp,nlastp;
    Dscalar2 rjk;
    Dscalar2 pi = h_p.data[i];

    nlastp = h_p.data[ns[ns.size()-1]];
    Box.minDist(nlastp,pi,rij);
    for (int nn = 0; nn < neigh;++nn)
        {
        nnextp = h_p.data[ns[nn]];
        Box.minDist(nnextp,pi,rik);
        Circumcenter(rij,rik,circumcent);
        voro[nn] = circumcent;
        rjk.x =rik.x-rij.x;
        rjk.y =rik.y-rij.y;

        Dscalar2 dbDdri,dgDdri,dDdriOD,z;
        Dscalar betaD = -dot(rik,rik)*dot(rij,rjk);
        Dscalar gammaD = dot(rij,rij)*dot(rik,rjk);
        Dscalar cp = rij.x*rjk.y - rij.y*rjk.x;
        Dscalar D = 2*cp*cp;


        z.x = betaD*rij.x+gammaD*rik.x;
        z.y = betaD*rij.y+gammaD*rik.y;

        dbDdri.x = 2*dot(rij,rjk)*rik.x+dot(rik,rik)*rjk.x;
        dbDdri.y = 2*dot(rij,rjk)*rik.y+dot(rik,rik)*rjk.y;

        dgDdri.x = -2*dot(rik,rjk)*rij.x-dot(rij,rij)*rjk.x;
        dgDdri.y = -2*dot(rik,rjk)*rij.y-dot(rij,rij)*rjk.y;

        dDdriOD.x = (-2.0*rjk.y)/cp;
        dDdriOD.y = (2.0*rjk.x)/cp;

        dhdri[nn] = Id+1.0/D*(dyad(rij,dbDdri)+dyad(rik,dgDdri)-(betaD+gammaD)*Id-dyad(z,dDdriOD));

        rij=rik;
        };

    Dscalar2 vlast,vnext,vother;
    vlast = voro[neigh-1];

    //start calculating forces
    Dscalar2 forceSum;
    forceSum.x=0.0;forceSum.y=0.0;
    Dscalar KA = 1.0;
    Dscalar KP = 1.0;

    Dscalar Adiff = KA*(h_AP.data[i].x - h_APpref.data[i].x);
    Dscalar Pdiff = KP*(h_AP.data[i].y - h_APpref.data[i].y);

//    printf("cell %i: %f, %f\n",i,h_AP.data[i].x,h_APpref.data[i].x);

    Dscalar2 vcur;
    vlast = voro[neigh-1];
    for(int nn = 0; nn < neigh; ++nn)
        {
        //first, let's do the self-term, dE_i/dr_i
        vcur = voro[nn];
        vnext = voro[(nn+1)%neigh];
        Dscalar2 dEidv,dAidv,dPidv;
        dAidv.x = 0.5*(vlast.y-vnext.y);
        dAidv.y = 0.5*(vnext.x-vlast.x);

        Dscalar2 dlast,dnext;
        dlast.x = vlast.x-vcur.x;
        dlast.y=vlast.y-vcur.y;

        Dscalar dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);

        dnext.x = vcur.x-vnext.x;
        dnext.y = vcur.y-vnext.y;
        Dscalar dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;

        dPidv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPidv.y = dlast.y/dlnorm - dnext.y/dnnorm;



        //
        //
        //now let's compute the other terms...first we need to find the third voronoi
        //position that v_cur is connected to
        //
        //
        int baseNeigh = ns[nn];
        int other_idx = nn - 1;
        if (other_idx < 0) other_idx += neigh;
        int otherNeigh = ns[other_idx];
        int neigh2 = h_nn.data[baseNeigh];
        int DT_other_idx = -1;
        for (int n2 = 0; n2 < neigh2; ++n2)
            {
            int testPoint = h_n.data[n_idx(n2,baseNeigh)];
            if(testPoint == otherNeigh) DT_other_idx = h_n.data[n_idx((n2+1)%neigh2,baseNeigh)];
            };
        if(DT_other_idx == otherNeigh || DT_other_idx == baseNeigh || DT_other_idx == -1)
            {
            printf("Triangulation problem %i\n",DT_other_idx);
            throw std::exception();
            };
        Dscalar2 nl1 = h_p.data[otherNeigh];
        Dscalar2 nn1 = h_p.data[baseNeigh];
        Dscalar2 no1 = h_p.data[DT_other_idx];


        Dscalar2 r1,r2,r3;
        Box.minDist(nl1,pi,r1);
        Box.minDist(nn1,pi,r2);
        Box.minDist(no1,pi,r3);

        Circumcenter(r1,r2,r3,vother);
        if(vother.x*vother.x+vother.y*vother.y > 10)
//        if(true)
            {
//        printf("\nvother %i--%i--%i = (%f,%f)\n",baseNeigh,otherNeigh,DT_other_idx,vother.x,vother.y);
//            printf("Big voro_other:\n");
//            printf("(%f,%f), (%f,%f), (%f,%f)\n",r1.x,r1.y,r2.x,r2.y,r3.x,r3.y);

            };

        Dscalar Akdiff = KA*(h_AP.data[baseNeigh].x  - h_APpref.data[baseNeigh].x);
        Dscalar Pkdiff = KP*(h_AP.data[baseNeigh].y  - h_APpref.data[baseNeigh].y);
        Dscalar Ajdiff = KA*(h_AP.data[otherNeigh].x - h_APpref.data[otherNeigh].x);
        Dscalar Pjdiff = KP*(h_AP.data[otherNeigh].y - h_APpref.data[otherNeigh].y);

        Dscalar2 dEkdv,dAkdv,dPkdv;
        dAkdv.x = 0.5*(vnext.y-vother.y);
        dAkdv.y = 0.5*(vother.x-vnext.x);

        dlast.x = vnext.x-vcur.x;
        dlast.y=vnext.y-vcur.y;
        dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);
        dnext.x = vcur.x-vother.x;
        dnext.y = vcur.y-vother.y;
        dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;

        dPkdv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPkdv.y = dlast.y/dlnorm - dnext.y/dnnorm;

        Dscalar2 dEjdv,dAjdv,dPjdv;
        dAjdv.x = 0.5*(vother.y-vlast.y);
        dAjdv.y = 0.5*(vlast.x-vother.x);

        dlast.x = vother.x-vcur.x;
        dlast.y=vother.y-vcur.y;
        dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);
        dnext.x = vcur.x-vlast.x;
        dnext.y = vcur.y-vlast.y;
        dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;

        dPjdv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPjdv.y = dlast.y/dlnorm - dnext.y/dnnorm;

        dEidv.x = 2.0*Adiff*dAidv.x  + 2.0*Pdiff*dPidv.x;
        dEidv.y = 2.0*Adiff*dAidv.y  + 2.0*Pdiff*dPidv.y;
        dEkdv.x = 2.0*Akdiff*dAkdv.x + 2.0*Pkdiff*dPkdv.x;
        dEkdv.y = 2.0*Akdiff*dAkdv.y + 2.0*Pkdiff*dPkdv.y;
        dEjdv.x = 2.0*Ajdiff*dAjdv.x + 2.0*Pjdiff*dPjdv.x;
        dEjdv.y = 2.0*Ajdiff*dAjdv.y + 2.0*Pjdiff*dPjdv.y;

        Dscalar2 temp = dEidv*dhdri[nn];
        forceSum.x += temp.x;
        forceSum.y += temp.y;

        Dscalar2 temp2 = dEkdv*dhdri[nn];
        forceSum.x += temp2.x;
        forceSum.y += temp2.y;

        Dscalar2 temp3 = dEjdv*dhdri[nn];
        forceSum.x += temp3.x;
        forceSum.y += temp3.y;

//        printf("\nvother %i--%i--%i = (%f,%f)\n",baseNeigh,otherNeigh,DT_other_idx,vother.x,vother.y);

//        printf("%f\t %f\t %f\t %f\t %f\t %f\t\n",Adiff,Akdiff,Ajdiff,Pdiff,Pkdiff,Pjdiff);
//        if (i ==0)
//            printf("(%f,%f)\t(%f,%f)\t(%f,%f)\n",dPidv.x,dPidv.y,dPkdv.x,dPkdv.y,dPjdv.x,dPjdv.y);
            //    printf("%f\t%f\t%f\t%f\n",dhdri[nn].x11,dhdri[nn].x12,dhdri[nn].x21,dhdri[nn].x22);
//            printf("%i %f %f\n",nn,temp.x+temp2.x+temp3.x,temp.y+temp2.y+temp3.y);
        vlast=vcur;
        };



    h_f.data[i].x=forceSum.x;
    h_f.data[i].y=forceSum.y;
//    printf("total force on cell: (%f,%f)\n",forceSum.x,forceSum.y);
    };

void SPV2D::computeSPVForceWithTensionsCPU(int i,bool verbose)
    {
    Dscalar Pthreshold = 1e-8;
 //   printf("cell %i: \n",i);
    //for testing these routines...
    vector <int> test;
    DelaunayCell celltest;
    delLoc.triangulatePoint(i, test,celltest);

    //read in all the data we'll need
    ArrayHandle<Dscalar2> h_p(points,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> h_f(forces,access_location::host,access_mode::readwrite);
    ArrayHandle<int> h_ct(CellType,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> h_AP(AreaPeri,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> h_APpref(AreaPeriPreferences,access_location::host,access_mode::read);

    ArrayHandle<int> h_nn(neigh_num,access_location::host,access_mode::read);
    ArrayHandle<int> h_n(neighs,access_location::host,access_mode::read);

    //get Delaunay neighbors of the cell
    int neigh = h_nn.data[i];
    vector<int> ns(neigh);
    for (int nn = 0; nn < neigh; ++nn)
        {
        ns[nn]=h_n.data[n_idx(nn,i)];
//        if (i == 602)
//            printf("%i - ",ns[nn]);
        };

    //compute base set of voronoi points, and the derivatives of those points w/r/t cell i's position
    vector<Dscalar2> voro(neigh);
    vector<Matrix2x2> dhdri(neigh);
    Matrix2x2 Id;
    Dscalar2 circumcent;
    Dscalar2 rij,rik;
    Dscalar2 nnextp,nlastp;
    Dscalar2 rjk;
    Dscalar2 pi = h_p.data[i];

    nlastp = h_p.data[ns[ns.size()-1]];
    Box.minDist(nlastp,pi,rij);
    for (int nn = 0; nn < neigh;++nn)
        {
        nnextp = h_p.data[ns[nn]];
        Box.minDist(nnextp,pi,rik);
        Circumcenter(rij,rik,circumcent);
        voro[nn] = circumcent;
        rjk.x =rik.x-rij.x;
        rjk.y =rik.y-rij.y;

        Dscalar2 dbDdri,dgDdri,dDdriOD,z;
        Dscalar betaD = -dot(rik,rik)*dot(rij,rjk);
        Dscalar gammaD = dot(rij,rij)*dot(rik,rjk);
        Dscalar cp = rij.x*rjk.y - rij.y*rjk.x;
        Dscalar D = 2*cp*cp;


        z.x = betaD*rij.x+gammaD*rik.x;
        z.y = betaD*rij.y+gammaD*rik.y;

        dbDdri.x = 2*dot(rij,rjk)*rik.x+dot(rik,rik)*rjk.x;
        dbDdri.y = 2*dot(rij,rjk)*rik.y+dot(rik,rik)*rjk.y;

        dgDdri.x = -2*dot(rik,rjk)*rij.x-dot(rij,rij)*rjk.x;
        dgDdri.y = -2*dot(rik,rjk)*rij.y-dot(rij,rij)*rjk.y;

        dDdriOD.x = (-2.0*rjk.y)/cp;
        dDdriOD.y = (2.0*rjk.x)/cp;

        dhdri[nn] = Id+1.0/D*(dyad(rij,dbDdri)+dyad(rik,dgDdri)-(betaD+gammaD)*Id-dyad(z,dDdriOD));

        rij=rik;
        };

    Dscalar2 vlast,vnext,vother;
    vlast = voro[neigh-1];

    //start calculating forces
    Dscalar2 forceSum;
    forceSum.x=0.0;forceSum.y=0.0;
    Dscalar KA = 1.0;
    Dscalar KP = 1.0;

    Dscalar Adiff = KA*(h_AP.data[i].x - h_APpref.data[i].x);
    Dscalar Pdiff = KP*(h_AP.data[i].y - h_APpref.data[i].y);

//    printf("cell %i: %f, %f\n",i,h_AP.data[i].x,h_APpref.data[i].x);

    Dscalar2 vcur;
    vlast = voro[neigh-1];
    for(int nn = 0; nn < neigh; ++nn)
        {
        //first, let's do the self-term, dE_i/dr_i
        vcur = voro[nn];
        vnext = voro[(nn+1)%neigh];
        int baseNeigh = ns[nn];
        int other_idx = nn - 1;
        if (other_idx < 0) other_idx += neigh;
        int otherNeigh = ns[other_idx];


        Dscalar2 dEidv,dAidv,dPidv,dTidv;
        dTidv.x = 0.0; dTidv.y = 0.0;

        dAidv.x = 0.5*(vlast.y-vnext.y);
        dAidv.y = 0.5*(vnext.x-vlast.x);

        Dscalar2 dlast,dnext;
        dlast.x = vlast.x-vcur.x;
        dlast.y=vlast.y-vcur.y;

        Dscalar dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);

        dnext.x = vcur.x-vnext.x;
        dnext.y = vcur.y-vnext.y;
        Dscalar dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;
        dPidv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPidv.y = dlast.y/dlnorm - dnext.y/dnnorm;

        //individual line tensions
        if(h_ct.data[i] != h_ct.data[baseNeigh])
            {
            dTidv.x -= dnext.x/dnnorm;
            dTidv.y -= dnext.y/dnnorm;
            };
        if(h_ct.data[i] != h_ct.data[otherNeigh])
            {
            dTidv.x += dlast.x/dlnorm;
            dTidv.y += dlast.y/dlnorm;
            };

        //
        //
        //now let's compute the other terms...first we need to find the third voronoi
        //position that v_cur is connected to
        //
        //
        int neigh2 = h_nn.data[baseNeigh];
        int DT_other_idx=-1;
        for (int n2 = 0; n2 < neigh2; ++n2)
            {
            int testPoint = h_n.data[n_idx(n2,baseNeigh)];
            if(testPoint == otherNeigh) DT_other_idx = h_n.data[n_idx((n2+1)%neigh2,baseNeigh)];
            };
        if(DT_other_idx == otherNeigh || DT_other_idx == baseNeigh || DT_other_idx == -1)
            {
            printf("Triangulation problem %i\n",DT_other_idx);
            throw std::exception();
            };
        Dscalar2 nl1 = h_p.data[otherNeigh];
        Dscalar2 nn1 = h_p.data[baseNeigh];
        Dscalar2 no1 = h_p.data[DT_other_idx];

        Dscalar2 r1,r2,r3;
        Box.minDist(nl1,pi,r1);
        Box.minDist(nn1,pi,r2);
        Box.minDist(no1,pi,r3);

        Circumcenter(r1,r2,r3,vother);

        Dscalar Akdiff = KA*(h_AP.data[baseNeigh].x  - h_APpref.data[baseNeigh].x);
        Dscalar Pkdiff = KP*(h_AP.data[baseNeigh].y  - h_APpref.data[baseNeigh].y);
        Dscalar Ajdiff = KA*(h_AP.data[otherNeigh].x - h_APpref.data[otherNeigh].x);
        Dscalar Pjdiff = KP*(h_AP.data[otherNeigh].y - h_APpref.data[otherNeigh].y);

        Dscalar2 dEkdv,dAkdv,dPkdv,dTkdv;
        dTkdv.x = 0.0;
        dTkdv.y = 0.0;
        dAkdv.x = 0.5*(vnext.y-vother.y);
        dAkdv.y = 0.5*(vother.x-vnext.x);

        dlast.x = vnext.x-vcur.x;
        dlast.y=vnext.y-vcur.y;
        dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);
        dnext.x = vcur.x-vother.x;
        dnext.y = vcur.y-vother.y;
        dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;

        dPkdv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPkdv.y = dlast.y/dlnorm - dnext.y/dnnorm;

        if(h_ct.data[i]!=h_ct.data[baseNeigh])
            {
            dTkdv.x +=dlast.x/dlnorm;
            dTkdv.y +=dlast.y/dlnorm;
            };
        if(h_ct.data[otherNeigh]!=h_ct.data[baseNeigh])
            {
            dTkdv.x -=dnext.x/dnnorm;
            dTkdv.y -=dnext.y/dnnorm;
            };

        Dscalar2 dEjdv,dAjdv,dPjdv,dTjdv;
        dTjdv.x = 0.0;
        dTjdv.y = 0.0;
        dAjdv.x = 0.5*(vother.y-vlast.y);
        dAjdv.y = 0.5*(vlast.x-vother.x);

        dlast.x = vother.x-vcur.x;
        dlast.y=vother.y-vcur.y;
        dlnorm = sqrt(dlast.x*dlast.x+dlast.y*dlast.y);
        dnext.x = vcur.x-vlast.x;
        dnext.y = vcur.y-vlast.y;
        dnnorm = sqrt(dnext.x*dnext.x+dnext.y*dnext.y);
        if(dnnorm < Pthreshold)
            dnnorm = Pthreshold;
        if(dlnorm < Pthreshold)
            dlnorm = Pthreshold;

        dPjdv.x = dlast.x/dlnorm - dnext.x/dnnorm;
        dPjdv.y = dlast.y/dlnorm - dnext.y/dnnorm;

        if(h_ct.data[i]!=h_ct.data[otherNeigh])
            {
            dTjdv.x -=dnext.x/dnnorm;
            dTjdv.y -=dnext.y/dnnorm;
            };
        if(h_ct.data[otherNeigh]!=h_ct.data[baseNeigh])
            {
            dTjdv.x +=dlast.x/dlnorm;
            dTjdv.y +=dlast.y/dlnorm;
            };


        dEidv.x = 2.0*Adiff*dAidv.x + 2.0*Pdiff*dPidv.x + gamma*dTidv.x;
        dEidv.y = 2.0*Adiff*dAidv.y + 2.0*Pdiff*dPidv.y + gamma*dTidv.y;

        dEkdv.x = 2.0*Akdiff*dAkdv.x + 2.0*Pkdiff*dPkdv.x + gamma*dTkdv.x;
        dEkdv.y = 2.0*Akdiff*dAkdv.y + 2.0*Pkdiff*dPkdv.y + gamma*dTkdv.y;

        dEjdv.x = 2.0*Ajdiff*dAjdv.x + 2.0*Pjdiff*dPjdv.x + gamma*dTjdv.x;
        dEjdv.y = 2.0*Ajdiff*dAjdv.y + 2.0*Pjdiff*dPjdv.y + gamma*dTjdv.y;

        Dscalar2 temp = dEidv*dhdri[nn];
        forceSum.x += temp.x;
        forceSum.y += temp.y;

        temp = dEkdv*dhdri[nn];
        forceSum.x += temp.x;
        forceSum.y += temp.y;

        temp = dEjdv*dhdri[nn];
        forceSum.x += temp.x;
        forceSum.y += temp.y;

        if(verbose)
            {
            printf("idx %i; baseNeigh %i; otherNeigh %i; DT_other_idx %i\n",i,baseNeigh,otherNeigh,DT_other_idx);
            printf("%f  %f   %f   \n%f  %f    %f\n   %f    %f    %f\n",dAidv.x,dPidv.x,dTidv.x,dAkdv.x, dPkdv.x,dTkdv.x,dAjdv.x,dPjdv.x,dTjdv.x);
            };
//        printf("\nvother %i--%i--%i = (%f,%f)\n",baseNeigh,otherNeigh,DT_other_idx,vother.x,vother.y);

//        printf("%f\t %f\t %f\t %f\t %f\t %f\t\n",Adiff,Akdiff,Ajdiff,Pdiff,Pkdiff,Pjdiff);
        vlast=vcur;
        };



    h_f.data[i].x=forceSum.x;
    h_f.data[i].y=forceSum.y;
//    printf("total force on cell: (%f,%f)\n",forceSum.x,forceSum.y);
    };


void SPV2D::meanArea()
    {
    ArrayHandle<Dscalar2> h_AP(AreaPeri,access_location::host,access_mode::read);
    Dscalar fx = 0.0;
    for (int i = 0; i < N; ++i)
        {
//        printf("cell %i Area %f\n",i,h_AP.data[i].x);
        fx += h_AP.data[i].x/N;
        };
    printf("Mean area = %f\n" ,fx);

    };

void SPV2D::reportDirectors()
    {
    ArrayHandle<Dscalar> h_cd(cellDirectors,access_location::host,access_mode::read);
    Dscalar fx = 0.0;
    Dscalar fy = 0.0;
    Dscalar min = 10000;
    Dscalar max = -10000;
    for (int i = 0; i < N; ++i)
        {
        if (h_cd.data[i] >max)
            max = h_cd.data[i];
        if (h_cd.data[i] < min)
            min = h_cd.data[i];
        };
    printf("min/max director : (%f,%f)\n",min,max);

    };


void SPV2D::reportForces()
    {
    ArrayHandle<Dscalar2> h_f(forces,access_location::host,access_mode::read);
    ArrayHandle<Dscalar2> p(points,access_location::host,access_mode::read);
    Dscalar fx = 0.0;
    Dscalar fy = 0.0;
    Dscalar min = 10000;
    Dscalar max = -10000;
    for (int i = 0; i < N; ++i)
        {
        if (h_f.data[i].y >max)
            max = h_f.data[i].y;
        if (h_f.data[i].x >max)
            max = h_f.data[i].x;
        if (h_f.data[i].y < min)
            min = h_f.data[i].y;
        if (h_f.data[i].x < min)
            min = h_f.data[i].x;
        fx += h_f.data[i].x;
        fy += h_f.data[i].y;
//
//        if (isnan(h_f.data[i].x) || isnan(h_f.data[i].y))
//        if(i == N-1)
//          printf("cell %i: \t position (%f,%f)\t force (%f, %f)\n",i,p.data[i].x,p.data[i].y ,h_f.data[i].x,h_f.data[i].y);
        };
    printf("min/max force : (%f,%f)\n",min,max);

    };

void SPV2D::meanForce()
    {
    ArrayHandle<Dscalar2> h_f(forces,access_location::host,access_mode::read);
    Dscalar fx = 0.0;
    Dscalar fy = 0.0;
    for (int i = 0; i < N; ++i)
        {
        fx += h_f.data[i].x;
        fy += h_f.data[i].y;
        };
    printf("Mean force = (%e,%e)\n" ,fx,fy);

    };

Dscalar SPV2D::reportq()
    {
    ArrayHandle<Dscalar2> h_AP(AreaPeri,access_location::host,access_mode::read);
    Dscalar A = 0.0;
    Dscalar P = 0.0;
    Dscalar q = 0.0;
    for (int i = 0; i < N; ++i)
        {
        A = h_AP.data[i].x;
        P = h_AP.data[i].y;
        q += P / sqrt(A);
        };
    return q/(Dscalar)N;
    };

void SPV2D::deltaAngle()
    {
    ArrayHandle<Dscalar> h_cd(cellDirectors,access_location::host, access_mode::read);
    ArrayHandle<Dscalar> h_cdi(cellDirectors_initial,access_location::host, access_mode::read);
    Dscalar dA = 0;
    for (int ii = 0; ii < N; ++ii)
        {
        dA += (h_cd.data[ii]-h_cdi.data[ii])* (h_cd.data[ii]-h_cdi.data[ii]);
        };
    dA/=(Dscalar)N;
    printf("timestep, dA^2 = (%i,%f)\n",Timestep,dA);


    };

