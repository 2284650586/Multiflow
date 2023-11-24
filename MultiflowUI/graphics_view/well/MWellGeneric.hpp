//
// Created by Hatsune Miku on 2023-11-23.
//

#pragma once

#include "helper/CoordinateHelper.hpp"
#include "helper/MEntityHelper.hpp"
#include "entity/MEntity.hpp"
#include "entity/MIndependentVariables.hpp"

class MWellGeneric {
protected:
    CoordinateHelper* _coordinateHelper;
    MEntityHelper _well;
    MIndependentVariables* _iv;

    [[nodiscard]] double l(double percent) const;

    [[nodiscard]] double t(double percent) const;

    [[nodiscard]] double hc(double offsetPercent = 0) const;

    [[nodiscard]] double vc(double offsetPercent = 0) const;

public:
    explicit MWellGeneric(MEntity* well, MIndependentVariables* iv);

    virtual ~MWellGeneric() = default;
};
