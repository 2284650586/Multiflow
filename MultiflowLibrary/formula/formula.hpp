//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression/expression.hpp"
#include "expression/variable.hpp"

#include <string>
#include <vector>

namespace ml {

class ML_PUBLIC Formula {
private:
    std::string _name;
    std::string _description;
    std::shared_ptr<Expression> _expression;

public:
    explicit Formula(std::string name, std::string description, std::shared_ptr<Expression> expression);
    virtual ~Formula() = default;

    [[nodiscard]]
    const std::string& name() const;

    [[nodiscard]]
    const std::string& description() const;

    [[nodiscard]]
    std::shared_ptr<Expression> expression() const;

    /**
     * @brief 递归地提取表达式中的参数，不应该反复调用
     * @return
     */
    [[nodiscard]]
    std::vector<std::shared_ptr<Variable>> extractVariables() const;
};

}
