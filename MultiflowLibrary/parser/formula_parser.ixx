//
// Created by miku on 11/5/2023.
//

module;

#include "expression/variable.hpp"
#include "expression/constant.hpp"
#include "expression/add.hpp"
#include "expression/subtract.hpp"
#include "expression/multiply.hpp"
#include "expression/divide.hpp"
#include "expression/power.hpp"
#include "expression/logarithm.hpp"
#include "expression/minus.hpp"
#include "expression/logical_and.hpp"
#include "expression/logical_or.hpp"
#include "expression/logical_not.hpp"
#include "expression/greater_than.hpp"
#include "expression/lower_than.hpp"
#include "expression/equal_to.hpp"
#include "expression/condition.hpp"

#include "utils/type_utils.hpp"
#include "lisp_parser.hpp"

#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

export module formula_parser;
import formula;

namespace ml {

export class __declspec(dllexport) MalformedDistException : public std::exception {
};

export class __declspec(dllexport) FunctionNotDefinedException : public std::exception {
};

export struct __declspec(dllexport) VariableInfo {
    std::string name;
    std::string description;
    std::string type;

    static VariableInfo fromYaml(const YAML::Node& node) {
        const auto& name = node["name"];
        const auto& type = node["type"];
        const auto& description = node["desc"];

        if (!name.IsDefined() || !type.IsDefined() || !description.IsDefined()) {
            throw MalformedDistException();
        }

        return VariableInfo{
            .name = name.as<std::string>(),
            .description = description.as<std::string>(),
            .type = type.as<std::string>(),
        };
    }
};

export struct __declspec(dllexport) ConstantInfo {
    std::string name;
    std::string description;
    Number value;

    static ConstantInfo fromYaml(const YAML::Node& node) {
        const auto& name = node["name"];
        const auto& description = node["desc"];
        const auto& value = node["value"];

        return ConstantInfo{
            .name = name.as<std::string>(),
            .description = description.as<std::string>(),
            .value = value.as<Number>(),
        };
    }
};

export struct __declspec(dllexport) FormulaInfo {
    std::string name;
    std::string description;
    std::string expression;
    std::vector<VariableInfo> variables;
    std::vector<ConstantInfo> constants;

    static FormulaInfo fromYaml(const YAML::Node& node) {
        const auto& name = node["name"];
        const auto& description = node["desc"];
        const auto& variables = node["variables"];
        const auto& constants = node["constants"];
        const auto& expression = node["expression"];
        if (!name.IsDefined() || !description.IsDefined() || !expression.IsDefined() || (
            !constants.IsDefined() && !variables.IsDefined()
        )) {
            throw MalformedDistException();
        }

        std::vector<VariableInfo> variablesInfos{};
        std::vector<ConstantInfo> constantInfos{};

        for (const auto& variable: variables) {
            variablesInfos.push_back(VariableInfo::fromYaml(variable));
        }
        for (const auto& constant: constants) {
            constantInfos.push_back(ConstantInfo::fromYaml(constant));
        }

        return FormulaInfo{
            .name = name.as<std::string>(),
            .description = description.as<std::string>(),
            .expression = expression.as<std::string>(),
            .variables = variablesInfos,
            .constants = constantInfos,
        };
    }
};

export class __declspec(dllexport) FormulaParser {
private:
    std::unordered_map<std::string, std::string> variableNameToDescription;
    std::unordered_map<std::string, ConstantInfo> constantNameToConstantInfo;

public:
    explicit FormulaParser() = default;

    virtual ~FormulaParser() = default;

    [[nodiscard]]
    std::vector<Formula> parseDistribution(const YAML::Node& config) {
        // Is multiflow config?
        if (!config["multiflow-dist"].IsDefined()) {
            throw MalformedDistException();
        }

        // Data present?
        const auto& formulae = config["formulae"];
        if (!formulae.IsDefined()) {
            throw MalformedDistException();
        }

        std::vector<Formula> ret{};

        for (const auto& formula: formulae) {
            auto formulaInfo = FormulaInfo::fromYaml(formula);

            // Build variable map.
            variableNameToDescription.clear();
            std::for_each(
                formulaInfo.variables.begin(), formulaInfo.variables.end(),
                [this](const VariableInfo& info) {
                    variableNameToDescription[info.name] = info.description;
                });

            // Build constant map.
            constantNameToConstantInfo.clear();
            std::for_each(
                formulaInfo.constants.begin(), formulaInfo.constants.end(),
                [this](const ConstantInfo& info) {
                    constantNameToConstantInfo[info.name] = info;
                });

            LispParser lispParser{};
            std::shared_ptr<ASTNode> ast = std::move(
                lispParser.parse(formulaInfo.expression));

            // Traverse AST and build expression.
            auto expression = _internalTraverseAst(ast);
            ret.emplace_back(
                formulaInfo.name, formulaInfo.description, expression, formulaInfo.expression);
        }
        return ret;
    }

    [[nodiscard]]
    std::vector<Formula> loadDistribution(const std::string& configPath) {
        YAML::Node config = YAML::LoadFile(configPath);
        return parseDistribution(config);
    }

    // 递归遍历AST，构建表达式。
    [[nodiscard]]
    std::shared_ptr<Expression> _internalTraverseAst(const std::shared_ptr<ASTNode>& root) { // NOLINT
        switch (root->type) {
            case NodeType::Function: {
                const std::string& functionName = root->value;
                for (auto pair: functionMap) {
                    if (std::ranges::any_of(pair.first,
                                            [functionName](const std::string& fn) { return fn == functionName; })) {
                        auto ptr = pair.second(*this, root->args);
                        return ptr;
                    }
                }
                throw FunctionNotDefinedException();
            }
            case NodeType::Variable: {
                const std::string& variableName = root->value;
                // Check if variable is a constant.
                if (constantNameToConstantInfo.contains(variableName)) {
                    root->type = NodeType::Constant;
                    return _internalTraverseAst(root);
                }
                return std::make_shared<Variable>(variableName, variableNameToDescription[variableName]);
            }
            case NodeType::Constant: {
                const std::string& constantName = root->value;
                if (variableNameToDescription.contains(constantName)) {
                    root->type = NodeType::Variable;
                    return _internalTraverseAst(root);
                }
                if (!constantNameToConstantInfo.contains(constantName)) {
                    // Raw number.
                    return std::make_shared<Constant>("Constant", "Constant", std::stod(constantName));
                }
                const auto& constantInfo = constantNameToConstantInfo[constantName];
                return std::make_shared<Constant>(constantName, constantInfo.description, constantInfo.value);
            }
            default: {
                throw MalformedDistException();
            }
        }
    }

private:
    static std::vector<
        std::pair<
            /* Validator: any_of */
            std::vector<std::string>,

            /* Function */
            std::function<std::shared_ptr<Expression>(FormulaParser&, const std::vector<std::shared_ptr<ASTNode>>
            &)>
        >
    > functionMap;
};

static std::vector<std::shared_ptr<Expression> > expressionsFromAstNodes(
    FormulaParser& parser,
    const std::vector<std::shared_ptr<ASTNode>>& v
) {
    std::vector<std::shared_ptr<Expression> > ret{};
    std::transform(v.begin(), v.end(), std::back_inserter(ret),
                   [&parser](const std::shared_ptr<ASTNode>& node) {
                       return parser._internalTraverseAst(node);
                   });
    return ret;
}

std::vector<
    std::pair<
        /* Validator: any_of */
        std::vector<std::string>,

        /* Function */
        std::function<std::shared_ptr<Expression>(FormulaParser&, const std::vector<std::shared_ptr<ASTNode>>
        &)>
    >
> FormulaParser::functionMap{{{
                                  "add", "+"
                              },                    [](
    FormulaParser& parser,
    const auto& args
) {
    return
        std::make_shared<Add>(expressionsFromAstNodes(parser, args)
        );
}},
                             {
                              {
                                  "sub", "-"},      [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Subtract>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "mul", "*"},      [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Multiply>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "div", "/"},      [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Divide>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "pow", "**"},     [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Power>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "log"},           [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Logarithm>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "minus"},         [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Minus>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "and", "&&"},     [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<LogicalAnd>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "or",  "||"},     [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<LogicalOr>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "not", "!", "~"}, [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<LogicalNot>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "gt",  ">"},      [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<GreaterThan>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "lt",  "<"},      [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<LowerThan>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "eq",  "=="},     [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<EqualTo>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
                             {
                              {
                                  "piecewise"},     [](
                                 FormulaParser& parser,
                                 const auto& args
                             ) {
                                 return
                                     std::make_shared<Condition>(expressionsFromAstNodes(parser, args)
                                     );
                             }},
};
}
