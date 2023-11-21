//
// Created by miku on 11/21/2023.
//

#include "WellReservoirUnit.hpp"

#include <logging/logging.hpp>

WellReservoirUnit::WellReservoirUnit(QObject* parent): CalculationUnit(parent) {
}

QVector<ml::Number> WellReservoirUnit::evaluate() const {
    QVector<ml::Number> ret{};

    for (const auto variables = _independentVariables->get("completions");
         const auto& variable: variables) {
        log_debug("Calculation vmap: ({})", variable.size());

        const double bd = _entity->property("bottom-depth").toDouble();
        const double wd = _entity->property("wellhead-depth").toDouble();
        const double md = variable["md"].toDouble();

        const auto formula = FormulaService::getInstance()->formula("area");
        auto env = ml::Environment{};
        env.set("r", 5);
        const double fx = formula.expression()->evaluate(env);

        ret.push_back(fx + bd - wd - md);
    }
    return std::move(ret);
}
