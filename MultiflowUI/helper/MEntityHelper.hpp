//
// Created by Hatsune Miku on 2023-11-23.
//

#pragma once

#include "entity/MEntity.hpp"
#include "expression/environment.hpp"

class MEntityHelper {
protected:
    MEntity* _entity;

public:
    explicit MEntityHelper(MEntity* entity = nullptr);

    void setEntity(MEntity* entity);

    MProperty operator[](const char* property) const;

    ml::Number valueAtUnit(const char* property, const char* unit) const;

    ml::Number ivValueAtUnit(ml::Number value, const char* property, const char* unit) const;
};
