#include "add.h"

#include "math/math.h"

namespace expression
{

Add::Add(const Expression& x, const Expression& y):
    Expression("Add", "Add"),
    _x(x),
    _y(y)
{

}

Expression::Number Add::evaluate() const
{
    // 哪怕是最最基本的两数相加，也将其逻辑抽离开来，放到math模块中
    // 也许未来会需要引入大整数等操作呢
    return math::add(_x.evaluate(), _y.evaluate());
}

QString Add::to_string() const
{
    return "(" + _x.to_string() + " + " + _y.to_string() + ")";
}

}
