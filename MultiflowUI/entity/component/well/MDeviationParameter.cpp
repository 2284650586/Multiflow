#include "MDeviationParameter.hpp"

MDeviationParameter::MDeviationParameter() {
}

double MDeviationParameter::getMD() const {
    return MD;
}

void MDeviationParameter::setMD(double newMD) {
    MD = newMD;
}

double MDeviationParameter::getTVD() const {
    return TVD;
}

void MDeviationParameter::setTVD(double newTVD) {
    TVD = newTVD;
}

double MDeviationParameter::getHorizontalDisplacement() const {
    return horizontalDisplacement;
}

void MDeviationParameter::setHorizontalDisplacement(double newHorizontalDisplacement) {
    horizontalDisplacement = newHorizontalDisplacement;
}

double MDeviationParameter::getAngle() const {
    return angle;
}

void MDeviationParameter::setAngle(double newAngle) {
    angle = newAngle;
}

double MDeviationParameter::getAzimuth() const {
    return azimuth;
}

void MDeviationParameter::setAzimuth(double newAzimuth) {
    azimuth = newAzimuth;
}

double MDeviationParameter::getMaxDog() const {
    return maxDog;
}

void MDeviationParameter::setMaxDog(double newMaxDog) {
    maxDog = newMaxDog;
}

MDeviationParameter::MDeviationParameter(double MD, double TVD, double horizontalDisplacement, double angle,
                                         double azimuth, double maxDog) : MD(MD),
                                                                          TVD(TVD),
                                                                          horizontalDisplacement(
                                                                              horizontalDisplacement),
                                                                          angle(angle),
                                                                          azimuth(azimuth),
                                                                          maxDog(maxDog) {
}
