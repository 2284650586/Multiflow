#ifndef CONSTANT_H
#define CONSTANT_H

#include "expression.hpp"

namespace ml
{

/**
 * @brief 常数表达式，在表达式中扮演常数的角色
 *
 * @author z
 */
class  __declspec(dllexport) Constant: public Expression
{
public:
    ml::Number _value;

    Constant(const std::string& name, const std::string& description, ml::Number value);

    /**
     * @brief 常数表达式的求值，自然就是常数本身
     */
    ml::Number evaluate(const Environment& env) const override;

    std::string to_string() const override;
};

}

#endif // CONSTANT_H
