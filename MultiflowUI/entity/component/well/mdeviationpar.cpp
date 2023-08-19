#include "mdeviationpar.h"

MDeviationPar::MDeviationPar()
{

}

double MDeviationPar::getMD() const
{
    return MD;
}

void MDeviationPar::setMD(double newMD)
{
    MD = newMD;
}

double MDeviationPar::getTVD() const
{
    return TVD;
}

void MDeviationPar::setTVD(double newTVD)
{
    TVD = newTVD;
}

double MDeviationPar::getHorizontalDisplacement() const
{
    return horizontalDisplacement;
}

void MDeviationPar::setHorizontalDisplacement(double newHorizontalDisplacement)
{
    horizontalDisplacement = newHorizontalDisplacement;
}

double MDeviationPar::getAngle() const
{
    return angle;
}

void MDeviationPar::setAngle(double newAngle)
{
    angle = newAngle;
}

double MDeviationPar::getAzimuth() const
{
    return azimuth;
}

void MDeviationPar::setAzimuth(double newAzimuth)
{
    azimuth = newAzimuth;
}

double MDeviationPar::getMaxDog() const
{
    return maxDog;
}

void MDeviationPar::setMaxDog(double newMaxDog)
{
    maxDog = newMaxDog;
}

MDeviationPar::MDeviationPar(double MD, double TVD, double horizontalDisplacement, double angle, double azimuth, double maxDog) : MD(MD),
    TVD(TVD),
    horizontalDisplacement(horizontalDisplacement),
    angle(angle),
    azimuth(azimuth),
    maxDog(maxDog)
{}
