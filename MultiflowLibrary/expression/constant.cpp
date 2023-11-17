#include "constant.hpp"

#include <string>

std::string removingFpTrailingZeros(const std::string& str) {
    if (str.find('.') == std::string::npos) {
        // Not a floating point number?
        return str;
    }
    size_t indexLastZero = str.find_last_not_of('0');
    if (indexLastZero == std::string::npos) {
        // No trailing zeros?
        return str;
    }
    if (str[indexLastZero] == '.') {
    // Remove the decimal point as well if it is the last character.
        --indexLastZero;
    }
    return str.substr(0, indexLastZero + 1);
}

namespace ml {
Constant::Constant(const std::string& name, const std::string& description, const Number value)
    : Expression(name, description),
      _value(value) {
}

Number Constant::evaluate(Environment& env) {
    return _value;
}

std::string Constant::representation() const {
    return removingFpTrailingZeros(std::to_string(_value));
}
}
