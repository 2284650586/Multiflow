//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression.hpp"

namespace ml {

class Minus : public Expression {
private:
    const Expression& _v;

public:
    Minus(const Expression& v);

    ml::Number evaluate(const ml::Environment &env) const override;

    std::vector<Expression> operands() const override;

    std::string to_string() const override;
};

}
