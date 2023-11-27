//
// Created by Hatsune Miku on 2023-11-23.
//

#include "MEntityHelper.hpp"

MEntityHelper::MEntityHelper(MEntity* entity): _entity(entity) {
}

void MEntityHelper::setEntity(MEntity* entity) {
    _entity = entity;
}

MProperty MEntityHelper::operator[](const char* property) const {
    return _entity->operator[](property).value<MProperty>();
}
