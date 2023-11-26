//
// Created by miku on 11/26/2023.
//

#include "FluidDataService.hpp"
#include "qml/utils/UIUtils.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

QString FluidDataService::categoryBlackOil() {
    return "BlackOil";
}

void FluidDataService::loadData() {
    _iv = new MIndependentVariables{};
    emit dataLoaded();
}

MIndependentVariables* FluidDataService::iv() const {
    return _iv;
}
