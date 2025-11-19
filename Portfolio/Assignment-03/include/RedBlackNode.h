//
// Created by abden on 17.11.2025.
//

#ifndef ASSIGNMENT_03_REDBLACKNODE_H
#define ASSIGNMENT_03_REDBLACKNODE_H

enum Color { Red, Black };

    struct RBNode{
        double data;
        Color color;
        RBNode* left;
        RBNode* right;
        RBNode* parent;

        explicit RBNode(double value)
            : data(value), color(Red), left(nullptr), right(nullptr), parent(nullptr){}
    };



#endif //ASSIGNMENT_03_REDBLACKNODE_H