#ifndef ASSIGNMENT_03_EXPRNODE_H
#define ASSIGNMENT_03_EXPRNODE_H
#include <string>


struct ExprNode {
    std::string tokenValue;
    ExprNode *left;
    ExprNode *right;

    explicit ExprNode(const std::string &value) : tokenValue(value), left(nullptr), right(nullptr) {}
};


#endif //ASSIGNMENT_03_EXPRNODE_H