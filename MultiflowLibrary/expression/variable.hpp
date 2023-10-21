#ifndef VARIABLE_H
#define VARIABLE_H

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <QString>

namespace expression
{

/**
 * @brief 未知数表达式，在表达式中扮演未知数（自变量）的角色
 * @author z
 */
class ML_PUBLIC Variable: public Expression
{
private:
    /**
     * @brief 实际带入的值
     */
    Expression::Number _value;

public:
    Variable(const QString& name, Expression::Number value, const QString& description);

    /**
     * @brief 改变未知数的带入的值
     */
    void set_value(Expression::Number value);

    Expression::Number evaluate() const override;
    QString to_string() const override;
};

}

#endif // VARIABLE_H
