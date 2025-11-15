#include "Parser.h"
#include <stack>
#include <cmath>
#include <stdexcept>

std::vector<std::string> Parser::Tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char c : input) {

        // Skip spaces
        if (std::isspace(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            continue;
        }
        // Digit, build number
        if (std::isdigit(c)) {
            currentToken += c;
            continue;
        }
        // Letter
        if (std::isalpha(c)) {
            currentToken += c;
            continue;
        }
        // Operator or parenthesis
        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
            currentToken.clear();
        }
        // Single character
        std::string op(1,c);
        tokens.push_back(op);
    }
    // Push last tokens, if remaining
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }
    return tokens;
}

int Parser::GetPrecedence(const std::string &token) {
    // Exponent has highest precedence
    if (token == "^") {
        return 3;
    }
    if (token == "*" || token == "/") {
        return 2;
    }
    if (token == "+" || token == "-") {
        return 1;
    }
    return 0;           // Not an operator (numbers, variables, parentheses)
}

void Parser::FreeTree(ExprNode *node) {
    if (node == nullptr) return;
    FreeTree(node->left);
    FreeTree(node->right);
    delete node;
}

std::vector<std::string> Parser::ToPostfix(const std::vector<std::string> &tokens) {
    std::vector<std::string> outputQueue;
    std::stack<std::string> operatorStack;

    // Check if we got a digit or alphabetical
    for (const std::string &token : tokens) {
        if (std::isdigit(token[0]) || std::isalpha(token[0])) {
            outputQueue.push_back(token);
            continue;
        }
        // Marks beginning of grouped expression
        if (token == "(") {
            operatorStack.push(token);
            continue;
        }
        // Stores everything inside the parenthesis to a stack
        if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop();
            }
            continue;
        }

        // Operator
        int currentPrecedence = GetPrecedence(token);

        while (!operatorStack.empty()) {
            std::string topOperator = operatorStack.top();
            int topPrecedence = GetPrecedence(topOperator);

            // Pop operators with equal or higher precedence
            if (topPrecedence >= currentPrecedence) {
                outputQueue.push_back(topOperator);
                operatorStack.pop();
            }
            else {
                break;
            }
        }
        operatorStack.push(token);
    }
    // pop all remaining operators
    while (!operatorStack.empty()) {
        outputQueue.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return outputQueue;
}

ExprNode *Parser::ExpressionTree(const std::vector<std::string> &postFixTokens) {
    std::stack<ExprNode*> expressionStack;

    for (const std::string &token : postFixTokens) {

        // Case 1: operand (variable, number, or functions)
        if (std::isdigit(token[0]) || std::isalpha(token[0])) {
            auto *node = new ExprNode(token);
            expressionStack.push(node);
            continue;
        }

        // Case 2: operator (+, -, * /, ^)
        ExprNode *rightNode = expressionStack.top();
        expressionStack.pop();

        ExprNode *leftNode = expressionStack.top();
        expressionStack.pop();

        ExprNode *operatorNode = new ExprNode(token);
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;

        expressionStack.push(operatorNode);
    }
    return expressionStack.top();
}

double Parser::EvaluateTree(ExprNode *root, AVL& symbolTable) {
    if (root == nullptr) {
        throw std::invalid_argument("null expression node");
    }
    const std::string &token = root->tokenValue;

    // Numbers
    if (std::isdigit(token[0])) {
        return std::stod(token);
    }
    //  Variable names
    if (std::isalpha(token[0])) {
        return symbolTable.searchValues(token);
    }
    // Operators
    double leftValue = EvaluateTree(root->left, symbolTable);
    double rightValue = EvaluateTree(root->right, symbolTable);

    if (token == "+") return leftValue + rightValue;
    if (token == "-") return leftValue - rightValue;
    if (token == "*") return leftValue * rightValue;
    if (token == "/") {
        if (rightValue == 0) {
            throw std::invalid_argument("Error : Division by zero");
        }
        return leftValue / rightValue;
    }
    if (token == "^") return std::pow(leftValue, rightValue);

    throw std::runtime_error("Unknown operator: " + token);
}