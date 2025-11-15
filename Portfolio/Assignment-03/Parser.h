#ifndef ASSIGNMENT_03_PARSER_H
#define ASSIGNMENT_03_PARSER_H
#include <string>
#include <vector>
#include "AVL.h"
#include "ExprNode.h"


class Parser {
    public:

    static int GetPrecedence(const std::string &token);
    static void FreeTree(ExprNode *node);

    static std::vector<std::string> ToPostfix(const std::vector<std::string> &tokens);
    static std::vector<std::string> Tokenize(const std::string &input);

    static ExprNode *ExpressionTree(const std::vector<std::string> &postFixTokens);
    static double EvaluateTree(ExprNode *root, AVL& symbolTable);
};


#endif //ASSIGNMENT_03_PARSER_H