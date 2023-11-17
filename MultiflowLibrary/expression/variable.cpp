#include "variable.hpp"

namespace ml {
Variable::Variable(const std::string& name, const std::string& description)
    : Expression(name, description) {
}

Number Variable::evaluate(Environment& env) {
    return env.get(_name);
}

std::string Variable::representation() const {
    return _name;
}

/**
 * @brief Should be ignored (hide from UI) when evaluating the expression.
 * This is useful for `setq`, which is a special instruction that defines a variable.
 */
bool Variable::shouldIgnore() const {
    return _shouldIgnore;
}

void Variable::setShouldIgnore(const bool shouldIgnore) {
    _shouldIgnore = shouldIgnore;
}
}
