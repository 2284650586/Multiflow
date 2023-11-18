#include "MFlowlineParameter.hpp"

MFlowlineParameter::MFlowlineParameter() {
}

double MFlowlineParameter::getHd1() const {
    return hd1;
}

void MFlowlineParameter::setHd1(double newHd1) {
    hd1 = newHd1;
}

double MFlowlineParameter::getElevation() const {
    return elevation;
}

void MFlowlineParameter::setElevation(double newElevation) {
    elevation = newElevation;
}

double MFlowlineParameter::getHd2() const {
    return hd2;
}

void MFlowlineParameter::setHd2(double newHd2) {
    hd2 = newHd2;
}

double MFlowlineParameter::getTemperature() const {
    return temperature;
}

void MFlowlineParameter::setTemperature(double newTemperature) {
    temperature = newTemperature;
}

MFlowlineParameter::MFlowlineParameter(double hd1, double elevation, double hd2, double temperature) : hd1(hd1),
    elevation(elevation),
    hd2(hd2),
    temperature(temperature) {
}
