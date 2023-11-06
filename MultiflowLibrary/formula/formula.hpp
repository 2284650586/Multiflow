//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression/expression.hpp"
#include "expression/variable.hpp"

#include <string>
#include <vector>

namespace ml {

class Formula {
private:
    std::string _name;
    std::string _description;
    Expression _expression;

public:
    explicit Formula(std::string name, std::string description, const Expression& expression);
    virtual ~Formula() = default;

    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] const std::string& description() const;
    [[nodiscard]] const Expression& expression() const;

    /**
     * @brief 递归地提取表达式中的参数，不应该反复调用
     * @return
     */
    [[nodiscard]] std::vector<Variable> extractVariables() const;
};

}
