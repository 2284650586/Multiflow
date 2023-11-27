//
// Created by Hatsune Miku on 2023-11-26.
//

#include "PvtCalculationUnit.hpp"

PvtCalculationUnit::PvtCalculationUnit(QObject* parent): AbstractCalculationUnit(parent) {
}

QVector<QVector<QVector<ml::Number>>> PvtCalculationUnit::evaluate(const QString& category) const {
    return {};
}
