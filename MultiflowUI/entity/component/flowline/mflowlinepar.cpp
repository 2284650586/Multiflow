#include "mflowlinepar.h"

MFlowlinePar::MFlowlinePar()
{

}

double MFlowlinePar::getHd1() const
{
    return hd1;
}

void MFlowlinePar::setHd1(double newHd1)
{
    hd1 = newHd1;
}

double MFlowlinePar::getElevation() const
{
    return elevation;
}

void MFlowlinePar::setElevation(double newElevation)
{
    elevation = newElevation;
}

double MFlowlinePar::getHd2() const
{
    return hd2;
}

void MFlowlinePar::setHd2(double newHd2)
{
    hd2 = newHd2;
}

double MFlowlinePar::getTemperature() const
{
    return temperature;
}

void MFlowlinePar::setTemperature(double newTemperature)
{
    temperature = newTemperature;
}

MFlowlinePar::MFlowlinePar(double hd1, double elevation, double hd2, double temperature) : hd1(hd1),
    elevation(elevation),
    hd2(hd2),
    temperature(temperature)
{}
