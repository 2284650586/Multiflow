//
// Created by Hatsune Miku on 2023-11-23.
//

#pragma once

#include "entity/MEntity.hpp"

#include <QString>

class MEntityHelper {
protected:
    MEntity* _entity;

public:
    explicit MEntityHelper(MEntity* entity);

    MEntityHelper operator[](const char* property) const;

    QString str(const char* property) const;

    double num(const char* property) const;
};
