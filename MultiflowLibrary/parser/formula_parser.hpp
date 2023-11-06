//
// Created by miku on 11/5/2023.
//

#pragma once

#include "MultiflowLibrary_global.hpp"

#include "formula/formula.hpp"
#include "lisp_parser.hpp"

#include "yaml-cpp/yaml.h"

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

namespace ml {

    struct ML_PUBLIC VariableInfo {
        std::string name;
        std::string description;
        std::string type;

        static VariableInfo fromYaml(const YAML::Node &node);
    };

    struct ML_PUBLIC ConstantInfo {
        std::string name;
        std::string description;
        Number value;

        static ConstantInfo fromYaml(const YAML::Node &node);
    };

    struct ML_PUBLIC FormulaInfo {
        std::string name;
        std::string description;
        std::string expression;
        std::vector<VariableInfo> variables;
        std::vector<ConstantInfo> constants;

        static FormulaInfo fromYaml(const YAML::Node &node);
    };

    class ML_PUBLIC FormulaParser {
    private:
        std::unordered_map<std::string, std::string> variableNameToDescription;
        std::unordered_map<std::string, ConstantInfo> constantNameToDescription;

    public:
        explicit FormulaParser() = default;

        virtual ~FormulaParser() = default;

        [[nodiscard]]
        std::vector<Formula> parseDistribution(const YAML::Node &config);

        [[nodiscard]]
        std::vector<Formula> loadDistribution(const std::string &configPath);

        std::shared_ptr<Expression> _internalTraverseAst(const std::shared_ptr<ASTNode> &root);
    };

    class MalformedDistException : public std::exception {
    };

    class FunctionNotDefinedException : public std::exception {
    };

}
