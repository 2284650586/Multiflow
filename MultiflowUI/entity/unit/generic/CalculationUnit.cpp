//
// Created by miku on 11/21/2023.
//

#include "CalculationUnit.hpp"

#include <logging/logging.hpp>

CalculationUnit::CalculationUnit(QObject* parent): QObject(parent) {
}

void CalculationUnit::update(const QVariant& entity, const QVariant& independentVariables) {
    _entity = dynamic_cast<MEntity*>(entity.value<QQmlPropertyMap*>());
    _independentVariables = independentVariables.value<MIndependentVariables*>();
    _helper.setEntity(_entity);

    log_debug("Entity properties ({})", _entity->count());
}
