//
// Created by miku on 11/5/2023.
//

#pragma once

#include "formula/formula.hpp"
#include "lisp_parser.hpp"

#include "yaml-cpp/yaml.h"

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

namespace ml {

struct VariableInfo {
    std::string name;
    std::string description;
    std::string type;

    static VariableInfo fromYaml(const YAML::Node& node);
};

struct ConstantInfo {
    std::string name;
    std::string description;
    Number value;

    static ConstantInfo fromYaml(const YAML::Node& node);
};

struct FormulaInfo {
    std::string name;
    std::string description;
    std::string expression;
    std::vector<VariableInfo> variables;
    std::vector<ConstantInfo> constants;

    static FormulaInfo fromYaml(const YAML::Node& node);
};

class FormulaParser {
private:
    std::unordered_map<std::string, std::string> variableMap;
    std::unordered_map<std::string, ConstantInfo> constantMap;

public:
    explicit FormulaParser() = default;
    virtual ~FormulaParser() = default;

    [[nodiscard]]
    std::vector<Formula> parseDistribution(const YAML::Node& config);

    [[nodiscard]]
    std::vector<Formula> parseDistribution(const std::string& configPath);

    std::shared_ptr<Expression> _internalTraverseAst(const std::shared_ptr<ASTNode>& root);
};

class MalformedDistException : public std::exception {};
class FunctionNotDefinedException : public std::exception {};

}
