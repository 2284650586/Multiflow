#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../MultiflowLibrary_global.hpp"

#include <QString>

namespace expression
{

/**
 * @brief 表达式的基类。表达式用于计算。每个表达式:
 * - 最基本的求值当然得有
 * - 有一个名字，代表这个量在我们软件中的意义
 * - 有一个描述，是对某个量更加详尽的描述
 * - 可以转换为字符串，以便于显示
 *
 * 例如：
 * J * (pr - pwf)
 *
 * 这个表达式的名字是"产液量"
 * 描述："产液量，不考虑泡点压力"
 *
 * @author z
 */
class ML_PUBLIC Expression
{
protected:
    QString _name;
    QString _description;

public:
    using Number = double;

    /**
     * @brief 每个表达式起码要有名字和描述
     */
    Expression(const QString& name, const QString& description);

    virtual ~Expression();

    /**
     * @brief 求值
     * @param environment 未知数的实际值的表，暂时没做 TODO
     * @return 求值结果
     */
    virtual Number evaluate() const;

    /**
     * @brief 表达式的字符串描述。例如
     * Add(Variable(X), Constant(5))
     * 对应
     * (X + 5)
     *
     * @return 字符串描述
     */
    virtual QString to_string() const;

    /**
     * @return 表达式所代表的量的意义
     */
    virtual const QString& name() const;

    /**
     * @return 对表达式的更详细的描述
     */
    virtual const QString& description() const;
};

}

#endif // EXPRESSION_H
