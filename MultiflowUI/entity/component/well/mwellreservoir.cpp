#include "mwellreservoir.h"
#include <QUuid>

MWellReservoir::MWellReservoir()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

MWellReservoir::MWellReservoir(MWellReservoir::ReservoirFluidType fluidType, double fluidDensity, double fluidViscosity, double reservoirPressure, double reservoirTemperature, double reservoirWatercut) : fluidType(fluidType),
    fluidDensity(fluidDensity),
    fluidViscosity(fluidViscosity),
    reservoirPressure(reservoirPressure),
    reservoirTemperature(reservoirTemperature),
    reservoirWatercut(reservoirWatercut)
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MWellReservoir::getId() const
{
    return id;
}

void MWellReservoir::setId(const QString &newId)
{
    id = newId;
}

QString MWellReservoir::getWellId() const
{
    return wellId;
}

void MWellReservoir::setWellId(const QString &newWellId)
{
    wellId = newWellId;
}

MWellReservoir::ReservoirFluidType MWellReservoir::getFluidType() const
{
    return fluidType;
}

void MWellReservoir::setFluidType(ReservoirFluidType newFluidType)
{
    fluidType = newFluidType;
}

double MWellReservoir::getFluidDensity() const
{
    return fluidDensity;
}

void MWellReservoir::setFluidDensity(double newFluidDensity)
{
    fluidDensity = newFluidDensity;
}

double MWellReservoir::getFluidViscosity() const
{
    return fluidViscosity;
}

void MWellReservoir::setFluidViscosity(double newFluidViscosity)
{
    fluidViscosity = newFluidViscosity;
}

double MWellReservoir::getReservoirPressure() const
{
    return reservoirPressure;
}

void MWellReservoir::setReservoirPressure(double newReservoirPressure)
{
    reservoirPressure = newReservoirPressure;
}

double MWellReservoir::getReservoirTemperature() const
{
    return reservoirTemperature;
}

void MWellReservoir::setReservoirTemperature(double newReservoirTemperature)
{
    reservoirTemperature = newReservoirTemperature;
}

double MWellReservoir::getReservoirWatercut() const
{
    return reservoirWatercut;
}

void MWellReservoir::setReservoirWatercut(double newReservoirWatercut)
{
    reservoirWatercut = newReservoirWatercut;
}
