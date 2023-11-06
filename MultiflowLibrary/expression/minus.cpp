//
// Created by miku on 11/5/2023.
//

#include "minus.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>

namespace ml {
    Minus::Minus(std::shared_ptr<Expression> v) :
        Expression("Minus", "Minus"),
        _v(std::move(v)) {}

    ml::Number Minus::evaluate(const Environment &env) const {
        return ml::subtract(0, _v->evaluate(env));
    }

    std::string Minus::to_string() const {
        return "-" + _v->to_string();
    }

    std::vector<std::shared_ptr<Expression>> Minus::operands() const {
        return {_v};
    }
}
