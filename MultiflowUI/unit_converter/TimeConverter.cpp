//
// Created by Hatsune Miku on 2023-12-13.
//

#include "TimeConverter.hpp"

const static QMap<QString, double> unitToSeconds = {
    {"s", 1.0},
    {"hr", 60.0},
    {"min", 3600.0},
    {"d", 86400.0},
    {"a", 31536000.0}
};

TimeConverter::TimeConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> TimeConverter::units() const {
    return {"s", "hr", "min", "d", "a"};
}

double TimeConverter::convert(const double value, const QString& from, const QString& to) const {
    const double valueInSeconds = value * unitToSeconds[from];
    return valueInSeconds / unitToSeconds[to];
}
