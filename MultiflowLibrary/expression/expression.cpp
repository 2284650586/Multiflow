#include "expression.hpp"

namespace ml
{

Expression::Expression(std::string name, std::string description):
    _name(std::move(name)),
    _description(std::move(description))
{

}

Expression::~Expression()
{

}

ml::Number Expression::evaluate(const Environment& env) const
{
    throw NotImplementedException();
}

std::string Expression::to_string() const
{
    throw NotImplementedException();
}

const std::string& Expression::name() const
{
    return _name;
}

const std::string& Expression::description() const
{
    return _description;
}

const std::vector<Expression> Expression::operands() const {
    throw NotImplementedException();
}

}
