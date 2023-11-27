//
// Created by miku on 11/21/2023.
//

#include "AbstractCalculationUnit.hpp"

#include <logging/logging.hpp>

AbstractCalculationUnit::AbstractCalculationUnit(QObject* parent): QObject(parent) {
}

void AbstractCalculationUnit::update(const QVariant& entity, const QVariant& independentVariables) {
    _entity = dynamic_cast<MEntity*>(entity.value<QQmlPropertyMap*>());
    _independentVariables = independentVariables.value<MIndependentVariables*>();
    _helper.setEntity(_entity);

    log_debug("Entity properties ({})", _entity->count());
}
