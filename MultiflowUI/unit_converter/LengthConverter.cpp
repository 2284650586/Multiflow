//
// Created by miku on 11/20/2023.
//

#include "LengthConverter.hpp"

#include <QMap>

const static QMap<QString, double> unitToMeter = {
    {"m", 1.0},
    {"cm", 0.01},
    {"dm", 0.1},
    {"km", 1000.0},
    {"mm", 0.001},
    {"ft", 0.3048},
    {"in", 0.0254}
};

LengthConverter::LengthConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> LengthConverter::units() const {
    return unitToMeter.keys();
}

double LengthConverter::convert(const double value, const QString& from, const QString& to) const {
    const double valueInMeters = value * unitToMeter[from];
    return valueInMeters / unitToMeter[to];
}
