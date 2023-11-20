#pragma once

#include <QVariant>

#include "entity/common.hpp"

struct MDeviationParameter {
    Q_GADGET

public:
    Q_MEMBER(double, MD)
    Q_MEMBER(double, TVD)
    Q_MEMBER(double, horizontalDisplacement)
    Q_MEMBER(double, angle)
    Q_MEMBER(double, azimuth)
    Q_MEMBER(double, maxDog)
};
