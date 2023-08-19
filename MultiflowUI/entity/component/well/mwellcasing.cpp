#include "mwellcasing.h"
#include <QUuid>

MWellCasing::MWellCasing()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MWellCasing::getId() const
{
    return id;
}

void MWellCasing::setId(const QString &newId)
{
    id = newId;
}

QString MWellCasing::getName() const
{
    return name;
}

void MWellCasing::setName(const QString &newName)
{
    name = newName;
}

double MWellCasing::getInnerDiameter() const
{
    return innerDiameter;
}

void MWellCasing::setInnerDiameter(double newInnerDiameter)
{
    innerDiameter = newInnerDiameter;
}

double MWellCasing::getOutDiameter() const
{
    return outDiameter;
}

void MWellCasing::setOutDiameter(double newOutDiameter)
{
    outDiameter = newOutDiameter;
}

QString MWellCasing::getMaterialId() const
{
    return materialId;
}

void MWellCasing::setMaterialId(const QString &newMaterialId)
{
    materialId = newMaterialId;
}

QString MWellCasing::getGrade() const
{
    return grade;
}

void MWellCasing::setGrade(const QString &newGrade)
{
    grade = newGrade;
}

double MWellCasing::getPerLengthWeight() const
{
    return perLengthWeight;
}

void MWellCasing::setPerLengthWeight(double newPerLengthWeight)
{
    perLengthWeight = newPerLengthWeight;
}

QString MWellCasing::getEndFace() const
{
    return endFace;
}

void MWellCasing::setEndFace(const QString &newEndFace)
{
    endFace = newEndFace;
}

double MWellCasing::getDensity() const
{
    return density;
}

void MWellCasing::setDensity(double newDensity)
{
    density = newDensity;
}

double MWellCasing::getAdjPerLengthWeight() const
{
    return adjPerLengthWeight;
}

void MWellCasing::setAdjPerLengthWeight(double newAdjPerLengthWeight)
{
    adjPerLengthWeight = newAdjPerLengthWeight;
}

double MWellCasing::getJointOutDiameter() const
{
    return jointOutDiameter;
}

void MWellCasing::setJointOutDiameter(double newJointOutDiameter)
{
    jointOutDiameter = newJointOutDiameter;
}

double MWellCasing::getJointInnerDiameter() const
{
    return jointInnerDiameter;
}

void MWellCasing::setJointInnerDiameter(double newJointInnerDiameter)
{
    jointInnerDiameter = newJointInnerDiameter;
}

double MWellCasing::getJointTensile() const
{
    return jointTensile;
}

void MWellCasing::setJointTensile(double newJointTensile)
{
    jointTensile = newJointTensile;
}

double MWellCasing::getNoumenonTensile() const
{
    return noumenonTensile;
}

void MWellCasing::setNoumenonTensile(double newNoumenonTensile)
{
    noumenonTensile = newNoumenonTensile;
}

double MWellCasing::getBuckleTorque() const
{
    return buckleTorque;
}

void MWellCasing::setBuckleTorque(double newBuckleTorque)
{
    buckleTorque = newBuckleTorque;
}

int MWellCasing::getElasticModulus() const
{
    return elasticModulus;
}

void MWellCasing::setElasticModulus(int newElasticModulus)
{
    elasticModulus = newElasticModulus;
}

double MWellCasing::getWallThickness() const
{
    return wallThickness;
}

void MWellCasing::setWallThickness(double newWallThickness)
{
    wallThickness = newWallThickness;
}

double MWellCasing::getCollapsePressure() const
{
    return collapsePressure;
}

void MWellCasing::setCollapsePressure(double newCollapsePressure)
{
    collapsePressure = newCollapsePressure;
}

double MWellCasing::getMaxCTorque() const
{
    return maxCTorque;
}

void MWellCasing::setMaxCTorque(double newMaxCTorque)
{
    maxCTorque = newMaxCTorque;
}

double MWellCasing::getBurstPressure() const
{
    return burstPressure;
}

void MWellCasing::setBurstPressure(double newBurstPressure)
{
    burstPressure = newBurstPressure;
}

double MWellCasing::getMaxTensile() const
{
    return maxTensile;
}

void MWellCasing::setMaxTensile(double newMaxTensile)
{
    maxTensile = newMaxTensile;
}

double MWellCasing::getDriftDiameter() const
{
    return driftDiameter;
}

void MWellCasing::setDriftDiameter(double newDriftDiameter)
{
    driftDiameter = newDriftDiameter;
}

double MWellCasing::getSafetyFactor() const
{
    return safetyFactor;
}

void MWellCasing::setSafetyFactor(double newSafetyFactor)
{
    safetyFactor = newSafetyFactor;
}

QString MWellCasing::getFactory() const
{
    return factory;
}

void MWellCasing::setFactory(const QString &newFactory)
{
    factory = newFactory;
}

QString MWellCasing::getModel() const
{
    return model;
}

void MWellCasing::setModel(const QString &newModel)
{
    model = newModel;
}

QString MWellCasing::getSn() const
{
    return sn;
}

void MWellCasing::setSn(const QString &newSn)
{
    sn = newSn;
}

QDateTime MWellCasing::getCreateDate() const
{
    return createDate;
}

void MWellCasing::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}

QString MWellCasing::getCreateUser() const
{
    return createUser;
}

void MWellCasing::setCreateUser(const QString &newCreateUser)
{
    createUser = newCreateUser;
}

QString MWellCasing::getDescription() const
{
    return description;
}

void MWellCasing::setDescription(const QString &newDescription)
{
    description = newDescription;
}

QDateTime MWellCasing::getUpdateDate() const
{
    return updateDate;
}

void MWellCasing::setUpdateDate(const QDateTime &newUpdateDate)
{
    updateDate = newUpdateDate;
}

QString MWellCasing::getUpdateUser() const
{
    return updateUser;
}

void MWellCasing::setUpdateUser(const QString &newUpdateUser)
{
    updateUser = newUpdateUser;
}

QByteArray MWellCasing::getIcon() const
{
    return icon;
}

void MWellCasing::setIcon(const QByteArray &newIcon)
{
    icon = newIcon;
}

double MWellCasing::getToMD() const
{
    return toMD;
}

void MWellCasing::setToMD(double newToMD)
{
    toMD = newToMD;
}

double MWellCasing::getRoughness() const
{
    return roughness;
}

void MWellCasing::setRoughness(double newRoughness)
{
    roughness = newRoughness;
}

double MWellCasing::getThermal() const
{
    return thermal;
}

void MWellCasing::setThermal(double newThermal)
{
    thermal = newThermal;
}

double MWellCasing::getCementTop() const
{
    return cementTop;
}

void MWellCasing::setCementTop(double newCementTop)
{
    cementTop = newCementTop;
}

double MWellCasing::getCementDensity() const
{
    return cementDensity;
}

void MWellCasing::setCementDensity(double newCementDensity)
{
    cementDensity = newCementDensity;
}

double MWellCasing::getCementTheramlCond() const
{
    return cementTheramlCond;
}

void MWellCasing::setCementTheramlCond(double newCementTheramlCond)
{
    cementTheramlCond = newCementTheramlCond;
}
