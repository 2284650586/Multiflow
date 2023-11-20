#pragma once

#include "component/well/MWellDeviation.hpp"
#include "component/well/MWellCasing.hpp"
#include "component/well/MWellTunbing.h"
#include "component/well/MWellPacker.hpp"
#include "component/well/MWellHeat.hpp"
#include "entity/common.hpp"

#include <QString>

enum WellKind {
    Production,
    Injection
};

struct MWell {
    Q_GADGET

public:
    Q_MEMBER(QString, name)
    Q_MEMBER(WellKind, kind)
    Q_MEMBER(MWellDeviation, deviation)
    Q_MEMBER(MWellHeat, heat)
    Q_MEMBER(QList<MWellCasing>, casings)
    Q_MEMBER(QList<MWellTunbing>, tubings)
    Q_MEMBER(QList<MWellPacker>, packers)
};

Q_DECLARE_METATYPE(MWell)
