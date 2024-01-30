#ifndef logWritter_SAC_H
#define logWritter_SAC_H

#include "BaseDatabase.h"
#include "analysisPackage.h"
#include "autocorrelator.h"
#include "twoValuesDatabase.h"

//! Handles the logic of saving log-spaced data files that might begin at different offset times
// This is for saving stress autocorrelation functions instead of state
class logSACWritter
    {
    private:
        typedef shared_ptr<Simple2DCell> STATE;

    public:
        logSACWritter(){};
        void addDatabase(shared_ptr<twoValuesDatabase> db, shared_ptr<autocorrelator> ac, int firstFrameToSave, long long int limit);
        void addData(double stress, long long int frame);
        void writeSAC();

        long long int uplimit;
        vector<shared_ptr<twoValuesDatabase>> databases;
        vector<shared_ptr<autocorrelator>> SACs;
        vector<int> saveOffsets;

    };
#endif
