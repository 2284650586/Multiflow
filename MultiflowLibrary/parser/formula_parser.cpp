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
#include "expression/referencing_function.hpp"
#include "expression/set_environment.hpp"
#include "expression/closure.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <logging/logging.hpp>

namespace ml {
static std::vector<std::shared_ptr<Expression>> expressionsFromAstNodes(
    FormulaParser& parser,
    const std::vector<std::shared_ptr<ASTNode>>& v
) {
    std::vector<std::shared_ptr<Expression>> ret{};

    std::ranges::transform(
        v, std::back_inserter(ret),
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
    {{"closure"}, _makeEf<Closure>()},
    {{"setq"}, _makeEf<SetEnvironment>()},
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


// NOLINTNEXTLINE(misc-no-recursion)
std::shared_ptr<Expression> FormulaParser::_handleFunction(const std::shared_ptr<ASTNode>& root) {
    const std::string& functionName = root->value;

    // Referencing an existing function?
    if (globalFunctionNameToExpression.contains(functionName)) {
        const auto expression = globalFunctionNameToExpression[functionName];
        expression->setName(functionName);

        std::vector<std::shared_ptr<Expression>> args{expression};
        for (const auto& arg: root->args) {
            args.push_back(_internalTraverseAst(arg));
        }
        return std::make_shared<ReferencingFunction>(args);
    }

    // A builtin function?
    if (const auto it = functionMap.find(functionName); it != functionMap.end()) {
        // Prevent second lookup.
        return it->second(*this, root->args);
    }

    // Neither?
    throw FunctionNotDefinedException();
}

// NOLINTNEXTLINE(misc-no-recursion)
std::shared_ptr<Expression> FormulaParser::_handleVariable(const std::shared_ptr<ASTNode>& root) {
    const std::string& variableName = root->value;
    // Named constants could first be recognized as variables.
    // Check if variable is a constant.
    if (constantNameToInfo.contains(variableName) || globalConstantNameToInfo.contains(variableName)) {
        root->type = NodeType::Constant;
        return _internalTraverseAst(root);
    }

    // Not declared as a variable? Create it.
    if (!variableNameToDescription.contains(variableName)) {
        variableNameToDescription[variableName] = "(无描述)";
    }

    return std::make_shared<Variable>(variableName, variableNameToDescription[variableName]);
}

// NOLINTNEXTLINE(misc-no-recursion)
std::shared_ptr<Expression> FormulaParser::_handleConstant(const std::shared_ptr<ASTNode>& root) {
    const std::string& constantName = root->value;

    // A declared scoped constant?
    if (constantNameToInfo.contains(constantName)) {
        const auto& [_, description, value] = constantNameToInfo[constantName];
        return std::make_shared<Constant>(constantName, description, value);
    }

    // A declared global constant?
    if (globalConstantNameToInfo.contains(constantName)) {
        const auto& [_, description, value] = globalConstantNameToInfo[constantName];
        return std::make_shared<Constant>(constantName, description, value);
    }

    // Raw number.
    return std::make_shared<Constant>("Constant", "Constant", std::stod(constantName));
}

// NOLINTNEXTLINE(misc-no-recursion)
std::shared_ptr<Expression> FormulaParser::_internalTraverseAst(const std::shared_ptr<ASTNode>& root) {
    switch (root->type) {
        case NodeType::Function:
            return _handleFunction(root);

        case NodeType::Variable:
            return _handleVariable(root);

        case NodeType::Constant:
            return _handleConstant(root);

        default:
            throw MalformedDistException();
    }
}

std::vector<Formula> FormulaParser::loadDistribution(const std::string& configPath) {
    const YAML::Node config = YAML::LoadFile(configPath);
    return parseDistribution(config);
}

void FormulaParser::_handleGlobalConstants(const YAML::Node& constants) {
    globalConstantNameToInfo.clear();
    for (const auto& constant: constants) {
        const auto constantInfo = ConstantInfo::fromYaml(constant);
        globalConstantNameToInfo[constantInfo.name] = constantInfo;
    }
}

std::vector<Formula> FormulaParser::parseDistribution(const YAML::Node& config) {
    globalFunctionNameToExpression.clear();
    _tryInitializeFunctionMap();

    // Is multiflow config?
    if (!config["multiflow-dist"].IsDefined()) {
        throw MalformedDistException();
    }

    if (const auto& globalConstants = config["global-constants"]; globalConstants.IsDefined()) {
        _handleGlobalConstants(globalConstants);
    }

    // Data present?
    const auto& formulae = config["formulae"];
    if (!formulae.IsDefined()) {
        throw MalformedDistException();
    }

    std::vector<Formula> ret{};

    for (const auto& formula: formulae) {
        const auto [
            name,
            description,
            expression,
            variables,
            constants
        ] = FormulaInfo::fromYaml(formula);

        // Build variable map.
        variableNameToDescription.clear();
        std::ranges::for_each(
            variables,
            [this](const VariableInfo& info) {
                variableNameToDescription[info.name] = info.description;
            });

        // Build constant map.
        constantNameToInfo.clear();
        std::ranges::for_each(
            constants,
            [this](const ConstantInfo& info) {
                constantNameToInfo[info.name] = info;
            });

        LispParser lispParser{};
        std::shared_ptr ast = std::move(lispParser.parse(expression));

        // Traverse AST and build expression.
        auto expressionParsed = _internalTraverseAst(ast);

        // Register as a global function.
        globalFunctionNameToExpression[name] = expressionParsed;

        ret.emplace_back(name, description, expressionParsed, expression);
    }
    return ret;
}

VariableInfo VariableInfo::fromYaml(const YAML::Node& node) {
    const auto& name = node["name"];
    const auto& description = node["desc"];

    if (!name.IsDefined()) {
        throw MalformedDistException();
    }

    return VariableInfo{
        .name = name.as<std::string>(),
        .description = description.as<std::string>("(无描述)"),
    };
}

FormulaInfo FormulaInfo::fromYaml(const YAML::Node& node) {
    const auto& name = node["name"];
    const auto& description = node["desc"];
    const auto& variables = node["variables"];
    const auto& constants = node["constants"];
    const auto& expression = node["expression"];
    if (!name.IsDefined() || !expression.IsDefined()) {
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
        .description = description.as<std::string>("(无描述)"),
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
        .description = description.as<std::string>("(无描述)"),
        .value = value.as<Number>(),
    };
}
}
