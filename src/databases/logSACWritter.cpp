#include "logSACWritter.h"


void logSACWritter::addDatabase(shared_ptr<twoValuesDatabase> db, shared_ptr<autocorrelator> ac, int firstFrameToSave)
    {
    SACs.push_back(ac);
    databases.push_back(db);
    saveOffsets.push_back(firstFrameToSave);
    }


void logSACWritter::addData(double stress, long long int frame)
    {
    for (int ii = 0; ii < databases.size(); ++ii)
        {
//            cout << frame << "\t" << ii << endl;
        if(frame > saveOffsets[ii])
            {
                SACs[ii]->add(stress,0);
            }
//            cout << frame << "\t" << ii << "\t"<<nextFrames[ii] << endl;
        }
        
    }

void logSACWritter::writeSAC()
    {
    for (int ii = 0; ii < databases.size(); ++ii)
        {
        SACs[ii]->evaluate(false);
        for(int j = 0; j < SACs[ii]->correlator.size(); ++j)
            {
            databases[ii]->writeValues(SACs[ii]->correlator[j].y,SACs[ii]->correlator[j].x);
            }
        }
    }

