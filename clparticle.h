#ifndef CLPARTICLE_H
#define CLPARTICLE_H

#include <String>
#include <Qstring>
#include <vector>


#include <vtkActor.h>
#include <vtkSmartPointer.h>

class vtkActor;

class clParticle
{
public:
    clParticle();
    clParticle( std::vector<std::string> vecStr );
    clParticle(const std::string& str_ID,
               double x,
               double y,
               double z,
               double vx,
               double vy,
               double vz,
               double mass
               );

    const std::string getStr();

    std::string getID() const { return m_strID; }
    void setID( std::string val ){ m_strID = val; }
    //void setID( QString val ) { m_strID = val.toStdString() ;}

    double getX() const { return m_dX; }
    void setX( double val){ m_dX = val; }
    double getY() const { return m_dY; }
    void setY( double val){ m_dY = val; }
    double getZ() const { return m_dZ; }
    void setZ( double val){ m_dZ = val; }
    double getVX() const { return m_dVX; }
    void setVX( double val){ m_dVX = val; }
    double getVY() const { return m_dVY; }
    void setVY( double val){ m_dVY = val; }
    double getVZ() const { return m_dVZ; }
    void setVZ( double val){ m_dVZ = val; }

    double getMass() { return m_dMass; }
    void setMass( double val ){ m_dMass = val; }

    // Energy budget methods
    // NOTE: PE must be set in regards to particle collection
    void calcKE();
    void setKE( double val ){ m_dKineticEnegy = val; }
    double getKE() const { return m_dKineticEnegy; }
    void setPE( double val){ m_dPotentialEnergy = val; }
    double getPE() const { return m_dPotentialEnergy; }

    void setActor( vtkSmartPointer<vtkActor> actor) { m_vtkActor = actor; }
    vtkSmartPointer<vtkActor> getActor() const { return m_vtkActor; }
    void updateActor();

private:

    std::string m_strID;

    double m_dX;
    double m_dY;
    double m_dZ;
    double m_dVX;
    double m_dVY;
    double m_dVZ;

    double m_dMass;

    double m_dKineticEnegy;
    double m_dPotentialEnergy;

    vtkSmartPointer<vtkActor> m_vtkActor;
};

#endif // CLPARTICLE_H
