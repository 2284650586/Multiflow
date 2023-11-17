//
// Created by miku on 11/15/2023.
//

#include "formula_utils.hpp"

#include <algorithm>

#include "expression/closure.hpp"
#include "utils/type_utils.hpp"
#include "expression/variable.hpp"
#include "expression/constant.hpp"
#include "expression/referencing_function.hpp"

struct IgnoredVariable {
    std::shared_ptr<ml::Expression> closure;
    std::shared_ptr<ml::Expression> variable;
};

namespace ml {
// NOLINTNEXTLINE
static void __internalExtractVariablesAndConstants(
    const std::shared_ptr<Expression>& expression,
    std::vector<std::shared_ptr<Expression>>& ret,
    std::vector<IgnoredVariable>& ignoredVariables,
    const std::shared_ptr<Expression>& enclosingClosure
) {
    const bool isConstant = ml::instance_of<Constant>(expression);
    const bool isVariable = ml::instance_of<Variable>(expression);
    const bool isClosure = ml::instance_of<Closure>(expression);

    // Skip variables that should be ignored.
    if (isVariable) {
        if (std::ranges::any_of(ignoredVariables, [&expression](const auto& iv) {
            return expression->name() == iv.variable->name();
        })) {
            return;
        }
        if (ml::as<Variable>(expression)->shouldIgnore()) {
            ignoredVariables.emplace_back(IgnoredVariable{enclosingClosure, expression});
            return;
        }
    }

    if (isConstant || isVariable) {
        // Skip raw numbers.
        if (expression->name() != "Constant") {
            ret.push_back(expression);
        }
        return;
    }

    try {
        const auto& operands = expression->operands();
        auto it = operands.begin();

        // Skip the first operand for referencing functions.
        if (ml::instance_of<ReferencingFunction>(expression)) {
            ++it;
        }

        for (; it != operands.end(); ++it) {
            __internalExtractVariablesAndConstants(
                *it,
                ret,
                ignoredVariables,
                isClosure ? expression : nullptr
            );
        }
    }
    catch (const NotImplementedException&) {
    }

    if (isClosure) {
        // Closure finished. Remove ignored variables.
        std::erase_if(ignoredVariables, [&enclosingClosure] (const IgnoredVariable& iv) {
            return iv.closure == enclosingClosure;
        });
    }
}

void _internalExtractVariablesAndConstants(
    const std::shared_ptr<Expression>& expression,
    std::vector<std::shared_ptr<Expression>>& ret
) {
    std::vector<IgnoredVariable> ignoredVariables{};
    __internalExtractVariablesAndConstants(expression, ret, ignoredVariables, nullptr);
}
}
