#include "clcommon.h"

clCommon::clCommon()
{
    M_DATASET = clDataset();
    M_TIMESTEP = 0.000001;
}

void clCommon::stepTime(bool bForward)
{
    if (bForward)
    {
        setCurrentTime(getCurrentTime() + getTimeStep());
        Data()->update( getTimeStep() );
    }
    else
    {
        setCurrentTime(getCurrentTime() - getTimeStep());
    }
}
