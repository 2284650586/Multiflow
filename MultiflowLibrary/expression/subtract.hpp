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
    class ML_PUBLIC Subtract: public Expression
    {
    private:
        std::vector<Expression> _operands;

    public:
        Subtract(std::vector<Expression>_operands);

        /**
         * @brief 计算相加结果
         */
        ml::Number evaluate(const Environment &env) const override;

        std::string to_string() const override;

        std::vector<Expression> operands() const override;
    };
}
