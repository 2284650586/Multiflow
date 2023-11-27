//
// Created by miku on 11/5/2023.
//

#include "formula.hpp"
#include "expression/expression.hpp"
#include "utils/type_utils.hpp"
#include "utils/formula_utils.hpp"
#include "logging/logging.hpp"

#include <utility>

namespace ml {
Formula::Formula(std::string id, std::string name, std::string description, std::shared_ptr<Expression> expression,
                 std::string lisp)
    : _id(std::move(id)),
      _name(std::move(name)),
      _description(std::move(description)),
      _expression(std::move(expression)),
      _lisp(std::move(lisp)) {
}

const std::string& Formula::id() const {
    return _id;
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
    return ret;
}
}
