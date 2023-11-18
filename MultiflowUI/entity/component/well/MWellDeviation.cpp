#include "mwelldeviation.hpp"
#include <QUuid>

MWellDeviation::MWellDeviation() {
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

MWellDeviation::MWellDeviation(
    double measurePointMD, double measurePointTVD, double inclination, double azimuth,
    double displacementEW, double displacementNS, double dogleg, double closureHorizon,
    double closureAzimuth, double closureDispl)
    : measurePointMD(measurePointMD),
      measurePointTVD(measurePointTVD),
      inclination(inclination),
      azimuth(azimuth),
      displacementEW(displacementEW),
      displacementNS(displacementNS),
      dogleg(dogleg),
      closureHorizon(closureHorizon),
      closureAzimuth(closureAzimuth),
      closureDispl(closureDispl) {
}

QString MWellDeviation::getId() const {
    return id;
}

void MWellDeviation::setId(const QString& newId) {
    id = newId;
}

QString MWellDeviation::getWellId() const {
    return wellId;
}

void MWellDeviation::setWellId(const QString& newWellId) {
    wellId = newWellId;
}

double MWellDeviation::getMeasurePointMD() const {
    return measurePointMD;
}

void MWellDeviation::setMeasurePointMD(double newMeasurePointMD) {
    measurePointMD = newMeasurePointMD;
}

double MWellDeviation::getMeasurePointTVD() const {
    return measurePointTVD;
}

void MWellDeviation::setMeasurePointTVD(double newMeasurePointTVD) {
    measurePointTVD = newMeasurePointTVD;
}

double MWellDeviation::getInclination() const {
    return inclination;
}

void MWellDeviation::setInclination(double newInclination) {
    inclination = newInclination;
}

double MWellDeviation::getAzimuth() const {
    return azimuth;
}

void MWellDeviation::setAzimuth(double newAzimuth) {
    azimuth = newAzimuth;
}

double MWellDeviation::getDisplacementEW() const {
    return displacementEW;
}

void MWellDeviation::setDisplacementEW(double newDisplacementEW) {
    displacementEW = newDisplacementEW;
}

double MWellDeviation::getDisplacementNS() const {
    return displacementNS;
}

void MWellDeviation::setDisplacementNS(double newDisplacementNS) {
    displacementNS = newDisplacementNS;
}

double MWellDeviation::getDogleg() const {
    return dogleg;
}

void MWellDeviation::setDogleg(double newDogleg) {
    dogleg = newDogleg;
}

double MWellDeviation::getClosureHorizon() const {
    return closureHorizon;
}

void MWellDeviation::setClosureHorizon(double newClosureHorizon) {
    closureHorizon = newClosureHorizon;
}

double MWellDeviation::getClosureAzimuth() const {
    return closureAzimuth;
}

void MWellDeviation::setClosureAzimuth(double newClosureAzimuth) {
    closureAzimuth = newClosureAzimuth;
}

double MWellDeviation::getClosureDispl() const {
    return closureDispl;
}

void MWellDeviation::setClosureDispl(double newClosureDispl) {
    closureDispl = newClosureDispl;
}

QString MWellDeviation::getRemark() const {
    return remark;
}

void MWellDeviation::setRemark(const QString& newRemark) {
    remark = newRemark;
}

double MWellDeviation::getWellHeadDpeth() const {
    return wellHeadDpeth;
}

void MWellDeviation::setWellHeadDpeth(double newWellHeadDpeth) {
    wellHeadDpeth = newWellHeadDpeth;
}

MWellDeviation::SurveyType MWellDeviation::getSurVeytype() const {
    return surVeytype;
}

void MWellDeviation::setSurVeytype(SurveyType newSurVeytype) {
    surVeytype = newSurVeytype;
}

MWellDeviation::DependentPara MWellDeviation::getDepType() const {
    return depType;
}

void MWellDeviation::setDepType(DependentPara newDepType) {
    depType = newDepType;
}

double MWellDeviation::getBottomDepth() const {
    return bottomDepth;
}

void MWellDeviation::setBottomDepth(double newBottomDepth) {
    bottomDepth = newBottomDepth;
}

QString MWellDeviation::getCalMedthod() const {
    return calMedthod;
}

void MWellDeviation::setCalMedthod(const QString& newCalMedthod) {
    calMedthod = newCalMedthod;
}
