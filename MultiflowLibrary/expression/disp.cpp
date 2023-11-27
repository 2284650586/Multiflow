//
// Created by Hatsune Miku on 2023-11-27.
//

#include "disp.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <numeric>
#include <logging/logging.hpp>

namespace ml
{
Disp::Disp(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Display", "Display"), _operands(std::move(operands)) {}

Number Disp::evaluate(Environment& env) {
    Number last = 0;
    std::ranges::for_each(_operands, [&env, &last] (const auto& operand) {
        last = operand->evaluate(env);
        log_info("DISP: {} = {}", operand->name(), last);
    });
    return last;
}

std::string Disp::representation() const {
    return "Disp" + joinExpression(_operands, " ");
}

const std::vector<std::shared_ptr<Expression>>& Disp::operands() const {
    return _operands;
}
}
