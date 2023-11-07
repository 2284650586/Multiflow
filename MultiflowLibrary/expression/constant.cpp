#include "constant.hpp"

#include <string>

namespace ml {

Constant::Constant(const std::string& name, const std::string& description, ml::Number value):
    Expression(name, description),
    _value(value)
{

}

ml::Number Constant::evaluate(const Environment& env) const
{
    return _value;
}

std::string Constant::to_string() const
{
    return std::to_string(_value);
}

}
