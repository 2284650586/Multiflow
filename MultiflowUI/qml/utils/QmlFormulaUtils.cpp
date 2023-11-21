//
// Created by miku on 11/21/2023.
//

#include "QmlFormulaUtils.hpp"

#include "service/FormulaService.hpp"
#include "qml/model/QmlFormula.hpp"

QmlFormulaUtils::QmlFormulaUtils(QObject* parent)
    : QObject(parent), IQmlSingleton("Multiflow.UI", 1, 0, "QmlFormulaUtils") {
}

QmlFormula QmlFormulaUtils::formula(const QString& name) {
    return QmlFormula{FormulaService::getInstance()->formula(name)};
}
