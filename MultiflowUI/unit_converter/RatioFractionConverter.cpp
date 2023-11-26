//
// Created by miku on 11/26/2023.
//

#include "RatioFractionConverter.hpp"

constexpr const char* Ratio = "%";
constexpr const char* Fraction = "fract.";

RatioFractionConverter::RatioFractionConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> RatioFractionConverter::units() const {
    return {Ratio, Fraction};
}

double RatioFractionConverter::convert(const double value, const QString& from, const QString& to) const {
    if (from == Ratio && to == Fraction) {
        return value / 100;
    }
    if (from == Fraction && to == Ratio) {
        return value * 100;
    }
    throw ConverterException("Unknown target unit");
}
