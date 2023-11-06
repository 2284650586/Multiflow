//
// Created by miku on 11/5/2023.
//

#include "multiply.hpp"

#include "math/math.hpp"

#include <vector>

namespace ml
{
    Multiply::Multiply(const Expression& x, const Expression& y):
        Expression("Multiply", "Multiply"),
        _x(x),
        _y(y)
    {

    }

    ml::Number Multiply::evaluate(const Environment& env) const
    {
        return ml::multiply(_x.evaluate(env), _y.evaluate(env));
    }

    std::string Multiply::to_string() const
    {
        return "(" + _x.to_string() + " * " + _y.to_string() + ")";
    }

    std::vector<Expression> Multiply::operands() const {
        return std::vector<Expression>{ _x, _y };
    }
}
