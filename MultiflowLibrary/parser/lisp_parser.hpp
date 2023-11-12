//
// Created by miku on 11/5/2023.
//

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

enum class  __declspec(dllexport) NodeType {
    Function,
    Constant,
    Variable
};

struct  __declspec(dllexport) ASTNode {
    NodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> args;

    ASTNode(NodeType t, std::string val);

    void print(int level = 0) const;
};


class  __declspec(dllexport) LispParser {
public:
    std::unique_ptr<ASTNode> parse(const std::string& input);

private:
    size_t index;

    std::unique_ptr<ASTNode> parseExpression(const std::string& input);

    std::unique_ptr<ASTNode> parseElement(const std::string& input);

    std::string parseToken(const std::string& input);

    void consumeWhitespace(const std::string& input);
};
