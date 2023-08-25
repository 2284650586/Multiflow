#ifndef CONSTANT_H
#define CONSTANT_H

#include "../MultiflowLibrary_global.h"

#include "expression.h"

namespace expression
{

/**
 * @brief 常数表达式，在表达式中扮演常数的角色
 *
 * @author z
 */
class ML_PUBLIC Constant: public Expression
{
private:
    Expression::Number _value;

public:
    Constant(const QString& name, Expression::Number value, const QString& description);

    /**
     * @brief 常数表达式的求值，自然就是常数本身
     */
    Expression::Number evaluate() const override;

    QString to_string() const override;

    /**
     * @brief 圆周率，预定义的常见常数
     */
    static Constant const pi;

    /**
     * @brief 自然对数的底，预定义的常见常数
     */
    static Constant const e;
};

}

#endif // CONSTANT_H
