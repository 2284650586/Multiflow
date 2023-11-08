//
// Created by miku on 11/5/2023.
//

#include "formula_parser.hpp"

#include "expression/constant.hpp"
#include "expression/add.hpp"
#include "expression/subtract.hpp"
#include "expression/multiply.hpp"
#include "expression/divide.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <functional>

namespace ml {
    static std::vector<std::shared_ptr<Expression> > expressionsFromAstNodes(
        FormulaParser &parser,
        const std::vector<std::shared_ptr<ASTNode>> &v
    ) {
        std::vector<std::shared_ptr<Expression> > ret{};

        std::transform(v.begin(), v.end(), std::back_inserter(ret),
                       [&parser](const std::shared_ptr<ASTNode> &node) {
                           return parser._internalTraverseAst(node);
                       });
        return ret;
    }

    static std::vector<
        std::pair<
            /* Validator: any_of */
            std::vector<std::string>,

            /* Function */
            std::function<std::shared_ptr<Expression>(FormulaParser &, const std::vector<std::shared_ptr<ASTNode>> &)>
        >
    > functionMap{
        {{"+", "Add"},         [](FormulaParser &parser, const auto &args) {
            return std::make_shared<Add>(expressionsFromAstNodes(parser, args));
        }},
        {{"-", "Sub"},         [](FormulaParser &parser, const auto &args) {
            return std::make_shared<Subtract>(expressionsFromAstNodes(parser, args));
        }},
        {{"*", "Mul", "Mult"}, [](FormulaParser &parser, const auto &args) {
            return std::make_shared<Multiply>(expressionsFromAstNodes(parser, args));
        }},
        {{"/", "Div"},         [](FormulaParser &parser, const auto &args) {
            return std::make_shared<Divide>(expressionsFromAstNodes(parser, args));
        }},
    };

    std::shared_ptr<Expression> FormulaParser::_internalTraverseAst(const std::shared_ptr<ASTNode> &root) {
        switch (root->type) {
            case NodeType::Function: {
                const std::string &functionName = root->value;
                for (auto pair: functionMap) {
                    if (std::ranges::any_of(pair.first,
                                            [functionName](const std::string &fn) { return fn == functionName; })) {
                        auto ptr = pair.second(*this, root->args);
                        return ptr;
                    }
                }
                throw FunctionNotDefinedException();
            }
            case NodeType::Variable: {
                const std::string &variableName = root->value;
                // Check if variable is a constant.
                if (constantNameToDescription.contains(variableName)) {
                    root->type = NodeType::Constant;
                    return _internalTraverseAst(root);
                }
                return std::make_shared<Variable>(variableName, variableNameToDescription[variableName]);
            }
            case NodeType::Constant: {
                const std::string &constantName = root->value;
                const auto &constantInfo = constantNameToDescription[constantName];
                return std::make_shared<Constant>(constantName, constantInfo.description, constantInfo.value);
            }
            default: {
                throw MalformedDistException();
            }
        }
    }

    std::vector<Formula> FormulaParser::loadDistribution(const std::string &configPath) {
        YAML::Node config = YAML::LoadFile(configPath);
        return parseDistribution(config);
    }

    std::vector<Formula> FormulaParser::parseDistribution(const YAML::Node &config) {
        // Is multiflow config?
        if (!config["multiflow-dist"].IsDefined()) {
            throw MalformedDistException();
        }

        // Data present?
        const auto &formulae = config["formulae"];
        if (!formulae.IsDefined()) {
            throw MalformedDistException();
        }

        std::vector<Formula> ret{};

        for (const auto &formula: formulae) {
            auto formulaInfo = FormulaInfo::fromYaml(formula);

            // Build variable map.
            variableNameToDescription.clear();
            std::for_each(
                formulaInfo.variables.begin(), formulaInfo.variables.end(),
                [this](const VariableInfo &info) {
                    variableNameToDescription[info.name] = info.description;
                });

            // Build constant map.
            constantNameToDescription.clear();
            std::for_each(
                formulaInfo.constants.begin(), formulaInfo.constants.end(),
                [this](const ConstantInfo &info) {
                    constantNameToDescription[info.name] = info;
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

    VariableInfo VariableInfo::fromYaml(const YAML::Node &node) {
        const auto &name = node["name"];
        const auto &type = node["type"];
        const auto &description = node["desc"];

        if (!name.IsDefined() || !type.IsDefined() || !description.IsDefined()) {
            throw MalformedDistException();
        }

        return VariableInfo{
            .name = name.as<std::string>(),
            .description = description.as<std::string>(),
            .type = type.as<std::string>(),
        };
    }

    FormulaInfo FormulaInfo::fromYaml(const YAML::Node &node) {
        const auto &name = node["name"];
        const auto &description = node["desc"];
        const auto &variables = node["variables"];
        const auto &constants = node["constants"];
        const auto &expression = node["expression"];
        if (!name.IsDefined() || !description.IsDefined() || !expression.IsDefined() || (
            !constants.IsDefined() && !variables.IsDefined()
        )) {
            throw MalformedDistException();
        }

        std::vector<VariableInfo> variablesInfos{};
        std::vector<ConstantInfo> constantInfos{};

        for (const auto &variable: variables) {
            variablesInfos.push_back(VariableInfo::fromYaml(variable));
        }
        for (const auto &constant: constants) {
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

    ConstantInfo ConstantInfo::fromYaml(const YAML::Node &node) {
        const auto &name = node["name"];
        const auto &description = node["desc"];
        const auto &value = node["value"];

        return ConstantInfo{
            .name = name.as<std::string>(),
            .description = description.as<std::string>(),
            .value = value.as<Number>(),
        };
    }
}
