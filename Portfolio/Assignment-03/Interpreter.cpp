#include "Interpreter.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>


Interpreter::Interpreter() = default;

// Removes whitespace before and after text
static std::string Trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");

    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Checks string for '='
bool Interpreter::IsAssignment(const std::string &input) const {
    return input.find("=") != std::string::npos;
}

// Returns leftSide of '='
std::string Interpreter::ExtractVariableName(const std::string& input) const {
    size_t equalPos = input.find("=");
    if (equalPos == std::string::npos){
        throw std::runtime_error("No '=' in assignment. ");
}

    std::string leftSide = input.substr(0, equalPos);
    leftSide = Trim(leftSide);

    if (leftSide.empty() || !std::isalpha(leftSide[0])){
        throw std::runtime_error("Not a valid variable name.");
    }
    return leftSide;
}

// Returns rightSide of '='
std::string Interpreter::ExtractExpression(const std::string& input) const {
    size_t equalPos = input.find("=");
    if (equalPos == std::string::npos) {
        throw std::runtime_error("No '=' in assignment. ");
    }

    std::string rightSide = input.substr(equalPos + 1);
    return Trim(rightSide);
}


double Interpreter::Process(const std::string &input) {
    std::string cleaned = Trim(input);
    if (cleaned.empty()) {
        throw std::runtime_error("Empty input.");
    }

    // Case 1: Assignment (e.g. : x = 7 + y)
    if (IsAssignment(cleaned)) {
        std::string varName = ExtractVariableName(cleaned);
        std::string expression = ExtractExpression(cleaned);

        // Tokenize
        std::vector<std::string> tokens = parser.Tokenize(expression);

        // Convert to postfix
        std::vector<std::string> postfix = parser.ToPostfix(tokens);

        // Build tree
        ExprNode *root = parser.ExpressionTree(postfix);

        // Evaluate
        double value = parser.EvaluateTree(root, symbolTable);

        // Store in AVL
        symbolTable.Insert(varName, value);

        // Free tree memory
        Parser::FreeTree(root);

        return value;
    }

    // Case 2: Expressions only
    std::vector<std::string> tokens = parser.Tokenize(cleaned);
    std::vector<std::string> postfix = parser.ToPostfix(tokens);
    ExprNode *root = parser.ExpressionTree(postfix);

    return parser.EvaluateTree(root, symbolTable);

}
