#ifndef ASSIGNMENT_03_REDBLACKTREE_H
#define ASSIGNMENT_03_REDBLACKTREE_H

#include "RedBlackNode.h"


class RedBlackTree {
public:
    RBNode *root;

    RedBlackTree();

    static void SetLeft(RBNode *node, RBNode *parent);

    static void SetRight(RBNode *node, RBNode *parent);
    void Insert(double data);
    void RotateLeft(RBNode*& node);
    void RotateRight(RBNode*& node);
    void FixInsert(RBNode*& node);
    RBNode *Search(double key) const;

};


#endif //ASSIGNMENT_03_REDBLACKTREE_H