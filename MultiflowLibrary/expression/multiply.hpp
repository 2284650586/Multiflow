//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression.hpp"

#include <string>
#include <vector>

namespace ml {
    class  __declspec(dllexport) Multiply : public Expression {
    private:
        std::vector<std::shared_ptr<Expression>> _operands;

    public:
        explicit Multiply(std::vector<std::shared_ptr<Expression>> _operands);

        [[nodiscard]]
        ml::Number evaluate(const Environment &env) const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        std::vector<std::shared_ptr<Expression>> operands() const override;
    };
}
