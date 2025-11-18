#include "../include/Parser.h"
#include <stack>
#include <cmath>
#include <stdexcept>

std::vector<std::string> Parser::Tokenize(const std::string &input) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        // Whitespace with implicit multiplication (*)
        if (std::isspace(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }

            // Look ahead for implicit multiplication
            size_t idx = i + 1;
            while (idx < input.size() && std::isspace(input[idx])) {
                idx++;
            }

            if (idx < input.size()) {
                char next = input[idx];

                bool lastIsValue =
                    !tokens.empty() &&
                    (std::isdigit(tokens.back()[0]) ||
                     std::isalpha(tokens.back()[0]) ||
                     tokens.back() == ")");

                bool nextIsValue =
                    (std::isdigit(next) ||
                     std::isalpha(next) ||
                     next == '(');

                if (lastIsValue && nextIsValue) {
                    tokens.push_back("*");
                }
            }

            continue;
        }

        // Digit, build number
        if (std::isdigit(c) || c == '.') {
            currentToken += c;
            continue;
        }

        // Letter
        if (std::isalpha(c)) {
            currentToken += c;
            continue;
        }

        // Finish token before operator or parenthesis
        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
            currentToken.clear();

            // Implicit multiplication without whitespace:
            // value immediately followed by '('
            if (c == '(') {
                char prev = tokens.back()[0];
                bool prevIsValue =
                    std::isdigit(prev) ||
                    std::isalpha(prev) ||
                    prev == ')';

                if (prevIsValue) {
                    tokens.push_back("*");
                }
            }
        }

        // Safety check
        if (!std::isdigit(c) && !std::isalpha(c) &&
            c != '+' && c != '-' && c != '*' && c != '/' && c != '^' &&
            c != '(' && c != ')')
        {
            throw std::runtime_error(std::string("Invalid character: '") + c + "'");
        }

        // Single operator/parenthesis
        tokens.push_back(std::string(1, c));
    }

    // Push final token (if any)
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
        currentToken.clear();
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

    for (const std::string &token : tokens) {

        // Numbers
        if (std::isdigit(token[0])) {
            outputQueue.push_back(token);
            continue;
        }

        // Functions
        if (token == "log" || token == "ln" || token == "exp") {
            operatorStack.push(token);
            continue;
        }

        // Variables
        if (std::isalpha(token[0])) {
            outputQueue.push_back(token);
            continue;
        }

        if (token.size() > 1 && !std::isalpha(token[0]) && !std::isdigit(token[0])) {
            throw std::runtime_error("Invalid operator token: " + token);
        }

        // Opening parenthesis
        if (token == "(") {
            operatorStack.push(token);
            continue;
        }

        // Closing parenthesis
        // Stores everything inside the parenthesis to a stack
        if (token == ")") {

            if (operatorStack.empty())
                throw std::runtime_error("Unmatched ')' found");

            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputQueue.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (operatorStack.empty() || operatorStack.top() != "(")
            throw std::runtime_error("Missing '(' for ')'");

            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop();

                if (!operatorStack.empty() &&
                    (operatorStack.top() == "ln" ||
                     operatorStack.top() == "log" ||
                     operatorStack.top() == "exp"))
                {
                    outputQueue.push_back(operatorStack.top());
                    operatorStack.pop();
                }
            }
            continue;
        }

        // Operator
        int currentPrecedence = GetPrecedence(token);

        while (!operatorStack.empty()) {
            std::string topOperator = operatorStack.top();
            int topPrecedence = GetPrecedence(topOperator);

            // Pop operators with equal or higher precedence
            bool isRightAssoc = (token == "^");
            if (topPrecedence > currentPrecedence ||
                (topPrecedence == currentPrecedence && !isRightAssoc)) {
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

        // Case 1: functions
        if (token == "ln" || token == "exp" || token == "log") {

            if (expressionStack.empty())
                throw std::runtime_error("Function '" + token + "' missing operand.");

            ExprNode *child = expressionStack.top();
            expressionStack.pop();

            auto *funcNode = new ExprNode(token);
            funcNode->right = child;

            expressionStack.push(funcNode);
            continue;
        }

        // Case 2: operand (variable or numbers)
        if (std::isdigit(token[0]) || std::isalpha(token[0])) {
            auto *node = new ExprNode(token);
            expressionStack.push(node);
            continue;
        }

        // Case 3: operator (+, -, * /, ^)
        if (expressionStack.size() < 2)
          throw std::runtime_error("Operator '" + token + "' missing operands.");

        ExprNode *rightNode = expressionStack.top();
        expressionStack.pop();

        ExprNode *leftNode = expressionStack.top();
        expressionStack.pop();

        ExprNode *operatorNode = new ExprNode(token);
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;

        expressionStack.push(operatorNode);
    }
    if (expressionStack.size() != 1)
        throw std::runtime_error("Invalid expression: leftover tokens.");

    return expressionStack.top();
}

double Parser::EvaluationTree(ExprNode *root, AVL& symbolTable) {
    if (root == nullptr) {
        throw std::invalid_argument("null expression node");
    }
    const std::string &token = root->tokenValue;

    // Numbers
    if (std::isdigit(token[0])) {
        return std::stod(token);
    }

    // Functions
    if (token == "log") {
        double val = EvaluationTree(root->right, symbolTable);
        return std::log10(val);
    }
    if (token == "ln") {
        double val = EvaluationTree(root->right, symbolTable);
        return std::log(val);
    }
    if (token == "exp") {
        double val = EvaluationTree(root->right, symbolTable);
        return std::exp(val);
    }

    //  Variable names
    if (std::isalpha(token[0])) {
        return symbolTable.searchValues(token);
    }


    // Operators
    double leftValue = EvaluationTree(root->left, symbolTable);
    double rightValue = EvaluationTree(root->right, symbolTable);

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