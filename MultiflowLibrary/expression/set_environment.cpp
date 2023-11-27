//
// Created by miku on 11/16/2023.
//

#include "set_environment.hpp"

#include <utility>
#include <vector>
#include <sstream>
#include <logging/logging.hpp>

#include "variable.hpp"
#include "utils/type_utils.hpp"

// NOLINTNEXTLINE
static std::vector<SetqPair> _parseSetq(const std::vector<std::shared_ptr<ml::Expression>>& operands) {
    std::vector<SetqPair> result;
    for (auto it = operands.begin(); it != operands.end(); it += 2) {
        const auto& expression = *it;
        const auto& value = *(it + 1);
        result.emplace_back(SetqPair{expression, value});
    }
    return result;
}

namespace ml {
SetEnvironment::SetEnvironment(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Setq", "Setq"), _operands(std::move(operands)) {
    if (_operands.size() & 1) {
        throw MalformedExpressionException("Arguments for Setq must be even");
    }
    _setqPairs = _parseSetq(_operands);
    for (auto [expression, value]: _setqPairs) {
        if (!ml::instance_of<Variable>(expression)) {
            throw MalformedExpressionException("First argument for Setq must be a variable");
        }
        ml::as<Variable>(expression)->setShouldIgnore(true);
    }
}

Number SetEnvironment::evaluate(Environment& env) {
    Number result = 0;
    for (auto [expression, value]: _setqPairs) {
        result = value->evaluate(env);
        env.set(expression->name(), result);
    }
    return result;
}

std::string SetEnvironment::representation() const {
    std::stringstream ss;
    for (auto [expression, value]: _setqPairs) {
        std::ranges::for_each(_setqPairs, [&ss, this] (const SetqPair& pair) {
            const int is_last = &pair == &_setqPairs.back();
            const auto& [expression, value] = pair;
            ss << "let " << expression->name() << " = " << value->representation() << "";
            if (!is_last) {
                ss << "\n";
            }
        });
    }
    return ss.str();
}

const std::vector<std::shared_ptr<Expression>>& SetEnvironment::operands() const {
    return _operands;
}
}
