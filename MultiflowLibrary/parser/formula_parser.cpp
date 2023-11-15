//
// Created by miku on 11/5/2023.
//

#include "formula_parser.hpp"

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

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <functional>

namespace ml {
static std::vector<std::shared_ptr<Expression>> expressionsFromAstNodes(
    FormulaParser& parser,
    const std::vector<std::shared_ptr<ASTNode>>& v
) {
    std::vector<std::shared_ptr<Expression>> ret{};

    std::ranges::transform(v, std::back_inserter(ret),
                           [&parser](const std::shared_ptr<ASTNode>& node) {
                               return parser._internalTraverseAst(node);
                           });
    return ret;
}

typedef std::function<
    std::shared_ptr<Expression>(
        FormulaParser&,
        const std::vector<std::shared_ptr<ASTNode>>&
    )
> ExpressionFactory;

// Expression Factory Factory :(
template<class EType>
ExpressionFactory _makeEf() {
    return [](FormulaParser& parser, const auto& args) {
        return std::make_shared<EType>(expressionsFromAstNodes(parser, args));
    };
}

static const std::vector<std::pair<std::vector<std::string>, ExpressionFactory>> _fMap{
    {{"add", "+"}, _makeEf<Add>()},
    {{"sub", "-"}, _makeEf<Subtract>()},
    {{"mul", "*"}, _makeEf<Multiply>()},
    {{"div", "/"}, _makeEf<Divide>()},
    {{"pow", "**"}, _makeEf<Power>()},
    {{"log"}, _makeEf<Logarithm>()},
    {{"minus"}, _makeEf<Minus>()},
    {{"and", "&&"}, _makeEf<LogicalAnd>()},
    {{"or", "||"}, _makeEf<LogicalOr>()},
    {{"not", "!", "~"}, _makeEf<LogicalNot>()},
    {{"gt", ">"}, _makeEf<GreaterThan>()},
    {{"lt", "<"}, _makeEf<LowerThan>()},
    {{"eq", "=="}, _makeEf<EqualTo>()},
    {{"piecewise"}, _makeEf<Condition>()},
};

static std::map<std::string, ExpressionFactory> functionMap{};

static void _tryInitializeFunctionMap() {
    if (!functionMap.empty()) {
        return;
    }
    for (const auto& [keys, ef]: _fMap) {
        for (const std::string& key: keys) {
            functionMap[key] = ef;
        }
    }
}

// NOLINTNEXTLINE
std::shared_ptr<Expression> FormulaParser::_internalTraverseAst(const std::shared_ptr<ASTNode>& root) {
    switch (root->type) {
        case NodeType::Function: {
            if (const auto it = functionMap.find(root->value); it != functionMap.end()) {
                // Prevent second lookup.
                return it->second(*this, root->args);
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
            const auto& [_, description, value] = constantNameToConstantInfo[constantName];
            return std::make_shared<Constant>(constantName, description, value);
        }
        default: {
            throw MalformedDistException();
        }
    }
}

std::vector<Formula> FormulaParser::loadDistribution(const std::string& configPath) {
    const YAML::Node config = YAML::LoadFile(configPath);
    return parseDistribution(config);
}

std::vector<Formula> FormulaParser::parseDistribution(const YAML::Node& config) {
    _tryInitializeFunctionMap();

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
        auto [name, description, expression, variables, constants] = FormulaInfo::fromYaml(formula);

        // Build variable map.
        variableNameToDescription.clear();
        std::ranges::for_each(
            variables,
            [this](const VariableInfo& info) {
                variableNameToDescription[info.name] = info.description;
            });

        // Build constant map.
        constantNameToConstantInfo.clear();
        std::ranges::for_each(
            constants,
            [this](const ConstantInfo& info) {
                constantNameToConstantInfo[info.name] = info;
            });

        LispParser lispParser{};
        std::shared_ptr ast = std::move(lispParser.parse(expression));

        // Traverse AST and build expression.
        auto expressionParsed = _internalTraverseAst(ast);
        ret.emplace_back(name, description, expressionParsed, expression);
    }
    return ret;
}

VariableInfo VariableInfo::fromYaml(const YAML::Node& node) {
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

FormulaInfo FormulaInfo::fromYaml(const YAML::Node& node) {
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

ConstantInfo ConstantInfo::fromYaml(const YAML::Node& node) {
    const auto& name = node["name"];
    const auto& description = node["desc"];
    const auto& value = node["value"];

    return ConstantInfo{
        .name = name.as<std::string>(),
        .description = description.as<std::string>(),
        .value = value.as<Number>(),
    };
}
}
