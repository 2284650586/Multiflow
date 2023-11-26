//
// Created by miku on 11/25/2023.
//

#include "FluidUnitConverter.hpp"

#include <QMap>

const static QMap<QString, double> unitsMap = {
    {"STB/(d.psi)", 1.0},
};

FluidUnitConverter::FluidUnitConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> FluidUnitConverter::units() const {
    return unitsMap.keys();
}

double FluidUnitConverter::convert(const double value, const QString& from, const QString& to) const {
    const double base = value * unitsMap[from];
    return base / unitsMap[to];
}
