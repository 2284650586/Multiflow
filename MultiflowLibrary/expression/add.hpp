#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml {
class ML_PUBLIC Add final : public Expression {
    std::vector<std::shared_ptr<Expression>> _operands;

public:
    explicit Add(std::vector<std::shared_ptr<Expression>> operands);

    [[nodiscard]]
    Number evaluate(const Environment& env) const override;

    [[nodiscard]]
    std::string to_string() const override;

    [[nodiscard]]
    std::vector<std::shared_ptr<Expression>> operands() const override;
};
}
