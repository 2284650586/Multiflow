#include "MWellCasingParameter.hpp"
#include <QUuid>

MWellCasingParameter::MWellCasingParameter() {
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MWellCasingParameter::getId() const {
    return id;
}

void MWellCasingParameter::setId(const QString& newId) {
    id = newId;
}

QString MWellCasingParameter::getName() const {
    return name;
}

void MWellCasingParameter::setName(const QString& newName) {
    name = newName;
}

double MWellCasingParameter::getInnerDiameter() const {
    return innerDiameter;
}

void MWellCasingParameter::setInnerDiameter(double newInnerDiameter) {
    innerDiameter = newInnerDiameter;
}

double MWellCasingParameter::getOutDiameter() const {
    return outDiameter;
}

void MWellCasingParameter::setOutDiameter(double newOutDiameter) {
    outDiameter = newOutDiameter;
}

QString MWellCasingParameter::getMaterialId() const {
    return materialId;
}

void MWellCasingParameter::setMaterialId(const QString& newMaterialId) {
    materialId = newMaterialId;
}

QString MWellCasingParameter::getGrade() const {
    return grade;
}

void MWellCasingParameter::setGrade(const QString& newGrade) {
    grade = newGrade;
}

double MWellCasingParameter::getPerLengthWeight() const {
    return perLengthWeight;
}

void MWellCasingParameter::setPerLengthWeight(double newPerLengthWeight) {
    perLengthWeight = newPerLengthWeight;
}

QString MWellCasingParameter::getEndFace() const {
    return endFace;
}

void MWellCasingParameter::setEndFace(const QString& newEndFace) {
    endFace = newEndFace;
}

double MWellCasingParameter::getDensity() const {
    return density;
}

void MWellCasingParameter::setDensity(double newDensity) {
    density = newDensity;
}

double MWellCasingParameter::getAdjPerLengthWeight() const {
    return adjPerLengthWeight;
}

void MWellCasingParameter::setAdjPerLengthWeight(double newAdjPerLengthWeight) {
    adjPerLengthWeight = newAdjPerLengthWeight;
}

double MWellCasingParameter::getJointOutDiameter() const {
    return jointOutDiameter;
}

void MWellCasingParameter::setJointOutDiameter(double newJointOutDiameter) {
    jointOutDiameter = newJointOutDiameter;
}

double MWellCasingParameter::getJointInnerDiameter() const {
    return jointInnerDiameter;
}

void MWellCasingParameter::setJointInnerDiameter(double newJointInnerDiameter) {
    jointInnerDiameter = newJointInnerDiameter;
}

double MWellCasingParameter::getJointTensile() const {
    return jointTensile;
}

void MWellCasingParameter::setJointTensile(double newJointTensile) {
    jointTensile = newJointTensile;
}

double MWellCasingParameter::getNoumenonTensile() const {
    return noumenonTensile;
}

void MWellCasingParameter::setNoumenonTensile(double newNoumenonTensile) {
    noumenonTensile = newNoumenonTensile;
}

double MWellCasingParameter::getBuckleTorque() const {
    return buckleTorque;
}

void MWellCasingParameter::setBuckleTorque(double newBuckleTorque) {
    buckleTorque = newBuckleTorque;
}

int MWellCasingParameter::getElasticModulus() const {
    return elasticModulus;
}

void MWellCasingParameter::setElasticModulus(int newElasticModulus) {
    elasticModulus = newElasticModulus;
}

double MWellCasingParameter::getWallThickness() const {
    return wallThickness;
}

void MWellCasingParameter::setWallThickness(double newWallThickness) {
    wallThickness = newWallThickness;
}

double MWellCasingParameter::getCollapsePressure() const {
    return collapsePressure;
}

void MWellCasingParameter::setCollapsePressure(double newCollapsePressure) {
    collapsePressure = newCollapsePressure;
}

double MWellCasingParameter::getMaxCTorque() const {
    return maxCTorque;
}

void MWellCasingParameter::setMaxCTorque(double newMaxCTorque) {
    maxCTorque = newMaxCTorque;
}

double MWellCasingParameter::getBurstPressure() const {
    return burstPressure;
}

void MWellCasingParameter::setBurstPressure(double newBurstPressure) {
    burstPressure = newBurstPressure;
}

double MWellCasingParameter::getMaxTensile() const {
    return maxTensile;
}

void MWellCasingParameter::setMaxTensile(double newMaxTensile) {
    maxTensile = newMaxTensile;
}

double MWellCasingParameter::getDriftDiameter() const {
    return driftDiameter;
}

void MWellCasingParameter::setDriftDiameter(double newDriftDiameter) {
    driftDiameter = newDriftDiameter;
}

double MWellCasingParameter::getSafetyFactor() const {
    return safetyFactor;
}

void MWellCasingParameter::setSafetyFactor(double newSafetyFactor) {
    safetyFactor = newSafetyFactor;
}

QString MWellCasingParameter::getFactory() const {
    return factory;
}

void MWellCasingParameter::setFactory(const QString& newFactory) {
    factory = newFactory;
}

QString MWellCasingParameter::getModel() const {
    return model;
}

void MWellCasingParameter::setModel(const QString& newModel) {
    model = newModel;
}

QString MWellCasingParameter::getSn() const {
    return sn;
}

void MWellCasingParameter::setSn(const QString& newSn) {
    sn = newSn;
}

QDateTime MWellCasingParameter::getCreateDate() const {
    return createDate;
}

void MWellCasingParameter::setCreateDate(const QDateTime& newCreateDate) {
    createDate = newCreateDate;
}

QString MWellCasingParameter::getCreateUser() const {
    return createUser;
}

void MWellCasingParameter::setCreateUser(const QString& newCreateUser) {
    createUser = newCreateUser;
}

QString MWellCasingParameter::getDescription() const {
    return description;
}

void MWellCasingParameter::setDescription(const QString& newDescription) {
    description = newDescription;
}

QDateTime MWellCasingParameter::getUpdateDate() const {
    return updateDate;
}

void MWellCasingParameter::setUpdateDate(const QDateTime& newUpdateDate) {
    updateDate = newUpdateDate;
}

QString MWellCasingParameter::getUpdateUser() const {
    return updateUser;
}

void MWellCasingParameter::setUpdateUser(const QString& newUpdateUser) {
    updateUser = newUpdateUser;
}

QByteArray MWellCasingParameter::getIcon() const {
    return icon;
}

void MWellCasingParameter::setIcon(const QByteArray& newIcon) {
    icon = newIcon;
}

double MWellCasingParameter::getToMD() const {
    return toMD;
}

void MWellCasingParameter::setToMD(double newToMD) {
    toMD = newToMD;
}

double MWellCasingParameter::getRoughness() const {
    return roughness;
}

void MWellCasingParameter::setRoughness(double newRoughness) {
    roughness = newRoughness;
}

double MWellCasingParameter::getThermal() const {
    return thermal;
}

void MWellCasingParameter::setThermal(double newThermal) {
    thermal = newThermal;
}

double MWellCasingParameter::getCementTop() const {
    return cementTop;
}

void MWellCasingParameter::setCementTop(double newCementTop) {
    cementTop = newCementTop;
}

double MWellCasingParameter::getCementDensity() const {
    return cementDensity;
}

void MWellCasingParameter::setCementDensity(double newCementDensity) {
    cementDensity = newCementDensity;
}

double MWellCasingParameter::getCementTheramlCond() const {
    return cementTheramlCond;
}

void MWellCasingParameter::setCementTheramlCond(double newCementTheramlCond) {
    cementTheramlCond = newCementTheramlCond;
}
