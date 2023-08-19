#include "mwellheat.h"

MWellHeat::MWellHeat()
{

}

MWellHeat::~MWellHeat()
{
    qDeleteAll(htcCalculateList);
    qDeleteAll(htcCalATIMultList);
    qDeleteAll(uMultATIMultList);
}

QString MWellHeat::getHeatTransferCoefficient() const
{
    return heatTransferCoefficient;
}

void MWellHeat::setHeatTransferCoefficient(const QString &newHeatTransferCoefficient)
{
    heatTransferCoefficient = newHeatTransferCoefficient;
}

QString MWellHeat::getUValutInput() const
{
    return UValutInput;
}

void MWellHeat::setUValutInput(const QString &newUValutInput)
{
    UValutInput = newUValutInput;
}

double MWellHeat::getAverageUValue() const
{
    return averageUValue;
}

void MWellHeat::setAverageUValue(double newAverageUValue)
{
    averageUValue = newAverageUValue;
}

double MWellHeat::getAmbientTemperatureInput() const
{
    return ambientTemperatureInput;
}

void MWellHeat::setAmbientTemperatureInput(double newAmbientTemperatureInput)
{
    ambientTemperatureInput = newAmbientTemperatureInput;
}

double MWellHeat::getSoilTemperatureWellhead() const
{
    return soilTemperatureWellhead;
}

void MWellHeat::setSoilTemperatureWellhead(double newSoilTemperatureWellhead)
{
    soilTemperatureWellhead = newSoilTemperatureWellhead;
}

double MWellHeat::getTime() const
{
    return time;
}

void MWellHeat::setTime(double newTime)
{
    time = newTime;
}

QList<HTCCalculate *> MWellHeat::getHtcCalculateList() const
{
    return htcCalculateList;
}

void MWellHeat::setHtcCalculateList(const QList<HTCCalculate *> &newHtcCalculateList)
{
    htcCalculateList = newHtcCalculateList;
}

QList<HTCCalATIMult *> MWellHeat::getHtcCalATIMultList() const
{
    return htcCalATIMultList;
}

void MWellHeat::setHtcCalATIMultList(const QList<HTCCalATIMult *> &newHtcCalATIMultList)
{
    htcCalATIMultList = newHtcCalATIMultList;
}

QList<UMultATIMult *> MWellHeat::getUMultATIMultList() const
{
    return uMultATIMultList;
}

void MWellHeat::setUMultATIMultList(const QList<UMultATIMult *> &newUMultATIMultList)
{
    uMultATIMultList = newUMultATIMultList;
}

double HTCCalculate::getMD() const
{
    return MD;
}

void HTCCalculate::setMD(double newMD)
{
    MD = newMD;
}

double HTCCalculate::getGroundDensity() const
{
    return groundDensity;
}

void HTCCalculate::setGroundDensity(double newGroundDensity)
{
    groundDensity = newGroundDensity;
}

double HTCCalculate::getGroundK() const
{
    return groundK;
}

void HTCCalculate::setGroundK(double newGroundK)
{
    groundK = newGroundK;
}

double HTCCalculate::getGroundCp() const
{
    return groundCp;
}

void HTCCalculate::setGroundCp(double newGroundCp)
{
    groundCp = newGroundCp;
}

HTCCalculate::HTCCalculate(double MD, double groundDensity, double groundK, double groundCp) : MD(MD),
    groundDensity(groundDensity),
    groundK(groundK),
    groundCp(groundCp)
{}

double HTCCalATIMult::getMD() const
{
    return MD;
}

void HTCCalATIMult::setMD(double newMD)
{
    MD = newMD;
}

double HTCCalATIMult::getAmbientTemperature() const
{
    return ambientTemperature;
}

void HTCCalATIMult::setAmbientTemperature(double newAmbientTemperature)
{
    ambientTemperature = newAmbientTemperature;
}

double HTCCalATIMult::getGroundDensity() const
{
    return groundDensity;
}

void HTCCalATIMult::setGroundDensity(double newGroundDensity)
{
    groundDensity = newGroundDensity;
}

double HTCCalATIMult::getGroundK() const
{
    return groundK;
}

void HTCCalATIMult::setGroundK(double newGroundK)
{
    groundK = newGroundK;
}

double HTCCalATIMult::getGourndCp() const
{
    return gourndCp;
}

void HTCCalATIMult::setGourndCp(double newGourndCp)
{
    gourndCp = newGourndCp;
}

HTCCalATIMult::HTCCalATIMult(double MD, double ambientTemperature, double groundDensity, double groundK, double gourndCp) : MD(MD),
    ambientTemperature(ambientTemperature),
    groundDensity(groundDensity),
    groundK(groundK),
    gourndCp(gourndCp)
{}

double UMultATIMult::getMD() const
{
    return MD;
}

void UMultATIMult::setMD(double newMD)
{
    MD = newMD;
}

double UMultATIMult::getAmbientTemperature() const
{
    return ambientTemperature;
}

void UMultATIMult::setAmbientTemperature(double newAmbientTemperature)
{
    ambientTemperature = newAmbientTemperature;
}

double UMultATIMult::getUValue() const
{
    return UValue;
}

void UMultATIMult::setUValue(double newUValue)
{
    UValue = newUValue;
}

UMultATIMult::UMultATIMult(double MD, double ambientTemperature, double UValue) : MD(MD),
    ambientTemperature(ambientTemperature),
    UValue(UValue)
{}
