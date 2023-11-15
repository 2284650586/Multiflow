//
// Created by miku on 11/5/2023.
//

#include "formula.hpp"

#include <utility>
#include "expression/variable.hpp"
#include "expression/constant.hpp"
#include "expression/expression.hpp"

#include "utils/type_utils.hpp"

#include "logging/logging.hpp"

// NOLINTNEXTLINE
static void _internalExtractVariablesAndConstants(
    const std::shared_ptr<ml::Expression>& expression,
    std::vector<std::shared_ptr<ml::Expression>>& ret
) {
    if (ml::instance_of<ml::Variable>(expression) || ml::instance_of<ml::Constant>(expression)) {
        // Skip raw numbers.
        if (expression->name() != "Constant") {
            ret.push_back(expression);
        }
        return;
    }

    try {
        for (const auto& operand: expression->operands()) {
            _internalExtractVariablesAndConstants(operand, ret);
        }
    }
    catch (const ml::NotImplementedException&) {}
}

namespace ml {
Formula::Formula(std::string name, std::string description, std::shared_ptr<Expression> expression, std::string lisp) :
    _name(std::move(name)),
    _description(std::move(description)),
    _expression(std::move(expression)),
    _lisp(std::move(lisp)) {

}

const std::string& Formula::name() const {
    return _name;
}

const std::string& Formula::description() const {
    return _description;
}

std::shared_ptr<Expression> Formula::expression() const {
    return _expression;
}

const std::string& Formula::lisp() const {
    return _lisp;
}
std::vector<std::shared_ptr<Expression>> Formula::extractVariablesAndConstants() const {
    std::vector<std::shared_ptr<Expression>> ret{};
    _internalExtractVariablesAndConstants(_expression, ret);
    log_info("Formula {} has {} variable(s) and constant(s).", _expression->name(), ret.size());
    return ret;
}

}
