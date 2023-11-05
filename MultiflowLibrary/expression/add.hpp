#ifndef ADD_H
#define ADD_H

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>
#include <vector>

namespace ml
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
    ml::Number evaluate(const Environment& env) const override;

    std::string to_string() const override;

    const std::vector<Expression> operands() const override;
};

}

#endif // ADD_H
