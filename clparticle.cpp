#include "clparticle.h"

clParticle::clParticle()
{
    setID("unknown");
    setX(0.0);
    setY(0.0);
    setZ(0.0);
    setVX(0.0);
    setVY(0.0);
    setVZ(0.0);
    setMass(0.0); // watch
}

clParticle::clParticle( std::vector<std::string> vecStr )
{
    setID(vecStr[0]);

    setX(std::stod( vecStr[1] ));
    setY(std::stod( vecStr[2] ));
    setZ(std::stod( vecStr[3] ));

    setVX(std::stod( vecStr[4] ));
    setVY(std::stod( vecStr[5] ));
    setVZ(std::stod( vecStr[6] ));

    setMass(std::stod( vecStr[7] ));
}

clParticle::clParticle(const std::string& str_ID,
                       double x, double y, double z,
                       double vx, double vy, double vz,
                       double mass)
    : m_strID(str_ID),
    m_dX(x), m_dY(y), m_dZ(z),
    m_dVX(vx), m_dVY(vy), m_dVZ(vz),
    m_dMass(mass)
{

}

std::string clParticle::getStr()
{
    std::string s = getID() + ", " +
                    std::to_string(getX()) + ", " +
                    std::to_string(getY()) + ", " +
                    std::to_string(getZ()) + ", " +
                    std::to_string(getVX()) + ", " +
                    std::to_string(getVY()) + ", " +
                    std::to_string(getVZ()) + ", " +
                    std::to_string(getMass());

    return s;

}
