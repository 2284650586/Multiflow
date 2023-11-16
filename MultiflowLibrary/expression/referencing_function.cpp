//
// Created by miku on 11/15/2023.
//

#include "referencing_function.hpp"
#include "environment.hpp"
#include "utils/formula_utils.hpp"
#include "math/math.hpp"

#include <utility>
#include <vector>
#include <numeric>
#include <sstream>
#include <logging/logging.hpp>

#include "variable.hpp"
#include "utils/type_utils.hpp"

namespace ml {
ReferencingFunction::ReferencingFunction(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("ReferencingFunction", "ReferencingFunction"), _operands(std::move(operands)) {
    if (_operands.empty()) {
        // Object reference not set to an instance of an object :)
        // 引用函数是由内部构造的，如果出现 empty 情况，说明是内部错误
        throw MalformedExpressionException("ReferencingFunction requires at least one operand.");
    }
}

Number ReferencingFunction::evaluate(const Environment& env) const {
    const auto fun = _operands[0];
    int operandIndex = 1;

    // Traverse all variables.
    std::vector<std::shared_ptr<Expression>> variables{};
    _internalExtractVariablesAndConstants(fun, variables);

    if (variables.size() != _operands.size() - 1) {
        const std::string errorMessage = std::format(
            "调用 {} 需要 {} 个参数，但是只给了 {} 个",
            fun->name(), variables.size(), _operands.size() - 1
        );
        throw MalformedExpressionException(errorMessage.c_str());
    }

    // Create isolated environment.
    Environment isolatedEnv{};
    for (const auto& variable: variables) {
        if (ml::instance_of<Variable>(variable)) {
            // Evaluate operands using current environment.
            // We assume the orders of operands and variables are the same.
            const auto correspondingOperand = _operands[operandIndex++];
            const Number actualValue = correspondingOperand->evaluate(env);
            isolatedEnv.set(variable->name(), actualValue);
            log_debug(
                "Binding {}.{} to {}, with value {}.",
                fun->name(), variable->name(), correspondingOperand->name(), actualValue);
        }
    }
    return fun->evaluate(isolatedEnv);
}

std::string ReferencingFunction::representation() const {
    std::stringstream ss;
    auto it = _operands.begin();
    ss << (*it)->name() << "(";
    while (++it != _operands.end()) {
        ss << (*it)->representation();
        if (it != _operands.end() - 1) {
            ss << ", ";
        }
    }
    ss << ")";
    return ss.str();
}

const std::vector<std::shared_ptr<Expression>>& ReferencingFunction::operands() const {
    return _operands;
}
}
