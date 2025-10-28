#ifndef CLCOMMON_H
#define CLCOMMON_H

#include "cldataset.h"

class clCommon
{
public:
    clCommon();

    clDataset* Data() { return &M_DATASET; }
    double getTimeStep(){ return M_TIMESTEP; }
    void setTimeStep( double val ){ M_TIMESTEP = val; }

private:
    clDataset M_DATASET;
    double M_TIMESTEP;
};

#endif // CLCOMMON_H
