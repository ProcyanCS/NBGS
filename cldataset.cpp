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

bool clDataset::validLine( std::vector<std::string> vecStr )
{
    if (vecStr.size() < 8)
        return false;

    double mass = std::stod( vecStr[7] );
    if ( mass <= 0.0)
        return false;

    return true;
}

void clDataset::loadCSV( std::string& filename )
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
        }
        else
        {
            std::cout << "Skipping line " << std::to_string(uLineNumber)
                      << " in CSV file..." << std::endl;
        }

    }

}

void clDataset::calcTotalMass()
{
    double dTotalMass = 0.0;

    for (auto it = m_vecParticles.begin();
         it != m_vecParticles.end();
         it++)
    {
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

