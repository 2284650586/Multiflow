#include "constant.hpp"

#include <string>

namespace ml {

const Constant Constant::pi = Constant("PI", 3.14159265358979323846, "圆周率");
const Constant Constant::e = Constant("e", 2.71828182845904523536, "自然对数的底");

Constant::Constant(const std::string& name, ml::Number value, const std::string& description):
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
