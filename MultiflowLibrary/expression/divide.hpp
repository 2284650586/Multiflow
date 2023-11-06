//
// Created by miku on 11/5/2023.
//

#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml {
    class ML_PUBLIC Divide : public Expression {
    private:
        std::vector<std::shared_ptr<Expression>> _operands;

    public:
        explicit Divide(std::vector<std::shared_ptr<Expression>> _operands);

        [[nodiscard]]
        ml::Number evaluate(const Environment &env) const override;

        [[nodiscard]]
        std::string to_string() const override;

        [[nodiscard]]
        std::vector<std::shared_ptr<Expression>> operands() const override;
    };
}
