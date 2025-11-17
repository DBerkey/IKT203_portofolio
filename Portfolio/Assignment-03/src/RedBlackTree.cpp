#include "../include/RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

void RedBlackTree::SetLeft(RBNode* parent, RBNode* node) {
    parent->left = node;
    if (node) node->parent = parent;
}

void RedBlackTree::SetRight(RBNode* parent, RBNode* node) {
    parent->right = node;
    if (node) node->parent = parent;
}

void RedBlackTree::Insert(double value) {
    RBNode* parent = nullptr;
    RBNode* cursor = root;

    // Standard BST search for the insertion point
    while (cursor != nullptr) {
        parent = cursor;
        if (value < cursor->data)
            cursor = cursor->left;
        else
            cursor = cursor->right;
    }

    // Create the new node
    RBNode* node = new RBNode(value);
    node->color = Red;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;

    // Empty tree case
    if (parent == nullptr) {
        root = node;
        root->color = Black;
        return;
    }

    // Attach to parent
    if (value < parent->data)
        parent->left = node;
    else
        parent->right = node;

    // Restore Red-Black invariants
    FixInsert(node);
}

void RedBlackTree::RotateLeft(RBNode* &node) {
    RBNode* child = node->right;

    node->right = child->left;
    if (child->left)
        child->left->parent = node;

    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

void RedBlackTree::RotateRight(RBNode* &node) {
    RBNode* child = node->left;

    node->left = child->right;
    if (child->right)
        child->right->parent = node;

    child->parent = node->parent;

    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->right) {
        node->parent->right = child;
    } else {
        node->parent->left = child;
    }

    child->right = node;
    node->parent = child;
}

void RedBlackTree::FixInsert(RBNode*& node) {
    while (node != root && node->parent->color == Red) {

        RBNode* parent = node->parent;
        RBNode* grand = parent->parent;

        // Parent on the left side
        if (parent == grand->left) {
            RBNode* uncle = grand->right;

            // Recoloring case
            if (uncle && uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                grand->color = Red;
                node = grand;
            }
            else {
                // Rotate to convert to line case
                if (node == parent->right) {
                    RotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                // Final rotation
                RotateRight(grand);
                Color tmp = parent->color;
                parent->color = grand->color;
                grand->color = tmp;
                node = parent;
            }
        }

        // Parent on the right side
        else {
            RBNode* uncle = grand->left;

            if (uncle && uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                grand->color = Red;
                node = grand;
            }
            else {
                if (node == parent->left) {
                    RotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                RotateLeft(grand);
                Color tmp = parent->color;
                parent->color = grand->color;
                grand->color = tmp;
                node = parent;
            }
        }
    }

    root->color = Black;
}

RBNode *RedBlackTree::Search(double key) const {
    RBNode* current = root;
    while (current != nullptr) {
        if (key == current->data) return current;
        if (key < current->data) current = current->left;
        else current = current->right;
    }
    return nullptr;
}