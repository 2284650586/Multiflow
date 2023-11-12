#pragma once

#include "expression.hpp"

#include <string>

namespace ml
{

/**
 * @brief 未知数表达式，在表达式中扮演未知数（自变量）的角色
 * @author z
 */
class  __declspec(dllexport) Variable: public Expression
{
public:
    Variable(const std::string& name, const std::string& description);

    [[nodiscard]]
    ml::Number evaluate(const Environment& env) const override;

    [[nodiscard]]
    std::string to_string() const override;
};

}
