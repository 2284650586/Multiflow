#ifndef VARIABLE_H
#define VARIABLE_H

#include "../MultiflowLibrary_global.hpp"
#include "expression.hpp"

#include <string>

namespace ml
{

/**
 * @brief 未知数表达式，在表达式中扮演未知数（自变量）的角色
 * @author z
 */
class ML_PUBLIC Variable: public Expression
{
private:
    /**
     * @brief 参数名
     */
    std::string _name;

public:
    Variable(const std::string& name, const std::string& description);

    ml::Number evaluate(const Environment& env) const override;
    std::string to_string() const override;
};

}

#endif // VARIABLE_H
