//
// Created by miku on 11/26/2023.
//

#include "GasRatioConverter.hpp"

constexpr const char* Sm3Sm3 = "sm3/sm3";
constexpr const char* ScfStb = "SCF/STB";

GasRatioConverter::GasRatioConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> GasRatioConverter::units() const {
    return {Sm3Sm3, ScfStb};
}

double GasRatioConverter::convert(const double value, const QString& from, const QString& to) const {
    if (from == Sm3Sm3 && to == ScfStb) {
        return value * 35.3147 / 0.1589873;
    }
    if (from == ScfStb && to == Sm3Sm3) {
        return value * 0.1589873 / 35.3147;
    }
    throw ConverterException("Unknown units");
}
