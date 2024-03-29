#include "expression.hpp"

#include <algorithm>

namespace ml {
Expression::Expression(std::string name, std::string description)
    : _name(std::move(name)),
      _description(std::move(description)) {
}

Number Expression::evaluate(Environment& env) {
    throw NotImplementedException();
}

std::string Expression::representation() const {
    throw NotImplementedException();
}

const std::string& Expression::name() const {
    return _name;
}

void Expression::setName(const std::string& name) {
    _name = name;
}

const std::string& Expression::description() const {
    return _description;
}

const std::vector<std::shared_ptr<Expression>>& Expression::operands() const {
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

std::string joinExpression(const std::vector<std::shared_ptr<ml::Expression>>& v, const std::string& delimiter) {
    std::vector<std::string> mappedOperands;
    std::ranges::transform(v, std::back_inserter(mappedOperands),
                   [](const std::shared_ptr<ml::Expression>& exp) {
                       return exp->representation();
                   });
    return "(" + joinArray(mappedOperands, delimiter) + ")";
}
