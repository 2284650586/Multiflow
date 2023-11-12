//
// Created by miku on 11/5/2023.
//

module;

#include "expression/expression.hpp"
#include "expression/variable.hpp"
#include "expression/constant.hpp"

#include "utils/type_utils.hpp"

#include <spdlog/spdlog.h>

#include <string>
#include <vector>

export module formula;

// 递归地提取表达式中的参数和常量，不应该反复调用
// 禁用警告是因为 Clang-Tidy 反对使用递归
void __declspec(dllexport) _internalExtractVariablesAndConstants( // NOLINT
    const std::shared_ptr<ml::Expression>& expression,
    std::vector<std::shared_ptr<ml::Expression>>& ret
) {
    if (ml::instance_of<ml::Variable>(expression) || ml::instance_of<ml::Constant>(expression)) {
        if (expression->name() != "Constant") {
            ret.push_back(expression);
        }
        return;
    }

    try {
        const auto& operands = expression->operands();
        for (const auto& operand: operands) {
            _internalExtractVariablesAndConstants(operand, ret);
        }
    }
    catch (const ml::NotImplementedException& e) {}
}

export namespace ml {

class  __declspec(dllexport) Formula {
private:
    std::string _name;
    std::string _description;
    std::string _lisp;
    std::shared_ptr<Expression> _expression;

public:
    explicit Formula(std::string name, std::string description, std::shared_ptr<Expression> expression, std::string lisp) :
        _name(std::move(name)),
        _description(std::move(description)),
        _expression(std::move(expression)),
        _lisp(std::move(lisp)) {}

    virtual ~Formula() = default;

    [[nodiscard]]
    const std::string& name() const {
        return _name;
    }

    [[nodiscard]]
    const std::string& description() const {
        return _description;
    }

    [[nodiscard]]
    std::shared_ptr<Expression> expression() const {
        return _expression;
    }

    [[nodiscard]]
    const std::string& lisp() const {
        return _lisp;
    }

    /**
     * @brief 递归地提取表达式中的参数和常量，不应该反复调用
     * @return
     */
    [[nodiscard]]
    std::vector<std::shared_ptr<Expression>> extractVariablesAndConstants() const {
        std::vector<std::shared_ptr<Expression>> ret{};
        _internalExtractVariablesAndConstants(_expression, ret);
        spdlog::trace("Formula {} has {} variable(s) and constant(s).", _expression->name(), ret.size());
        return ret;
    }
};

}
