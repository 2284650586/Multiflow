//
// Created by miku on 11/25/2023.
//

#include "PressureConverter.hpp"

#include <QMap>

const static QMap<QString, double> unitToKPa = {
    {"kPa", 1.0},
    {"MPa", 1000.0},
    {"bar", 100.0},
    {"psi", 6.895},
    {"kgf/cm2", 98.0665},
    {"psia", 6.895},
    {"psig", 6.895},
};

PressureConverter::PressureConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> PressureConverter::units() const {
    // unitToMeter.keys() returns ordered list of keys which are not expected
    return {"MPa", "kPa", "bar", "psi", "kgf/cm2", "psia", "psig"};
}

double PressureConverter::convert(const double value, const QString& from, const QString& to) const {
    const double base = value * unitToKPa[from];
    return base / unitToKPa[to];
}
