#pragma once

#include "entity/common.hpp"

#include <QDateTime>
#include <QString>
#include <QUuid>

struct MWellCasing {
    Q_GADGET

public:
    Q_MEMBER_INIT(QString, id, QUuid::createUuid().toString())
    Q_MEMBER(double, innerDiameter)
    Q_MEMBER(double, outDiameter)
    Q_MEMBER(QString, materialId)
    Q_MEMBER(double, perLengthWeight)
    Q_MEMBER(QString, endFace)
    Q_MEMBER(double, adjPerLengthWeight)
    Q_MEMBER(double, jointOutDiameter)
    Q_MEMBER(double, jointInnerDiameter)
    Q_MEMBER(double, jointTensile)
    Q_MEMBER(double, noumenonTensile)
    Q_MEMBER(double, buckleTorque)
    Q_MEMBER(int, elasticModulus)
    Q_MEMBER(double, collapsePressure)
    Q_MEMBER(double, maxCTorque)
    Q_MEMBER(double, burstPressure)
    Q_MEMBER(double, maxTensile)
    Q_MEMBER(double, driftDiameter)
    Q_MEMBER(double, safetyFactor)
    Q_MEMBER(QString, factory)
    Q_MEMBER(QString, model)
    Q_MEMBER(QString, sn)
    Q_MEMBER(QDateTime, createDate)
    Q_MEMBER(QString, createUser)
    Q_MEMBER(QString, description)
    Q_MEMBER(QDateTime, updateDate)
    Q_MEMBER(QString, updateUser)
    Q_MEMBER(QByteArray, icon)
    Q_MEMBER(QString, name)
    Q_MEMBER(double, wallThickness)
    Q_MEMBER(QString, grade)
    Q_MEMBER(double, density)
    Q_MEMBER(double, toMD)
    Q_MEMBER(double, ID)
    Q_MEMBER(double, roughness)
    Q_MEMBER(double, thermal)
    Q_MEMBER(double, cementTop)
    Q_MEMBER(double, cementDensity)
    Q_MEMBER(double, cementTheramlCond)
};
