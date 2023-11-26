//
// Created by Hatsune Miku on 2023-11-23.
//

#include "MEntityHelper.hpp"

MEntityHelper::MEntityHelper(MEntity* entity): _entity(entity) {
}

void MEntityHelper::setEntity(MEntity* entity) {
    _entity = entity;
}

MEntityHelper MEntityHelper::operator[](const char* property) const {
    auto* propertyMap = _entity->property(property).value<QQmlPropertyMap*>();
    return MEntityHelper{dynamic_cast<MEntity*>(propertyMap)};
}

QString MEntityHelper::str(const char* property) const {
    return _entity->property(property).toString();
}

double MEntityHelper::num(const char* property) const {
    return _entity->property(property).toString().toDouble();
}
