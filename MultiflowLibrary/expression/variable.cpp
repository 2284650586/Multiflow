#include "variable.hpp"

namespace ml {
Variable::Variable(const std::string& name, const std::string& description)
    : Expression(name, description) {
}

Number Variable::evaluate(const Environment& env) const {
    return env.get(_name);
}

std::string Variable::to_string() const {
    return _name;
}
}
