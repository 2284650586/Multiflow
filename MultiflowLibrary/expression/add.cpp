#include "add.hpp"

#include "math/math.hpp"

#include <vector>

namespace ml
{

Add::Add(const Expression& x, const Expression& y):
    Expression("Add", "Add"),
    _x(x),
    _y(y)
{

}

ml::Number Add::evaluate(const Environment& env) const
{
    // 哪怕是最最基本的两数相加，也将其逻辑抽离开来，放到math模块中
    // 也许未来会需要引入大整数等操作呢
    return ml::add(_x.evaluate(env), _y.evaluate(env));
}

std::string Add::to_string() const
{
    return "(" + _x.to_string() + " + " + _y.to_string() + ")";
}

const std::vector<Expression> Add::operands() const {
    return std::vector<Expression>{ _x, _y };
}

}
