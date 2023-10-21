#include "variable.hpp"

namespace expression
{

Variable::Variable(const QString& name, Expression::Number value, const QString& description):
    Expression(name, description),
    _value(value)
{

}

void Variable::set_value(Expression::Number value)
{
    _value = value;
}

Expression::Number Variable::evaluate() const
{
    return _value;
}

QString Variable::to_string() const
{
    return _name;
}

}
