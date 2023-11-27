//
// Created by miku on 11/5/2023.
//

#pragma once

#include "expression/expression.hpp"
#include "expression/variable.hpp"

#include <string>
#include <vector>

namespace ml {
class ML_PUBLIC Formula final {
    std::string _id;
    std::string _name;
    std::string _description;
    std::string _lisp;
    std::shared_ptr<Expression> _expression;

public:
    explicit Formula(
        std::string id, std::string name, std::string description, std::shared_ptr<Expression> expression,
        std::string lisp);

    Formula() = default;

    ~Formula() = default;

    [[nodiscard]]
    const std::string& id() const;

    [[nodiscard]]
    const std::string& name() const;

    [[nodiscard]]
    const std::string& description() const;

    [[nodiscard]]
    std::shared_ptr<Expression> expression() const;

    [[nodiscard]]
    const std::string& lisp() const;

    /**
     * @brief 递归地提取表达式中的参数和常量，不应该反复调用
     * @return
     */
    [[nodiscard]]
    std::vector<std::shared_ptr<Expression>> extractVariablesAndConstants() const;
};
}
