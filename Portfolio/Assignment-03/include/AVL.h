//
// Created by abden on 14.11.2025.
//

#ifndef IKT203_COURSE_ASSIGNMENTS_BST_H
#define IKT203_COURSE_ASSIGNMENTS_BST_H
#include "Node.h"


class AVL {
private:
    Node *root;

    // AVL implementation
    static int Height(Node *node);
    static int GetBalance(Node *node);
    static Node *RotateRight(Node *y);
    static Node *RotateRightLeft(Node *node);
    static Node *RotateLeft(Node *y);
    static Node *RotateLeftRight(Node *node);

    // BST implementation
    static Node *Insert(Node *node ,const std::string &key,double value);
    static Node *Search(Node *node, const std::string &key);
    static void  Destroy(Node* node);
    static Node* Remove(Node* node, const std::string& key);
    static Node* FindMin(Node* node);

    static void InOrder(Node* node);
    static void PreOrder(Node* node);
    static void PostOrder(Node* node);


public:
    AVL();
    ~AVL();

    void Insert(const std::string &key, double value);
    [[nodiscard]] Node *Search(const std::string &key) const;

    double searchValues(const std::string &key) const;

    void Remove(const std::string& key);

    void PrintInOrder() const;
    void PrintPreOrder() const;
    void PrintPostOrder() const;
};


#endif //IKT203_COURSE_ASSIGNMENTS_BST_H