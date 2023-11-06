//
// Created by miku on 11/5/2023.
//

#include "formula.hpp"

#include <utility>
#include "expression/variable.hpp"

#include "utils/type_utils.hpp"

static void _internalExtractVariables(
    const std::shared_ptr<ml::Expression>& expression,
    std::vector<std::shared_ptr<ml::Variable>>& ret
) {
    if (ml::instance_of<ml::Variable>(expression)) {
        ret.push_back(std::dynamic_pointer_cast<ml::Variable>(expression));
        return;
    }

    try {
        const auto& operands = expression->operands();
        for (const auto& operand : operands) {
            _internalExtractVariables(operand, ret);
        }
    }
    catch (const std::exception& e) {}
}

namespace ml {
    Formula::Formula(std::string name, std::string description, std::shared_ptr<Expression> expression) :
        _name(std::move(name)),
        _description(std::move(description)),
        _expression(std::move(expression)) {

    }

    const std::string &Formula::name() const {
        return _name;
    }

    const std::string &Formula::description() const {
        return _description;
    }

    std::shared_ptr<Expression> Formula::expression() const {
        return _expression;
    }

    std::vector<std::shared_ptr<Variable>> Formula::extractVariables() const {
        std::vector<std::shared_ptr<Variable>> ret{};
        _internalExtractVariables(_expression, ret);
        return ret;
    }
}
