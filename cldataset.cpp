#include "cldataset.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <constants.h>


clDataset::clDataset()
{
    setTotalKE(0.0);
    setTotalPE(0.0);
    setTotalMass(0.0);
}

void clDataset::reset()
{
    setTotalKE(0.0);
    setTotalPE(0.0);
    setTotalMass(0.0);
    this->m_vecParticles.clear();
}

void clDataset::update( double timestep )
{
    calcTotalMass();
    std::tuple<double, double, double> tup_COM = getWeightedCOM();

    calcNewVelocity( tup_COM, timestep );
    calcNewPosition( timestep );

}

void clDataset::calcNewVelocity(
    std::tuple<double, double, double> tup_COM , double timestep)
{
    for (auto& p : Particles() )
    {
        double dMassOutside = getTotalMass() - p.getMass();
        // TODO: SAFEGUARD a dominating particle mass to prevent
        // undefined behavior.

        double dVCM_X = (std::get<0>(tup_COM) - p.getMass() * p.getX()) /
                            dMassOutside - p.getMass() * p.getX();
        double dVCM_Y = (std::get<1>(tup_COM) - p.getMass() * p.getY()) /
                            dMassOutside - p.getMass() * p.getY();
        double dVCM_Z = (std::get<2>(tup_COM) - p.getMass() * p.getZ()) /
                            dMassOutside - p.getMass() * p.getZ();
        double dR = sqrt(pow(dVCM_X,2) +
                         pow(dVCM_Y,2) +
                         pow(dVCM_Z,2) );

        double dA = 0.0;
        if ( fabs(dR) > ERR_TOL)
            dA = dMassOutside * CONST_GRAV / dR;

        double dVX_new = p.getVX() + dA * dVCM_X * timestep;
        double dVY_new = p.getVY() + dA * dVCM_Y * timestep;
        double dVZ_new = p.getVZ() + dA * dVCM_Z * timestep;

        p.setVX( dVX_new );
        p.setVY( dVY_new );
        p.setVZ( dVZ_new );
    }
}

void clDataset::calcNewPosition( double timestep )
{
    for (auto& p : Particles())
    {
        double dX_new = p.getX() + p.getVX()*timestep;
        double dY_new = p.getY() + p.getVY()*timestep;
        double dZ_new = p.getZ() + p.getVZ()*timestep;

        p.setX( dX_new );
        p.setY( dY_new );
        p.setZ( dZ_new );

    }
}


std::tuple<double, double, double> clDataset::getWeightedCOM()
{
    double dI = 0.0;
    double dJ = 0.0;
    double dK = 0.0;

    for (auto p : Particles() )
    {
        dI += p.getMass() * p.getX();
        dJ += p.getMass() * p.getY();
        dK += p.getMass() * p.getZ();
    }
    std::tuple<double, double, double> tup =
        std::make_tuple(dI, dJ, dK);
    return tup;
}

bool clDataset::validLine( std::vector<std::string> vecStr )
{
    // Invalid number of fields
    if ((vecStr.size() < 8) || (vecStr.size() > 9))
        return false;

    // Comment line
    if (vecStr[0].rfind("#",0) == 0)
        return false;

    // Invalid mass supplied
    double mass = std::stod( vecStr[7] );
    if ( mass <= 0.0)
        return false;

    return true;
}

void clDataset::loadCSV( const std::string& filename )
{
    std::ifstream fp(filename);
    std::string line, cell;
    uint uLineNumber = 0;

    while (std::getline(fp, line))
    {
        std::stringstream lineStream(line);
        std::vector<std::string> row;

        while (std::getline(lineStream, cell, ','))
        {
            row.push_back(cell);
        }

        if ( validLine( row ) )
        {
            clParticle particle = clParticle( row );
            //std::cout << particle.getStr() << std::endl;
            m_vecParticles.push_back(particle);
        }
        else
        {
            std::cout << "Skipping line " << std::to_string(uLineNumber)
                      << " in CSV file..." << std::endl;
        }
        uLineNumber++;

    }

}

void clDataset::saveCSV( const std::string &filename )
{
    std::ofstream fp(filename);

    // Write Header Comment Line
    fp << "# OBJECT_ID, X0, Y0, Z0, VX0, VY0, VZ0, MASS" << std::endl;;

    for (auto it = m_vecParticles.begin();
         it != m_vecParticles.end();
         it++)
    {
        fp << it->getStr() << std::endl;
    }



    fp.close();
}

void clDataset::calcTotalMass()
{
    double dTotalMass = 0.0;

    for (auto it = m_vecParticles.begin();
         it != m_vecParticles.end();
         it++)
    {
        //std::cout << std::to_string(it->getMass()) << std::endl;
        dTotalMass += it->getMass();
    }
    setTotalMass( dTotalMass );
}

void clDataset::calcKE()
{
    double dTotalKE = 0.0;

    for (auto it = m_vecParticles.begin();
         it != m_vecParticles.end();
         it++)
    {
        dTotalKE += it->getKE();
    }
    setTotalKE( dTotalKE );
}

void clDataset::calcPE()
{
    double dTotalPE = 0.0;

    for (auto it = m_vecParticles.begin();
         it != m_vecParticles.end();
         it++)
    {
        dTotalPE += it->getPE();
    }
    setTotalPE( dTotalPE );
}

