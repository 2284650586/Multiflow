#pragma once

#include "MultiflowLibrary_global.hpp"

#include "expression.hpp"

namespace ml {
/**
 * @brief 常数表达式，在表达式中扮演常数的角色
 *
 * @author z
 */
class ML_PUBLIC Constant final : public Expression {
public:
    Number _value;

    Constant(const std::string& name, const std::string& description, Number value);

    /**
     * @brief 常数表达式的求值，自然就是常数本身
     */
    [[nodiscard]] Number evaluate(Environment& env) override;

    [[nodiscard]] std::string representation() const override;
};
}
