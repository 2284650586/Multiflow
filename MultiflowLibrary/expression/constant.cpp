#include "constant.hpp"

#include <string>

namespace ml {

const Constant Constant::pi = Constant("PI", "圆周率", 3.14159265358979323846);
const Constant Constant::e = Constant("e", "自然对数", 2.71828182845904523536);

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
