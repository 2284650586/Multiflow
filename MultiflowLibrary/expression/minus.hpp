//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression.hpp"

namespace ml {

class Minus : public Expression {
private:
    const std::shared_ptr<Expression> _v;

public:
    explicit Minus(std::shared_ptr<Expression> v);

    [[nodiscard]]
    ml::Number evaluate(const ml::Environment &env) const override;

    [[nodiscard]]
    std::vector<std::shared_ptr<Expression>> operands() const override;

    [[nodiscard]]
    std::string to_string() const override;
};

}
