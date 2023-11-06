//
// Created by miku on 11/5/2023.
//

#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml
{

/**
 * @brief 加法表达式，指示两个表达式相加
 *
 * @author z
 */
    class ML_PUBLIC Subtract: public Expression
    {
    private:
        const Expression& _x;
        const Expression& _y;

    public:
        Subtract(const Expression& x, const Expression& y);

        ml::Number evaluate(const Environment& env) const override;

        std::string to_string() const override;

        std::vector<Expression> operands() const override;
    };

}
