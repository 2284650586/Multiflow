//
// Created by miku on 11/5/2023.
//

#include "subtract.hpp"

#include "math/math.hpp"

#include <vector>

namespace ml
{
    Subtract::Subtract(const Expression& x, const Expression& y):
        Expression("Subtract", "Subtract"),
        _x(x),
        _y(y)
    {

    }

    ml::Number Subtract::evaluate(const Environment& env) const
    {
        return ml::subtract(_x.evaluate(env), _y.evaluate(env));
    }

    std::string Subtract::to_string() const
    {
        return "(" + _x.to_string() + " - " + _y.to_string() + ")";
    }

    std::vector<Expression> Subtract::operands() const {
        return std::vector<Expression>{ _x, _y };
    }
}
