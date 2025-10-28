#ifndef CLDATASET_H
#define CLDATASET_H

#include <vector>
#include "clparticle.h"

class clDataset
{
public:
    clDataset();

    void reset();

    void calcTotalMass();
    double getTotalMass(){ return m_dTotalMass; }
    void setTotalMass( double val ) { m_dTotalMass = val; }

    void loadCSV( const std::string& filename );
    void saveCSV( const std::string& filename );
    bool validLine( std::vector<std::string> vecStr );

    double getKE(){ return m_dTotalKineticEnergy; }
    void setTotalKE( double val ){ m_dTotalKineticEnergy = val; }
    void calcKE();
    double getPE(){ return m_dTotalPotentialEnergy; }
    void setTotalPE( double val ){ m_dTotalPotentialEnergy = val; }
    void calcPE();

private:
    std::vector<clParticle> m_vecParticles;
    double m_dTotalMass;
    double m_dTotalKineticEnergy;
    double m_dTotalPotentialEnergy;
};

#endif // CLDATASET_H
