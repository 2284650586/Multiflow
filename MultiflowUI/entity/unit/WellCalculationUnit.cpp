//
// Created by miku on 11/21/2023.
//

#include "WellCalculationUnit.hpp"

#include <logging/logging.hpp>
#include <math/math.hpp>

using ml::Number;

QVector<Number> WellCalculationUnit::reservoirPressure() const {
    QVector<Number> ret{};

    for (const auto& variables = _independentVariables->get("completions");
         const auto& variable: variables) {
        const Number pr = variable["reservoir-pressure"].toDouble();
        const Number j = variable["productivity-index"].toDouble();
        const bool considerBubble = variable["vogel-below-bubble-point"].toString() == "考虑";

        const auto fPiCompletions = FormulaService::getInstance()->formula("PI-completions");
        Number pwf = pr;
        ml::Environment env{
            {"consider_bubble", considerBubble ? 1 : 0},
            {"J", j},
            {"pr", pr},
            {"pb", 0},
        };

        while (!ml::z(pwf)) {
            env.set("pwf", pwf);
            const Number result = fPiCompletions.expression()->evaluate(env);
            ret.push_back(result);
            pwf -= 1;
        }
    }
    return ret;
}

WellCalculationUnit::WellCalculationUnit(QObject* parent): CalculationUnit(parent) {
}

QVector<Number> WellCalculationUnit::evaluate(const QString& category) const {
    if (category == "completions") {
        return reservoirPressure();
    }
    return {};
}
