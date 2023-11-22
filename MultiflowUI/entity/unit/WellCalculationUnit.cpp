//
// Created by miku on 11/21/2023.
//

#include "WellCalculationUnit.hpp"

#include <logging/logging.hpp>

QVector<ml::Number> WellCalculationUnit::reservoirPressure() const {
    QVector<ml::Number> ret{};

    for (const auto variables = _independentVariables->get("completions");
         const auto& variable: variables) {
        log_debug("Calculation vmap: ({})", variable.size());

        const double bd = _entity->property("bottom-depth").toDouble();
        const double wd = _entity->property("wellhead-depth").toDouble();
        const double md = variable["md"].toDouble();

        const auto formula = FormulaService::getInstance()->formula("area");
        auto env = ml::Environment{{"r", 5}};
        const double fx = formula.expression()->evaluate(env);

        ret.push_back(fx + bd - wd - md);
         }
    return std::move(ret);
}

WellCalculationUnit::WellCalculationUnit(QObject* parent): CalculationUnit(parent) {
}

QVector<ml::Number> WellCalculationUnit::evaluate(const QString& category) const {
    if (category == "reservoir") {
        return reservoirPressure();
    }
    return {};
}
