#pragma once

#include "entity/common.hpp"

#include <QVariant>
#include <QString>

struct HTCCalculate {
    Q_GADGET

public:
    Q_MEMBER(double, MD)
    Q_MEMBER(double, ambientTemperature)
    Q_MEMBER(double, groundDensity)
    Q_MEMBER(double, groundK)
    Q_MEMBER(double, groundCp)
};

Q_DECLARE_METATYPE(HTCCalculate)

struct HTCCalATIMult {
    Q_GADGET

public:
    Q_MEMBER(double, MD)
    Q_MEMBER(double, ambientTemperature)
    Q_MEMBER(double, groundDensity)
    Q_MEMBER(double, groundK)
    Q_MEMBER(double, groundCp)
};

Q_DECLARE_METATYPE(HTCCalATIMult)

struct UMultATIMult {
    Q_GADGET

public:
    Q_MEMBER(double, MD)
    Q_MEMBER(double, ambientTemperature)
    Q_MEMBER(double, UValue)
};

Q_DECLARE_METATYPE(UMultATIMult)

struct MWellHeat {
    Q_GADGET

public:
    Q_MEMBER(QString, heatTransferCoefficient)
    Q_MEMBER(QString, UValutInput)
    Q_MEMBER(double, averageUValue)
    Q_MEMBER(double, ambientTemperatureInput)
    Q_MEMBER(double, soilTemperatureWellhead)
    Q_MEMBER(double, time)
    Q_MEMBER(QList<HTCCalculate>, htcCalculateList)
    Q_MEMBER(QList<HTCCalATIMult>, htcCalATIMultList)
    Q_MEMBER(QList<UMultATIMult>, uMultATIMultList)
};

Q_DECLARE_METATYPE(MWellHeat)
