//
// Created by miku on 11/5/2023.
//

#include "formula.hpp"
#include "expression/variable.hpp"

#include "utils/type_utils.hpp"

static void _internalExtractVariables(const ml::Expression& expression, std::vector<ml::Variable>& ret) {
    if (ml::instance_of<ml::Variable>(expression)) {
        ret.push_back(dynamic_cast<const ml::Variable&>(expression));
        return;
    }

    try {
        const auto& operands = expression.operands();
        for (const auto& operand : operands) {
            _internalExtractVariables(operand, ret);
        }
    }
    catch (const std::exception& e) {}
}

namespace ml {
    Formula::Formula(std::string name, std::string description, const Expression& expression) :
        _name(std::move(name)),
        _description(std::move(description)),
        _expression(expression) {

    }

    const std::string &Formula::name() const {
        return _name;
    }

    const std::string &Formula::description() const {
        return _description;
    }

    const Expression &Formula::expression() const {
        return _expression;
    }

    std::vector<Variable> Formula::extractVariables() const {
        std::vector<Variable> ret{};
        _internalExtractVariables(_expression, ret);
        return ret;
    }
}
