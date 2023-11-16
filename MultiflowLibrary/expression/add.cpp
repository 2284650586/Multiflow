#include "add.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <numeric>

namespace ml {
Add::Add(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Add", "Add"), _operands(std::move(operands)) {
}

Number Add::evaluate(const Environment& env) const {
    return std::accumulate(
        _operands.begin(), _operands.end(),
        static_cast<Number>(0), [env](const Number acc, const std::shared_ptr<Expression>& v) {
            return add(acc, v->evaluate(env));
        });
}

std::string Add::representation() const {
    return joinExpression(_operands, " + ");
}

const std::vector<std::shared_ptr<Expression>>& Add::operands() const {
    return _operands;
}
}
