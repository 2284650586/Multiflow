//
// Created by Hatsune Miku on 2023-11-23.
//

#include "MEntityHelper.hpp"

#include "unit_converter/AbstractUnitConverter.hpp"

MEntityHelper::MEntityHelper(MEntity* entity): _entity(entity) {
}

void MEntityHelper::setEntity(MEntity* entity) {
    _entity = entity;
}

MProperty MEntityHelper::operator[](const char* property) const {
    return _entity->operator[](property).value<MProperty>();
}

ml::Number MEntityHelper::valueAtUnit(const char* property, const char* unit) const {
    const auto propertyObject = operator[](property);
    const auto value = propertyObject.value.value<ml::Number>();
    return ivValueAtUnit(value, property, unit);
}

ml::Number MEntityHelper::ivValueAtUnit(const ml::Number value, const char* property, const char* unit) const {
    const auto propertyObject = operator[](property);
    const auto* converter = propertyObject.extra.value<AbstractUnitConverter*>();
    const auto currentUnit = propertyObject.associateValue.value<QString>();
    return converter->convert(value, currentUnit, unit);
}
