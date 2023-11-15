#pragma once

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>

namespace ml {
/**
 * @brief 未知数表达式，在表达式中扮演未知数（自变量）的角色
 * @author z
 */
class ML_PUBLIC Variable final : public Expression {
public:
    Variable(const std::string& name, const std::string& description);

    [[nodiscard]]
    Number evaluate(const Environment& env) const override;

    [[nodiscard]]
    std::string representation() const override;
};
}
