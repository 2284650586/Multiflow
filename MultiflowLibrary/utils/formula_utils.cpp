//
// Created by miku on 11/15/2023.
//

#include "formula_utils.hpp"

#include <logging/logging.hpp>

#include "utils/type_utils.hpp"
#include "expression/variable.hpp"
#include "expression/constant.hpp"
#include "expression/referencing_function.hpp"

namespace ml {
// NOLINTNEXTLINE
void _internalExtractVariablesAndConstants(
    const std::shared_ptr<Expression>& expression,
    std::vector<std::shared_ptr<Expression>>& ret
) {
    if (ml::instance_of<Variable>(expression) || ml::instance_of<Constant>(expression)) {
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
            _internalExtractVariablesAndConstants(*it, ret);
        }
    }
    catch (const NotImplementedException&) {}
}
}
