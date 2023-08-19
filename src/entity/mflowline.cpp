#include "mflowline.h"
#include <QUuid>

MFlowline::MFlowline()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MFlowline::getFlowlineId() const
{
    return id;
}

void MFlowline::setFlowlineId(const QString &newFlowlineId)
{
    id = newFlowlineId;
}

MFlowline::FlowlineType MFlowline::getFlowlineType() const
{
    return flowlineType;
}

void MFlowline::setFlowlineType(FlowlineType newFlowlineType)
{
    flowlineType = newFlowlineType;
}

MFlowline::FlowlineMode MFlowline::getFlowlineMode() const
{
    return flowlineMode;
}

void MFlowline::setFlowlineMode(FlowlineMode newFlowlineMode)
{
    flowlineMode = newFlowlineMode;
}

MFlowline::FlowlineEnviroment MFlowline::getFlowlineEnviroment() const
{
    return flowlineEnviroment;
}

void MFlowline::setFlowlineEnviroment(FlowlineEnviroment newFlowlineEnviroment)
{
    flowlineEnviroment = newFlowlineEnviroment;
}

double MFlowline::getPipInsideDiameter() const
{
    return pipInsideDiameter;
}

void MFlowline::setPipInsideDiameter(double newPipInsideDiameter)
{
    pipInsideDiameter = newPipInsideDiameter;
}

double MFlowline::getPipWallThickness() const
{
    return pipWallThickness;
}

void MFlowline::setPipWallThickness(double newPipWallThickness)
{
    pipWallThickness = newPipWallThickness;
}

double MFlowline::getPipeRoughness() const
{
    return pipeRoughness;
}

void MFlowline::setPipeRoughness(double newPipeRoughness)
{
    pipeRoughness = newPipeRoughness;
}

double MFlowline::getProfileHorizontalDistance() const
{
    return profileHorizontalDistance;
}

void MFlowline::setProfileHorizontalDistance(double newProfileHorizontalDistance)
{
    profileHorizontalDistance = newProfileHorizontalDistance;
}

double MFlowline::getProfileElevatiaonDifference() const
{
    return profileElevatiaonDifference;
}

void MFlowline::setProfileElevatiaonDifference(double newProfileElevatiaonDifference)
{
    profileElevatiaonDifference = newProfileElevatiaonDifference;
}

double MFlowline::getHeatTransferCoefficient() const
{
    return heatTransferCoefficient;
}

void MFlowline::setHeatTransferCoefficient(double newHeatTransferCoefficient)
{
    heatTransferCoefficient = newHeatTransferCoefficient;
}

QList<MFlowlinePar *> MFlowline::getParList() const
{
    return parList;
}

MFlowline::MFlowline(MFlowline::FlowlineType flowlineType, MFlowline::FlowlineMode flowlineMode, MFlowline::FlowlineEnviroment flowlineEnviroment, double pipInsideDiameter, double pipWallThickness, double pipeRoughness, double profileHorizontalDistance, double profileElevatiaonDifference, double heatTransferCoefficient) : flowlineType(flowlineType),
    flowlineMode(flowlineMode),
    flowlineEnviroment(flowlineEnviroment),
    pipInsideDiameter(pipInsideDiameter),
    pipWallThickness(pipWallThickness),
    pipeRoughness(pipeRoughness),
    profileHorizontalDistance(profileHorizontalDistance),
    profileElevatiaonDifference(profileElevatiaonDifference),
    heatTransferCoefficient(heatTransferCoefficient)
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

MFlowline::~MFlowline()
{
    for (MFlowlinePar *par : parList) {
        delete par;
    }
}

void MFlowline::addPar(double hd1, double elevation, double dh2, double temperature)
{
    MFlowlinePar *par = new MFlowlinePar(hd1, elevation, dh2, temperature);
    parList.append(par);
}
