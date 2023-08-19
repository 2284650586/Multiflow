#include "msource.h"
#include <QUuid>

MSource::MSource()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
    sourcePressure = 0;
    sourceTemperature = 0;
    sourceFlowType = SourceType::Liquid;
    sourceFlowRate = 0;
}

double MSource::getSourcePressure() const
{
    return sourcePressure;
}

void MSource::setSourcePressure(double newSourcePressure)
{
    sourcePressure = newSourcePressure;
}

double MSource::getSourceTemperature() const
{
    return sourceTemperature;
}

void MSource::setSourceTemperature(double newSourceTemperature)
{
    sourceTemperature = newSourceTemperature;
}

void MSource::setSourceFlowType(SourceType newSourceFlowType)
{
    sourceFlowType = newSourceFlowType;
}

double MSource::getSourceFlowRate() const
{
    return sourceFlowRate;
}

void MSource::setSourceFlowRate(double newSourceFlowRate)
{
    sourceFlowRate = newSourceFlowRate;
}

MSource::MSource(double sourcePressure, double sourceTemperature, MSource::SourceType sourceFlowType, double sourceFlowRate) :
    sourcePressure(sourcePressure),
    sourceTemperature(sourceTemperature),
    sourceFlowType(sourceFlowType),
    sourceFlowRate(sourceFlowRate)
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}
