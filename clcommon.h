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

    double getCurrentTime(){ return M_CURRENTTIME; }
    void setCurrentTime( double val ){ M_CURRENTTIME = val; }
    void stepTime(bool bForward );

    std::string getFilename(){ return M_FILENAME; }
    void setFilename( std::string val ){ M_FILENAME = val; }

private:
    clDataset M_DATASET;
    std::string M_FILENAME;
    double M_TIMESTEP;
    double M_CURRENTTIME;
};

#endif // CLCOMMON_H
