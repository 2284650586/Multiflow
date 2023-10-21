#include "constant.hpp"

namespace expression {

const Constant Constant::pi = Constant("PI", 3.14159265358979323846, "圆周率");
const Constant Constant::e = Constant("e", 2.71828182845904523536, "自然对数的底");

Constant::Constant(const QString& name, Expression::Number value, const QString& description):
    Expression(name, description),
    _value(value)
{

}

Expression::Number Constant::evaluate() const
{
    return _value;
}

QString Constant::to_string() const
{
    return QString::number(_value);
}

}
