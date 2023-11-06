#include "add.hpp"

#include "math/math.hpp"

#include <vector>
#include <numeric>

namespace ml {
    Add::Add(std::vector<Expression> operands)
        : Expression("Add", "Add"), _operands(std::move(operands)) {}

    ml::Number Add::evaluate(const Environment &env) const {
        return std::accumulate(
            _operands.begin(), _operands.end(),
            static_cast<ml::Number>(0), [env] (Number acc, const Expression& v) {
            return ml::add(acc, v.evaluate(env));
        });
    }

    std::string Add::to_string() const {
        return join(_operands, " + ");
    }

    std::vector<Expression> Add::operands() const {
        return _operands;
    }
}
