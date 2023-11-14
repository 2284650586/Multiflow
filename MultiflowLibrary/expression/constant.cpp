#include "constant.hpp"

#include <string>

std::string removingTailingZeros(const std::string& str) {
    if (str.find('.') == std::string::npos) {
        // Not a floating point number?
        return str;
    }
    size_t strEnd = str.find_last_not_of('0');
    if (strEnd == std::string::npos) {
        return "";
    }
    if (str[strEnd] == '.') {
    // Remove the decimal point as well if it is the last character.
        --strEnd;
    }
    return str.substr(0, strEnd + 1);
}

namespace ml {
Constant::Constant(const std::string& name, const std::string& description, const Number value)
    : Expression(name, description),
      _value(value) {
}

Number Constant::evaluate(const Environment& env) const {
    return _value;
}

std::string Constant::to_string() const {
    return removingTailingZeros(std::to_string(_value));
}
}
