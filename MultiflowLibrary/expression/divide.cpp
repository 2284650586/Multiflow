//
// Created by miku on 11/5/2023.
//

#include "divide.hpp"

#include "math/math.hpp"

#include <vector>

namespace ml
{
    Divide::Divide(const Expression& x, const Expression& y):
        Expression("Divide", "Divide"),
        _x(x),
        _y(y)
    {

    }

    ml::Number Divide::evaluate(const Environment& env) const
    {
        return ml::divide(_x.evaluate(env), _y.evaluate(env));
    }

    std::string Divide::to_string() const
    {
        return "(" + _x.to_string() + " / " + _y.to_string() + ")";
    }

    std::vector<Expression> Divide::operands() const {
        return std::vector<Expression>{ _x, _y };
    }
}
