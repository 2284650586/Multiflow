//
// Created by miku on 11/16/2023.
//

#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

struct SetqPair {
    std::shared_ptr<ml::Expression> expression;
    std::shared_ptr<ml::Expression> value;
};

namespace ml {
class ML_PUBLIC SetEnvironment final : public Expression {
    std::vector<std::shared_ptr<Expression>> _operands;
    std::vector<SetqPair> _setqPairs;

public:
    explicit SetEnvironment(std::vector<std::shared_ptr<Expression>> operands);

    [[nodiscard]]
    Number evaluate(Environment& env) override;

    [[nodiscard]]
    std::string representation() const override;

    [[nodiscard]]
    const std::vector<std::shared_ptr<Expression>>& operands() const override;
};
}
