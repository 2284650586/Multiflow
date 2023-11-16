//
// Created by miku on 11/5/2023.
//

#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml {
class ML_PUBLIC Multiply final : public Expression {
    std::vector<std::shared_ptr<Expression>> _operands;

public:
    explicit Multiply(std::vector<std::shared_ptr<Expression>> operands);

    [[nodiscard]]
    Number evaluate(const Environment& env) const override;

    [[nodiscard]]
    std::string representation() const override;

    [[nodiscard]]
    const std::vector<std::shared_ptr<Expression>>& operands() const override;
};
}
