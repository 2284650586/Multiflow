//
// Created by Hatsune Miku on 2023-11-26.
//

#include "PVTService.hpp"

#include "EntityService.hpp"

void PVTService::loadData() {
    _iv = new MIndependentVariables{};
    _cu = new PvtCalculationUnit{};
    _entity = EntityService::getInstance()->createEntity("MPVT");
}

PVTService::~PVTService() {
    delete _iv;
    delete _cu;
}

MEntity* PVTService::entity() const {
    return _entity;
}

PvtCalculationUnit* PVTService::cu() const {
    return _cu;
}

QString PVTService::category() {
    return "pvt";
}

MIndependentVariables* PVTService::iv() const {
    return _iv;
}
