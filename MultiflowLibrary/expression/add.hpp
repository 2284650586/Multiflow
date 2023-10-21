#ifndef ADD_H
#define ADD_H

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <QString>

namespace expression
{

/**
 * @brief 加法表达式，指示两个表达式相加
 *
 * @author z
 */
class ML_PUBLIC Add: public Expression
{
private:
    const Expression& _x;
    const Expression& _y;

public:
    Add(const Expression& x, const Expression& y);

    /**
     * @brief 计算相加结果
     */
    Expression::Number evaluate() const override;

    QString to_string() const override;
};

}

#endif // ADD_H
