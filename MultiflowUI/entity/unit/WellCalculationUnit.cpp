//
// Created by miku on 11/21/2023.
//

#include "WellCalculationUnit.hpp"

#include <logging/logging.hpp>
#include <math/math.hpp>

using ml::Number;

// 作孽啊
QVector<QVector<QVector<Number>>> WellCalculationUnit::reservoirPressure() const {
    QVector<QVector<QVector<Number>>> ret{};

    for (const auto& variables = _independentVariables->get("completions");
         const auto& variable: variables) {
        QVector<QVector<Number>> reservoirPressure{};

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
            reservoirPressure.push_back({ pwf, result });
            pwf -= 1;
        }
        ret.push_back(reservoirPressure);
    }
    return ret;
}

WellCalculationUnit::WellCalculationUnit(QObject* parent): AbstractCalculationUnit(parent) {
}

QVector<QVector<QVector<Number>>> WellCalculationUnit::evaluate(const QString& category) const {
    if (category == "completions") {
        return reservoirPressure();
    }
    return {};
}
