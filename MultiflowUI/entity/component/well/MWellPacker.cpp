#include "MWellPacker.hpp"
#include <QUuid>

MWellPacker::MWellPacker() {
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MWellPacker::getId() const {
    return id;
}

void MWellPacker::setId(const QString& newId) {
    id = newId;
}

QString MWellPacker::getName() const {
    return name;
}

void MWellPacker::setName(const QString& newName) {
    name = newName;
}

double MWellPacker::getInnerDiameter() const {
    return innerDiameter;
}

void MWellPacker::setInnerDiameter(double newInnerDiameter) {
    innerDiameter = newInnerDiameter;
}

double MWellPacker::getOutDiameter() const {
    return outDiameter;
}

void MWellPacker::setOutDiameter(double newOutDiameter) {
    outDiameter = newOutDiameter;
}

QString MWellPacker::getMaterialId() const {
    return materialId;
}

void MWellPacker::setMaterialId(const QString& newMaterialId) {
    materialId = newMaterialId;
}

QString MWellPacker::getGrade() const {
    return grade;
}

void MWellPacker::setGrade(const QString& newGrade) {
    grade = newGrade;
}

double MWellPacker::getLength() const {
    return length;
}

void MWellPacker::setLength(double newLength) {
    length = newLength;
}

double MWellPacker::getWorkPressureDiff() const {
    return workPressureDiff;
}

void MWellPacker::setWorkPressureDiff(double newWorkPressureDiff) {
    workPressureDiff = newWorkPressureDiff;
}

int MWellPacker::getSealType() const {
    return sealType;
}

void MWellPacker::setSealType(int newSealType) {
    sealType = newSealType;
}

int MWellPacker::getUnsealType() const {
    return unsealType;
}

void MWellPacker::setUnsealType(int newUnsealType) {
    unsealType = newUnsealType;
}

double MWellPacker::getSealPressure() const {
    return sealPressure;
}

void MWellPacker::setSealPressure(double newSealPressure) {
    sealPressure = newSealPressure;
}

double MWellPacker::getWorkTemperature() const {
    return workTemperature;
}

void MWellPacker::setWorkTemperature(double newWorkTemperature) {
    workTemperature = newWorkTemperature;
}

double MWellPacker::getCasingDiameter() const {
    return casingDiameter;
}

void MWellPacker::setCasingDiameter(double newCasingDiameter) {
    casingDiameter = newCasingDiameter;
}

QString MWellPacker::getBoreMaterial() const {
    return boreMaterial;
}

void MWellPacker::setBoreMaterial(const QString& newBoreMaterial) {
    boreMaterial = newBoreMaterial;
}

double MWellPacker::getDriftDiameter() const {
    return driftDiameter;
}

void MWellPacker::setDriftDiameter(double newDriftDiameter) {
    driftDiameter = newDriftDiameter;
}

double MWellPacker::getPerLengthWeight() const {
    return perLengthWeight;
}

void MWellPacker::setPerLengthWeight(double newPerLengthWeight) {
    perLengthWeight = newPerLengthWeight;
}

double MWellPacker::getCollapsePressure() const {
    return collapsePressure;
}

void MWellPacker::setCollapsePressure(double newCollapsePressure) {
    collapsePressure = newCollapsePressure;
}

double MWellPacker::getMaxTensile() const {
    return maxTensile;
}

void MWellPacker::setMaxTensile(double newMaxTensile) {
    maxTensile = newMaxTensile;
}

double MWellPacker::getBurstPressure() const {
    return burstPressure;
}

void MWellPacker::setBurstPressure(double newBurstPressure) {
    burstPressure = newBurstPressure;
}

double MWellPacker::getMaxCTorque() const {
    return maxCTorque;
}

void MWellPacker::setMaxCTorque(double newMaxCTorque) {
    maxCTorque = newMaxCTorque;
}

double MWellPacker::getSafetyFactor() const {
    return safetyFactor;
}

void MWellPacker::setSafetyFactor(double newSafetyFactor) {
    safetyFactor = newSafetyFactor;
}

double MWellPacker::getNoumenonTensile() const {
    return noumenonTensile;
}

void MWellPacker::setNoumenonTensile(double newNoumenonTensile) {
    noumenonTensile = newNoumenonTensile;
}

int MWellPacker::getWaterAnchor() const {
    return waterAnchor;
}

void MWellPacker::setWaterAnchor(int newWaterAnchor) {
    waterAnchor = newWaterAnchor;
}

double MWellPacker::getSealingDiameter() const {
    return sealingDiameter;
}

void MWellPacker::setSealingDiameter(double newSealingDiameter) {
    sealingDiameter = newSealingDiameter;
}

double MWellPacker::getMaxCasingFriction() const {
    return maxCasingFriction;
}

void MWellPacker::setMaxCasingFriction(double newMaxCasingFriction) {
    maxCasingFriction = newMaxCasingFriction;
}

QString MWellPacker::getFactory() const {
    return factory;
}

void MWellPacker::setFactory(const QString& newFactory) {
    factory = newFactory;
}

QString MWellPacker::getModel() const {
    return model;
}

void MWellPacker::setModel(const QString& newModel) {
    model = newModel;
}

QString MWellPacker::getSn() const {
    return sn;
}

void MWellPacker::setSn(const QString& newSn) {
    sn = newSn;
}

QDateTime MWellPacker::getCreateDate() const {
    return createDate;
}

void MWellPacker::setCreateDate(const QDateTime& newCreateDate) {
    createDate = newCreateDate;
}

QString MWellPacker::getCreateUser() const {
    return createUser;
}

void MWellPacker::setCreateUser(const QString& newCreateUser) {
    createUser = newCreateUser;
}

QDateTime MWellPacker::getUpdateDate() const {
    return updateDate;
}

void MWellPacker::setUpdateDate(const QDateTime& newUpdateDate) {
    updateDate = newUpdateDate;
}

QString MWellPacker::getUpdateUser() const {
    return updateUser;
}

void MWellPacker::setUpdateUser(const QString& newUpdateUser) {
    updateUser = newUpdateUser;
}

QString MWellPacker::getDescription() const {
    return description;
}

void MWellPacker::setDescription(const QString& newDescription) {
    description = newDescription;
}

double MWellPacker::getUnsealingForce() const {
    return unsealingForce;
}

void MWellPacker::setUnsealingForce(double newUnsealingForce) {
    unsealingForce = newUnsealingForce;
}

QByteArray MWellPacker::getIcon() const {
    return icon;
}

void MWellPacker::setIcon(const QByteArray& newIcon) {
    icon = newIcon;
}

double MWellPacker::getMeasuredDepth() const {
    return measuredDepth;
}

void MWellPacker::setMeasuredDepth(double newMeasuredDepth) {
    measuredDepth = newMeasuredDepth;
}
