#include "lisp_parser.hpp"

ASTNode::ASTNode(const NodeType t, std::string val)
    : type(t), value(std::move(val)) {
}

bool isNumber(const std::string& str) {
    bool decimal_point_seen = false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (i == 0 && (str[i] == '+' || str[i] == '-')) {
            // Possible sign indicator at start
            if (str.size() == 1) {
                return false; // '+' or '-' alone is not a number
            }
            continue;
        }
        if (str[i] == '.') {
            if (decimal_point_seen || i == 0 || i == str.size() - 1) {
                return false; // Multiple decimal points or at start/end aren't numbers
            }
            decimal_point_seen = true;
        }
        else if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

std::unique_ptr<ASTNode> LispParser::parse(const std::string& input) {
    index = 0;
    return parseExpression(input);
}

// NOLINTNEXTLINE
std::unique_ptr<ASTNode> LispParser::parseExpression(const std::string& input) {
    consumeWhitespace(input);

    if (index >= input.size() || input[index] != '(') {
        throw LispParserException("Expected '(' at the beginning of an expression.");
    }

    ++index; // Skip '('
    consumeWhitespace(input);

    std::string token = parseToken(input); // Assume a function call if token is first after '('

    auto node = std::make_unique<ASTNode>(NodeType::Function, token);

    while (index < input.size() && input[index] != ')') {
        node->args.push_back(std::move(parseElement(input)));
        consumeWhitespace(input);
    }

    if (index >= input.size()) {
        throw LispParserException("Expected ')' at the end of an expression.");
    }

    ++index; // Skip ')'

    return node;
}

// NOLINTNEXTLINE
std::unique_ptr<ASTNode> LispParser::parseElement(const std::string& input) {
    consumeWhitespace(input);

    if (input[index] == '(') {
        return parseExpression(input);
    }

    std::string token = parseToken(input);
    if (isNumber(token)) {
        return std::make_unique<ASTNode>(NodeType::Constant, token);
    }
    return std::make_unique<ASTNode>(NodeType::Variable, token);
}

std::string LispParser::parseToken(const std::string& input) {
    consumeWhitespace(input);
    const size_t start = index;
    while (index < input.size() && !std::isspace(input[index]) && input[index] != '(' && input[index] != ')') {
        ++index;
    }
    return input.substr(start, index - start);
}

void LispParser::consumeWhitespace(const std::string& input) {
    while (index < input.size() && std::isspace(input[index])) {
        ++index;
    }
}
