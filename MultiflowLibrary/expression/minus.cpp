//
// Created by miku on 11/5/2023.
//

#include "minus.hpp"

#include "math/math.hpp"

#include <vector>

namespace ml {
    Minus::Minus(const Expression &v) :
        Expression("Minus", "Minus"),
        _v(v) {}

    ml::Number Minus::evaluate(const Environment &env) const {
        return ml::subtract(0, _v.evaluate(env));
    }

    std::string Minus::to_string() const {
        return "-" + _v.to_string();
    }

    std::vector<Expression> Minus::operands() const {
        return std::vector<Expression>{_v};
    }
}
