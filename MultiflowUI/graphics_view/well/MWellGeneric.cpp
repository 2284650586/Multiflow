//
// Created by Hatsune Miku on 2023-11-23.
//

#include "MWellGeneric.hpp"

double MWellGeneric::l(const double percent) const {
    return _coordinateHelper->left(percent);
}

double MWellGeneric::t(const double percent) const {
    return _coordinateHelper->top(percent);
}

double MWellGeneric::hc(const double offsetPercent) const {
    return _coordinateHelper->hcenter(offsetPercent);
}

double MWellGeneric::vc(const double offsetPercent) const {
    return _coordinateHelper->vcenter(offsetPercent);
}

MWellGeneric::MWellGeneric(MEntity* well, MIndependentVariables* iv)
    : _well(MEntityHelper{well}),
      _iv(iv),
      _coordinateHelper(CoordinateHelper::getInstance()) {
}
