#include "dynamicalFeatures.h"
#include "functions.h"
/*! \file dynamicalFeatures.cpp */

dynamicalFeatures::dynamicalFeatures(GPUArray<double2> &initialPos, PeriodicBoxPtr _bx, double fractionAnalyzed)
    {
    Box = _bx;
    copyGPUArrayData(initialPos,iPos);
    N = iPos.size();
    if(fractionAnalyzed < 1)
        N = floor(N*fractionAnalyzed);
    };

dynamicalFeatures::dynamicalFeatures(GPUArray<double2> &initialVel)
    {
    copyGPUArrayData(initialVel,iVel);
    N = iVel.size();
    };

void dynamicalFeatures::setCageNeighbors(GPUArray<int> &neighbors, GPUArray<int> &neighborNum, Index2D n_idx)
    {
    nIdx = Index2D(n_idx.getW(),n_idx.getH());
    ArrayHandle<int> h_nn(neighborNum,access_location::host,access_mode::read);
    ArrayHandle<int> h_n(neighbors,access_location::host,access_mode::read);

    cageNeighbors.resize(N);
    for (int ii = 0; ii < N; ++ii)
        {
        int neighs = h_nn.data[ii];
        vector<int> ns(neighs);
        for (int nn = 0; nn < neighs; ++nn)
            {
            ns[nn]=h_n.data[nIdx(nn,ii)];
            };
        cageNeighbors[ii] = ns;
        }
    };

void dynamicalFeatures::computeDisplacements(GPUArray<double2> &currentPos)
    {
    currentDisplacements.resize(N);
    //first, compute the vector of current displacements
    ArrayHandle<double2> fPos(currentPos,access_location::host,access_mode::read);
    double2 disp,cur,init;
    for (int ii = 0; ii < N; ++ii)
        {
        cur = fPos.data[ii];
        init = iPos[ii];
        Box->minDist(cur,init,disp);
        currentDisplacements[ii] = disp;
        }
    };

void dynamicalFeatures::computeTrueDisplacements(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox)
    {
    currentDisplacements.resize(N);
    //first, compute the vector of current displacements
    ArrayHandle<double2> fPos(currentPos,access_location::host,access_mode::read);
    ArrayHandle<double2> sPos(previousPos,access_location::host,access_mode::read);
    double2 disp,cur,init,prev;
    int2 curWhichBox, prevWhichBox, initWhichBox;
    initWhichBox.x = 0,initWhichBox.y = 0;
    for (int ii = 0; ii < N; ++ii)
        {
        prev = sPos.data[ii];
        cur = fPos.data[ii];
        init = iPos[ii];
        prevWhichBox = previousWhichBox[ii];
        Box->whichBox(cur,prev,prevWhichBox,curWhichBox);
        previousWhichBox[ii] = curWhichBox;
        Box->trueDist(cur,init,curWhichBox,initWhichBox,disp);
        currentDisplacements[ii] = disp;
        }
    };

void dynamicalFeatures::computeCageRelativeDisplacements(GPUArray<double2> &currentPos)
    {
    cageRelativeDisplacements.resize(N);
    cageDisplacements.resize(N);
    cageEnhancedDisplacements.resize(N);
    //first, compute the vector of current displacements
    computeDisplacements(currentPos);

    //now, for each particle, compute the cage-relativedisplacement
    double2 cur;
    double2 temp;
    for(int ii = 0; ii < N; ++ii)
        {
        //self term
        cur = currentDisplacements[ii];
        //subtract off net neighbor motion
        int nNeighs = cageNeighbors[ii].size();
        temp.x=0;temp.y=0;
        for(int nn = 0; nn < nNeighs; ++nn)
            {
            int neighborIndex = cageNeighbors[ii][nn];
            temp.x = temp.x + currentDisplacements[neighborIndex].x;
            temp.y = temp.y + currentDisplacements[neighborIndex].y;
            }
        cageRelativeDisplacements[ii].x = cur.x - (1./((double) nNeighs))* temp.x;
        cageRelativeDisplacements[ii].y = cur.y - (1./((double) nNeighs))* temp.y;
        cageEnhancedDisplacements[ii].x = cur.x + (1./((double) nNeighs))* temp.x;
        cageEnhancedDisplacements[ii].y = cur.y + (1./((double) nNeighs))* temp.y;
        cageDisplacements[ii].x = (1./((double) nNeighs))* temp.x;
        cageDisplacements[ii].y = (1./((double) nNeighs))* temp.y;
        };
    };

void dynamicalFeatures::computeCageRelativeTrueDisplacements(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox)
    {
    cageRelativeDisplacements.resize(N);
    cageDisplacements.resize(N);
    cageEnhancedDisplacements.resize(N);
    //first, compute the vector of current displacements
    computeTrueDisplacements(currentPos, previousPos, previousWhichBox);

    //now, for each particle, compute the cage-relativedisplacement
    double2 cur;
    double2 temp;
    for(int ii = 0; ii < N; ++ii)
        {
        //self term
        cur = currentDisplacements[ii];
        //subtract off net neighbor motion
        int nNeighs = cageNeighbors[ii].size();
        temp.x=0;temp.y=0;
        for(int nn = 0; nn < nNeighs; ++nn)
            {
            int neighborIndex = cageNeighbors[ii][nn];
            temp.x = temp.x + currentDisplacements[neighborIndex].x;
            temp.y = temp.y + currentDisplacements[neighborIndex].y;
            }
        cageRelativeDisplacements[ii].x = cur.x - (1./((double) nNeighs))* temp.x;
        cageRelativeDisplacements[ii].y = cur.y - (1./((double) nNeighs))* temp.y;
        cageEnhancedDisplacements[ii].x = cur.x + (1./((double) nNeighs))* temp.x;
        cageEnhancedDisplacements[ii].y = cur.y + (1./((double) nNeighs))* temp.y;
        cageDisplacements[ii].x = (1./((double) nNeighs))* temp.x;
        cageDisplacements[ii].y = (1./((double) nNeighs))* temp.y;
        };
    };

// a simple (not strictly correct) calculation of velocity auto-correlation function.
double dynamicalFeatures::computeVelocityCorrelation(GPUArray<double2> &currentVel)
    {
    ArrayHandle<double2> fVel(currentVel,access_location::host,access_mode::read);
    double2 cur,init;
    double VelocityCorrelation = 0;
    for (int ii = 0; ii < N; ++ii)
        {
        cur = fVel.data[ii];
        init = iVel[ii];
        VelocityCorrelation += dot(cur,init);
        }
    return VelocityCorrelation/N;
    };

// This correlation between the velocity of the cage and the cell
double dynamicalFeatures::computeCageRelativeVelocityCorrelation(GPUArray<double2> &currentVel)
    {
    currentCageVelocity.resize(N);
    ArrayHandle<double2> fVel(currentVel,access_location::host,access_mode::read);
    double2 cur;
    double2 temp;
    double cageRelativeVelocityCorrelation = 0;
    for(int ii = 0; ii < N; ++ii)
        {
        //self term
        cur = fVel.data[ii];
        //subtract off net neighbor motion
        int nNeighs = cageNeighbors[ii].size();
        temp.x=0;temp.y=0;
        for(int nn = 0; nn < nNeighs; ++nn)
            {
            int neighborIndex = cageNeighbors[ii][nn];
            temp.x = temp.x + fVel.data[neighborIndex].x / nNeighs;
            temp.y = temp.y + fVel.data[neighborIndex].y / nNeighs;
            }
        cageRelativeVelocityCorrelation += dot(cur,temp);
        };
    return cageRelativeVelocityCorrelation/N;
    };



double dynamicalFeatures::MSDhelper(vector<double2> &displacements)
    {
    double2 disp;
    double msd = 0.0;
    for (int ii = 0; ii < N; ++ii)
        {
        disp = displacements[ii];
        msd += dot(disp,disp);
        };
    msd = msd / N;
    return msd;
    };

double dynamicalFeatures::computeMSD(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox)
    {
    //call helper function to compute vector of current displacements
    computeTrueDisplacements(currentPos, previousPos, previousWhichBox);
    double result = MSDhelper(currentDisplacements);
    return result;
    };

double dynamicalFeatures::computeCageRelativeMSD(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox)
    {
    //call helper function to compute the vector of current cage-relative displacement vectors
    computeCageRelativeTrueDisplacements(currentPos,previousPos, previousWhichBox);

    //then just compute the MSD of that set of vectors..
    double result = MSDhelper(cageRelativeDisplacements);
    return result;
    };

double dynamicalFeatures::computeCageMSD(GPUArray<double2> &currentPos)
    {
    //call helper function to compute the vector of current cage-relative displacement vectors
    computeCageRelativeDisplacements(currentPos);

    //then just compute the MSD of that set of vectors..
    double result = MSDhelper(cageDisplacements);
    return result;
    };

double dynamicalFeatures::computeCageEnhancedMSD(GPUArray<double2> &currentPos)
    {
    //call helper function to compute the vector of current cage-relative displacement vectors
    computeCageRelativeDisplacements(currentPos);

    //then just compute the MSD of that set of vectors..
    double result = MSDhelper(cageEnhancedDisplacements);
    return result;
    };


/*!
In d-dimensions, the contribution of the angularly average of <exp(I k.r)> is
(Power(2,-1 + n/2.)*(-(k*r*BesselJ(1 + n/2.,k*r)) + n*BesselJ(n/2.,k*r))*Gamma(n/2.))/
   Power(k*r,n/2.)
See: THE DEBYE SCATTERING FORMULA IN n DIMENSION, Wieder, J. Math. Comput. Sci. 2 (2012), No. 4, 1086-1090
*/
double dynamicalFeatures::angularAverageSISF(vector<double2> &displacements, double k)
    {
    double2 disp;
    double sisfContribution = 0.0;
    double kr;
    for (int ii = 0; ii < N; ++ii)
        {
        disp = displacements[ii];
        kr = k*sqrt(dot(disp,disp));
        sisfContribution += std::cyl_bessel_j((double) 0.0, (double) kr);
        };
    sisfContribution = sisfContribution / N;
    return sisfContribution;
    };

double dynamicalFeatures::computeSISF(GPUArray<double2> &currentPos, double k)
    {
    //call helper function to compute the vector of current cage-relative displacement vectors
    computeDisplacements(currentPos);

    //then just compute the MSD of that set of vectors..
    double result = angularAverageSISF(currentDisplacements,k);
    return result;
    };
/*
 Just compute cage relative displacements and pass that vector to the helper function
 */
double dynamicalFeatures::computeCageRelativeSISF(GPUArray<double2> &currentPos, double k)
    {
    //call helper function to compute the vector of current cage-relative displacement vectors
    computeCageRelativeDisplacements(currentPos);

    //then just compute the MSD of that set of vectors..
    double result = angularAverageSISF(cageRelativeDisplacements,k);
    return result;
    };

/*!
returns <F_s^2(q,t)> for a set of displacements
*/
double dynamicalFeatures::chi4Helper(vector<double2> &displacements, double k)
    {
    double2 disp,disp2,totalDisp, relativeDisp;
    double kr;

    double chi4Contribution = 0.0;
    //self contribution
    chi4Contribution = 1.0*N;
    //relative contributions
    for(int ii = 0; ii < N-1; ++ii)
        {
        disp = displacements[ii];
        for (int jj = ii+1; jj < N; ++jj)
            {
            disp2 = displacements[jj];
            relativeDisp.x=disp.x-disp2.x;
            relativeDisp.y=disp.y-disp2.y;
            kr = k*sqrt(dot(relativeDisp,relativeDisp));
            chi4Contribution += 2*std::cyl_bessel_j((double) 0.0, (double) kr);
            };
        }

    return (chi4Contribution / (N*N));
    }

/*!
returns <Q(t)^2> for a set of displacements
*/
double dynamicalFeatures::overlapChi4Helper(vector<double2> &displacements, double cutoff)
    {
    double2 disp,disp2;
    double chi4Contribution = 0.0;
    //self contribution
    for (int ii = 0; ii < N; ++ii)
        {
        disp = displacements[ii];
        if(norm(disp) < cutoff)
            chi4Contribution += 1;
        };
    //relative contributions
    for(int ii = 0; ii < N-1; ++ii)
        {
        disp = displacements[ii];
        for (int jj = ii+1; jj < N; ++jj)
            {
            disp2 = displacements[jj];
            if(norm(disp) < cutoff&&norm(disp2) < cutoff)
                chi4Contribution += 2;
            };
        };

    return (chi4Contribution / (N*N));
    }


double2 dynamicalFeatures::computeFsChi4(GPUArray<double2> &currentPos, double k)
    {
    double2 ans; ans.x=0;ans.y=0;
    double meanFs= computeSISF(currentPos,k);
    double fsSquared = chi4Helper(currentDisplacements,k);

    ans.x=meanFs;
    ans.y=N*(fsSquared - meanFs*meanFs);
    return ans;
    };

double2 dynamicalFeatures::computeCageRelativeFsChi4(GPUArray<double2> &currentPos, double k)
    {
    double2 ans; ans.x=0;ans.y=0;
    double meanFs= computeCageRelativeSISF(currentPos,k);

    double fsSquared = chi4Helper(cageRelativeDisplacements,k);
    ans.x=meanFs;
    ans.y=N*(fsSquared - meanFs*meanFs);
    return ans;

    };

double dynamicalFeatures::computeCageRelativeMobilityCorrelation(GPUArray<double2> &currentPos)
    {
    double2 disp,disp2;
    double correlation = 0.0;
    double2 averageDisplacement;
    averageDisplacement.x=0.0; 
    averageDisplacement.y=0.0;
    computeCageRelativeDisplacements(currentPos);
    //self contribution
    for (int ii = 0; ii < N; ++ii)
        {
        disp = cageRelativeDisplacements[ii];
        correlation += dot(disp,disp);
        averageDisplacement.x += disp.x; 
        averageDisplacement.y += disp.y;
        };
    //relative contributions
    for(int ii = 0; ii < N-1; ++ii)
        {
        disp = cageRelativeDisplacements[ii];
        for (int jj = ii+1; jj < N; ++jj)
            {
            disp2 = cageRelativeDisplacements[jj];
            correlation += 2 * dot(disp2,disp);
        };
        }

    return (correlation/N);
    }

double2 dynamicalFeatures::computeCageRelativeOverlapChi4(GPUArray<double2> &currentPos, double cutoff)
    {
    double2 ans; ans.x=0;ans.y=0;
    double meanOverlap= computeCageRelativeOverlapFunction(currentPos,cutoff);

    double overlapSquared = overlapChi4Helper(cageRelativeDisplacements,cutoff);
    ans.x=meanOverlap;
    ans.y=N*(overlapSquared - meanOverlap*meanOverlap);
    return ans;

    };


double2 dynamicalFeatures::computeOrientationalCorrelationFunction(GPUArray<double2> &currentPos,GPUArray<int> &currentNeighbors, GPUArray<int> &currentNeighborNum, Index2D n_idx, int n)
    {
    double2 ans; ans.x=0; ans.y=0;

    double2 disp,p1,p2;
    int neighborIndex;
    double theta;
    if(!initialBondOrderComputed)
        {
        initialBondOrderComputed = true;
        initialConjugateBondOrder.resize(currentPos.getNumElements());

        for(int ii = 0; ii < N; ++ii)
            {
            double2 localPsi; localPsi.x=0;localPsi.y=0;
            int neighs = cageNeighbors[ii].size();
            p1 = iPos[ii];
            for (int nn = 0; nn < neighs; ++nn)
                {
                neighborIndex = cageNeighbors[ii][nn];
                p2 = iPos[neighborIndex];
                Box->minDist(p2,p1,disp);
                theta = atan2(disp.y,disp.x);
                localPsi.x += cos(n*theta)/neighs;
                localPsi.y += sin(n*theta)/neighs;
                };
            initialConjugateBondOrder[ii].x = localPsi.x;
            initialConjugateBondOrder[ii].y = localPsi.y;
            }
        };

    ArrayHandle<int> h_nn(currentNeighborNum,access_location::host,access_mode::read);
    ArrayHandle<int> h_n(currentNeighbors,access_location::host,access_mode::read);
    ArrayHandle<double2> h_p(currentPos,access_location::host,access_mode::read);

    for(int ii = 0; ii < N; ++ii)
        {
        double2 localPsi; localPsi.x=0;localPsi.y=0;
        int neighs = h_nn.data[ii];
        p1 = h_p.data[ii];
        for (int nn = 0; nn < neighs; ++nn)
            {
            neighborIndex = h_n.data[n_idx(nn,ii)];
            p2 = h_p.data[neighborIndex];
            Box->minDist(p2,p1,disp);
            theta = atan2(disp.y,disp.x);
            localPsi.x += cos(n*theta)/neighs;
            localPsi.y += sin(n*theta)/neighs;
            }
        ans.x+= localPsi.x*initialConjugateBondOrder[ii].x+localPsi.y*initialConjugateBondOrder[ii].y;
        ans.y+= localPsi.y*initialConjugateBondOrder[ii].x - localPsi.x*initialConjugateBondOrder[ii].y;
        };

    return ans;
    };


double dynamicalFeatures::computeOverlapFunction(GPUArray<double2> &currentPos, double cutoff)
    {
    double overlap = 0.0;
    ArrayHandle<double2> fPos(currentPos,access_location::host,access_mode::read);
    double2 disp,cur,init;
    for (int ii = 0; ii < N; ++ii)
        {
        cur = fPos.data[ii];
        init = iPos[ii];
        Box->minDist(cur,init,disp);
        if(norm(disp) < cutoff)
            overlap += 1;
        };
    overlap = overlap / N;
    return overlap;
    }

double dynamicalFeatures::computeCageRelativeOverlapFunction(GPUArray<double2> &currentPos, double cutoff)
    {
    double overlap = 0.0;
    computeCageRelativeDisplacements(currentPos);
    for (int ii = 0; ii < N; ++ii)
        {
        if(norm(cageRelativeDisplacements[ii]) < cutoff)
            overlap += 1;
        };
    overlap = overlap / N;
    return overlap;
    }

double dynamicalFeatures::computeNeighborOverlapFunction(GPUArray<int> &neighbors, GPUArray<int> &neighborNum, Index2D n_idx)
    {
    nIdx = Index2D(n_idx.getW(),n_idx.getH());
    ArrayHandle<int> h_nn(neighborNum,access_location::host,access_mode::read);
    ArrayHandle<int> h_n(neighbors,access_location::host,access_mode::read);
    double overlap = 0.0;

    for (int ii = 0; ii < N; ++ii)
        {
            int neighs = h_nn.data[ii];
            vector<int> ns(neighs);
            for (int nn = 0; nn < neighs; ++nn)
            {
                ns[nn]=h_n.data[nIdx(nn,ii)];
            };
            unordered_set<int> set;
            int commomNeighbor=0;

            for (int num : ns)
            {
                set.insert(num);
            }
            for (int num : cageNeighbors[ii]) 
            {
            // If element is present in set, it's common
                if (set.find(num) != set.end())
                {
                    commomNeighbor++;
                }
            }

            overlap += commomNeighbor/neighs;
        }

        overlap = overlap / N;
        return overlap;
    }