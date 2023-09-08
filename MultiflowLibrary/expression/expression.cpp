#include "expression.h"

#include <stdexcept>

namespace expression
{

Expression::Expression(const QString& name, const QString& description):
    _name(name),
    _description(description)
{

}

Expression::~Expression()
{

}

Expression::Number Expression::evaluate() const
{
    throw std::runtime_error("Not implemented");
}

QString Expression::to_string() const
{
    throw std::runtime_error("Not implemented");
}

const QString& Expression::name() const
{
    return _name;
}

const QString& Expression::description() const
{
    return _description;
}

}
