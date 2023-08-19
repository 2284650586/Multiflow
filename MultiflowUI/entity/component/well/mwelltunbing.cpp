#include "mwelltunbing.h"
#include <QUuid>

MWellTunbing::MWellTunbing()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MWellTunbing::getId() const
{
    return id;
}

void MWellTunbing::setId(const QString &newId)
{
    id = newId;
}

QString MWellTunbing::getName() const
{
    return name;
}

void MWellTunbing::setName(const QString &newName)
{
    name = newName;
}

double MWellTunbing::getInnerDiameter() const
{
    return innerDiameter;
}

void MWellTunbing::setInnerDiameter(double newInnerDiameter)
{
    innerDiameter = newInnerDiameter;
}

double MWellTunbing::getOutDiameter() const
{
    return outDiameter;
}

void MWellTunbing::setOutDiameter(double newOutDiameter)
{
    outDiameter = newOutDiameter;
}

QString MWellTunbing::getMaterialId() const
{
    return materialId;
}

void MWellTunbing::setMaterialId(const QString &newMaterialId)
{
    materialId = newMaterialId;
}

QString MWellTunbing::getGrade() const
{
    return grade;
}

void MWellTunbing::setGrade(const QString &newGrade)
{
    grade = newGrade;
}

double MWellTunbing::getWallThickness() const
{
    return wallThickness;
}

void MWellTunbing::setWallThickness(double newWallThickness)
{
    wallThickness = newWallThickness;
}

double MWellTunbing::getSpecs() const
{
    return specs;
}

void MWellTunbing::setSpecs(double newSpecs)
{
    specs = newSpecs;
}

double MWellTunbing::getPerLengthWeight() const
{
    return perLengthWeight;
}

void MWellTunbing::setPerLengthWeight(double newPerLengthWeight)
{
    perLengthWeight = newPerLengthWeight;
}

double MWellTunbing::getCollapsePress() const
{
    return collapsePress;
}

void MWellTunbing::setCollapsePress(double newCollapsePress)
{
    collapsePress = newCollapsePress;
}

double MWellTunbing::getMaxTensile() const
{
    return maxTensile;
}

void MWellTunbing::setMaxTensile(double newMaxTensile)
{
    maxTensile = newMaxTensile;
}

double MWellTunbing::getNoumenonTensile() const
{
    return noumenonTensile;
}

void MWellTunbing::setNoumenonTensile(double newNoumenonTensile)
{
    noumenonTensile = newNoumenonTensile;
}

double MWellTunbing::getConnectionStrength() const
{
    return connectionStrength;
}

void MWellTunbing::setConnectionStrength(double newConnectionStrength)
{
    connectionStrength = newConnectionStrength;
}

QString MWellTunbing::getJoinType() const
{
    return joinType;
}

void MWellTunbing::setJoinType(const QString &newJoinType)
{
    joinType = newJoinType;
}

double MWellTunbing::getDriftDiameter() const
{
    return driftDiameter;
}

void MWellTunbing::setDriftDiameter(double newDriftDiameter)
{
    driftDiameter = newDriftDiameter;
}

double MWellTunbing::getBurstPress() const
{
    return burstPress;
}

void MWellTunbing::setBurstPress(double newBurstPress)
{
    burstPress = newBurstPress;
}

double MWellTunbing::getMaxCTorque() const
{
    return maxCTorque;
}

void MWellTunbing::setMaxCTorque(double newMaxCTorque)
{
    maxCTorque = newMaxCTorque;
}

QString MWellTunbing::getFactory() const
{
    return factory;
}

void MWellTunbing::setFactory(const QString &newFactory)
{
    factory = newFactory;
}

QString MWellTunbing::getModel() const
{
    return model;
}

void MWellTunbing::setModel(const QString &newModel)
{
    model = newModel;
}

QString MWellTunbing::getSn() const
{
    return sn;
}

void MWellTunbing::setSn(const QString &newSn)
{
    sn = newSn;
}

double MWellTunbing::getSafeFactory() const
{
    return safeFactory;
}

void MWellTunbing::setSafeFactory(double newSafeFactory)
{
    safeFactory = newSafeFactory;
}

double MWellTunbing::getPerLengthDensity() const
{
    return perLengthDensity;
}

void MWellTunbing::setPerLengthDensity(double newPerLengthDensity)
{
    perLengthDensity = newPerLengthDensity;
}

double MWellTunbing::getDensity() const
{
    return density;
}

void MWellTunbing::setDensity(double newDensity)
{
    density = newDensity;
}

double MWellTunbing::getElasticModule() const
{
    return elasticModule;
}

void MWellTunbing::setElasticModule(double newElasticModule)
{
    elasticModule = newElasticModule;
}

QDateTime MWellTunbing::getCreateDate() const
{
    return createDate;
}

void MWellTunbing::setCreateDate(const QDateTime &newCreateDate)
{
    createDate = newCreateDate;
}

QString MWellTunbing::getCreateUser() const
{
    return createUser;
}

void MWellTunbing::setCreateUser(const QString &newCreateUser)
{
    createUser = newCreateUser;
}

QDateTime MWellTunbing::getUpdateDate() const
{
    return updateDate;
}

void MWellTunbing::setUpdateDate(const QDateTime &newUpdateDate)
{
    updateDate = newUpdateDate;
}

QString MWellTunbing::getUpdateUser() const
{
    return updateUser;
}

void MWellTunbing::setUpdateUser(const QString &newUpdateUser)
{
    updateUser = newUpdateUser;
}

QString MWellTunbing::getDescription() const
{
    return description;
}

void MWellTunbing::setDescription(const QString &newDescription)
{
    description = newDescription;
}

double MWellTunbing::getPoissonRatio() const
{
    return poissonRatio;
}

void MWellTunbing::setPoissonRatio(double newPoissonRatio)
{
    poissonRatio = newPoissonRatio;
}

QByteArray MWellTunbing::getIcon() const
{
    return icon;
}

void MWellTunbing::setIcon(const QByteArray &newIcon)
{
    icon = newIcon;
}

double MWellTunbing::getRoughness() const
{
    return roughness;
}

void MWellTunbing::setRoughness(double newRoughness)
{
    roughness = newRoughness;
}

double MWellTunbing::getThermal() const
{
    return thermal;
}

void MWellTunbing::setThermal(double newThermal)
{
    thermal = newThermal;
}

double MWellTunbing::getToMD() const
{
    return toMD;
}

void MWellTunbing::setToMD(double newToMD)
{
    toMD = newToMD;
}

QString MWellTunbing::getFluidType() const
{
    return fluid;
}

void MWellTunbing::setFluidType(const QString &newFluid)
{
    fluid = newFluid;
}

double MWellTunbing::getFluidDensity() const
{
    return fluidDensity;
}

void MWellTunbing::setFluidDensity(double newFluidDensity)
{
    fluidDensity = newFluidDensity;
}

double MWellTunbing::getFluidThermalCond() const
{
    return fluidThermalCond;
}

void MWellTunbing::setFluidThermalCond(double newFluidThermalCond)
{
    fluidThermalCond = newFluidThermalCond;
}

MWellTunbing::MWellTunbing(const QString &id, double innerDiameter, double outDiameter, const QString &materialId, double specs, double perLengthWeight, double collapsePress, double maxTensile, double noumenonTensile, double connectionStrength, const QString &joinType, double driftDiameter, double burstPress, double maxCTorque, const QString &factory, const QString &model, const QString &sn, double safeFactory, double perLengthDensity, double elasticModule, const QDateTime &createDate, const QString &createUser, const QDateTime &updateDate, const QString &updateUser, const QString &description, const QByteArray &icon, double poissonRatio, const QString &name, double roughness, double thermal, double toMD, double wallThickness, const QString &grade, double density, double ID, const QString &fluid, double fluidDensity, double fluidThermalCond) : id(id),
    innerDiameter(innerDiameter),
    outDiameter(outDiameter),
    materialId(materialId),
    specs(specs),
    perLengthWeight(perLengthWeight),
    collapsePress(collapsePress),
    maxTensile(maxTensile),
    noumenonTensile(noumenonTensile),
    connectionStrength(connectionStrength),
    joinType(joinType),
    driftDiameter(driftDiameter),
    burstPress(burstPress),
    maxCTorque(maxCTorque),
    factory(factory),
    model(model),
    sn(sn),
    safeFactory(safeFactory),
    perLengthDensity(perLengthDensity),
    elasticModule(elasticModule),
    createDate(createDate),
    createUser(createUser),
    updateDate(updateDate),
    updateUser(updateUser),
    description(description),
    icon(icon),
    poissonRatio(poissonRatio),
    name(name),
    roughness(roughness),
    thermal(thermal),
    toMD(toMD),
    wallThickness(wallThickness),
    grade(grade),
    density(density),
    ID(ID),
    fluid(fluid),
    fluidDensity(fluidDensity),
    fluidThermalCond(fluidThermalCond)
{}
