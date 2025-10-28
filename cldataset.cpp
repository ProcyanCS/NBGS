#include "cldataset.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


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
        std::cout << std::to_string(it->getMass()) << std::endl;
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

