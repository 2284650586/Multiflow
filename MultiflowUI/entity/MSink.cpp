#include "MSink.hpp"
#include <QUuid>

MSink::MSink() {
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

MSink::MSink(
    double sinkPressure, double sinkTemperature, MSink::SinkType sinkFlowType,
    double sinkFlowRate
)
    : sinkPressure(sinkPressure),
      sinkTemperature(sinkTemperature),
      sinkFlowType(sinkFlowType),
      sinkFlowRate(sinkFlowRate) {
    QUuid uid = QUuid::createUuid();
    id = uid.toString();
}

QString MSink::getSinkId() const {
    return id;
}

void MSink::setSinkId(const QString& newSinkId) {
    id = newSinkId;
}

double MSink::getSinkPressure() const {
    return sinkPressure;
}

void MSink::setSinkPressure(double newSinkPressure) {
    sinkPressure = newSinkPressure;
}

double MSink::getSinkTemperature() const {
    return sinkTemperature;
}

void MSink::setSinkTemperature(double newSinkTemperature) {
    sinkTemperature = newSinkTemperature;
}

void MSink::setSinkFlowType(SinkType newSinkFlowType) {
    sinkFlowType = newSinkFlowType;
}

double MSink::getSinkFlowRate() const {
    return sinkFlowRate;
}

void MSink::setSinkFlowRate(double newSinkFlowRate) {
    sinkFlowRate = newSinkFlowRate;
}
