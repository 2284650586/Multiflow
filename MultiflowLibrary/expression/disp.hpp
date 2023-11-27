//
// Created by Hatsune Miku on 2023-11-27.
//

#pragma once

#include "MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml {
class ML_PUBLIC Disp final : public Expression {
    std::vector<std::shared_ptr<Expression>> _operands;

public:
    explicit Disp(std::vector<std::shared_ptr<Expression>> operands);

    [[nodiscard]]
    Number evaluate(Environment& env) override;

    [[nodiscard]]
    std::string representation() const override;

    [[nodiscard]]
    const std::vector<std::shared_ptr<Expression>>& operands() const override;
};
}
