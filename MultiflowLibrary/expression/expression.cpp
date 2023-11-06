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

std::vector<Expression> Expression::operands() const {
    throw NotImplementedException();
}

}

std::string joinArray(const std::vector<std::string>& v, const std::string& delimiter) {
    std::stringstream ss{};
    for (auto it = v.begin(); it != v.end(); ++it) {
        ss << *it;
        if (it != v.end() - 1) {
            ss << delimiter;
        }
    }
    return ss.str();
}

std::string join(const std::vector<ml::Expression>& v, const std::string& delimiter) {
    std::vector<std::string> mappedOperands;
    std::transform(v.begin(), v.end(), std::back_inserter(mappedOperands), [] (const ml::Expression& exp) {
        return exp.to_string();
    });
    return "(" + joinArray(mappedOperands, delimiter) + ")";
}
