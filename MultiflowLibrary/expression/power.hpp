//
// Created by miku on 11/9/2023.
//

#pragma once

#include "MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>
#include <memory>

namespace ml {
class ML_PUBLIC Power final : public Expression {
    std::vector<std::shared_ptr<Expression>> _operands;

public:
    explicit Power(std::vector<std::shared_ptr<Expression>> operands);

    [[nodiscard]]
    Number evaluate(Environment& env) override;

    [[nodiscard]]
    std::string representation() const override;

    [[nodiscard]]
    const std::vector<std::shared_ptr<Expression>>& operands() const override;
};
}
