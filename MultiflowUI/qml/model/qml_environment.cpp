//
// Created by miku on 11/9/2023.
//

#include "qml_environment.hpp"

QmlEnvironment::QmlEnvironment()
    : IQmlObject("Multiflow.UI", 1, 0, "QmlEnvironment") {
}

ml::Number QmlEnvironment::get(const QString& name) const {
    return _environment->get(name.toStdString());
}

void QmlEnvironment::set(const QString& name, const ml::Number& value) const {
    return _environment->set(name.toStdString(), value);
}

void QmlEnvironment::resetValues() {
    for (const auto& variable: _variables) {
        auto key = variable.value<QString>();
        _environment->set(key.toStdString(), 0);
    }
}

void QmlEnvironment::setVariableNames(const QVariantList& variables) {
    _variables = variables;
    _environment = std::make_shared<ml::Environment>();
    resetValues();
}

const QVariantList& QmlEnvironment::variableNames() const {
    return _variables;
}
