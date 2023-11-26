//
// Created by miku on 11/25/2023.
//

#include "TemperatureConverter.hpp"

constexpr const char* DegreeCelsius = "degC";
constexpr const char* DegreeFahrenheit = "degF";
constexpr const char* Kelvin = "K";
constexpr const char* DegreeRankine = "degR";

TemperatureConverter::TemperatureConverter(QObject* parent): AbstractUnitConverter(parent) {
}

QVector<QString> TemperatureConverter::units() const {
    return {DegreeCelsius, DegreeFahrenheit, Kelvin, DegreeRankine};
}

double TemperatureConverter::convert(const double value, const QString& from, const QString& to) const {
    double tempInK; // 以开尔文为中间转换单位
    // 从源单位转换到开尔文
    if (from == DegreeCelsius) {
        tempInK = value + 273.15;
    }
    else if (from == DegreeFahrenheit) {
        tempInK = (value - 32) * 5.0 / 9.0 + 273.15;
    }
    else if (from == Kelvin) {
        tempInK = value;
    }
    else if (from == DegreeRankine) {
        tempInK = value * 5.0 / 9.0;
    }
    else {
        throw ConverterException("Unknown source unit");
    }

    // 从开尔文转换到目标单位
    if (to == DegreeCelsius) {
        return tempInK - 273.15;
    }
    if (to == DegreeFahrenheit) {
        return (tempInK - 273.15) * 9.0 / 5.0 + 32;
    }
    if (to == Kelvin) {
        return tempInK;
    }
    if (to == DegreeRankine) {
        return tempInK * 9.0 / 5.0;
    }
    throw ConverterException("Unknown target unit");
}
