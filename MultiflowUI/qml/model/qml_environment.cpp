//
// Created by miku on 11/9/2023.
//

#include "qml_environment.hpp"

QmlEnvironment::QmlEnvironment()
     : IQmlObject<QmlEnvironment>("Multiflow.UI", 1, 0, "QmlEnvironment") {
}

ml::Number QmlEnvironment::get(const QString& name) const {
    return _environment->get(name.toStdString());
}

void QmlEnvironment::set(const QString& name, const ml::Number& value) {
    return _environment->set(name.toStdString(), value);
}

void QmlEnvironment::setVariableNames(const QVariantList& variables) {
    _variables = variables;
    ml::Environment env;
    for (const auto& variable: variables) {
        auto key = variable.value<QString>();
        env.set(key.toStdString(), static_cast<ml::Number>(0));
    }
    _environment = std::make_shared<ml::Environment>(env);
}

const QVariantList& QmlEnvironment::variableNames() const {
    return _variables;
}
