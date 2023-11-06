#ifndef CONSTANT_H
#define CONSTANT_H

#include "../MultiflowLibrary_global.hpp"

#include "expression.hpp"

namespace ml
{

/**
 * @brief 常数表达式，在表达式中扮演常数的角色
 *
 * @author z
 */
class ML_PUBLIC Constant: public Expression
{
private:
    ml::Number _value;

public:
    Constant(const std::string& name, const std::string& description, ml::Number value);

    /**
     * @brief 常数表达式的求值，自然就是常数本身
     */
    ml::Number evaluate(const Environment& env) const override;

    std::string to_string() const override;

    /**
     * @brief 圆周率，预定义的常见常数
     */
    static const Constant pi;

    /**
     * @brief 自然对数的底，预定义的常见常数
     */
    static const Constant e;
};

}

#endif // CONSTANT_H
