#include <iostream>
#include <ostream>
#include "BST.h"

BST::BST() : root(nullptr) {}

// Public destructor
BST::~BST() {
    Destroy(root);
}

// Private destroy function
void BST::Destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    Destroy(node->GetLeft());
    Destroy(node->GetRight());
    delete node;
}

// Public insert function
void BST::Insert(const std::string &key, double value) {
    root = Insert(root, key, value);
}

// Recursive insert helper
Node *BST::Insert(Node *node, const std::string &key, double value) {
    if (node == nullptr) {
        return new Node(value, key, nullptr, nullptr);
    }
    if (key < node->GetKey()) {
        node->SetLeft(Insert(node->GetLeft(), key, value));
    }
    else if (key > node->GetKey()) {
        node->SetRight(Insert(node->GetRight(), key, value));
    }
    return node;
}

// Public search
Node *BST::Search(const std::string &key) const {
    return Search(root, key);
}

// Recursive search
Node *BST::Search(Node *node, const std::string &key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key == node->GetKey()) {
        return node;
    }
    if (key < node->GetKey()) {
        return Search(node->GetLeft(), key);
    }
    return Search(node->GetRight(), key);
}

// Public delete function
void BST::Remove(const std::string& key) {
    root = Remove(root, key);
}

// Recursive delete function
Node *BST::Remove(Node *node, const std::string &key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->GetKey()) {
        node->SetLeft(Remove(node->GetLeft(), key));
    }
    else if (key > node->GetKey()) {
        node->SetRight(Remove(node->GetRight(), key));
    }
                // ---- Case 1: no children ----
    else {
        if (node->GetLeft() == nullptr && node->GetRight() == nullptr) {
            delete node;
            return nullptr;
        }       // ---- Case 2: one child ----
        if (node->GetLeft() == nullptr) {
            Node *temp = node->GetRight();
            delete node;
            return temp;
        }
        if (node->GetRight() == nullptr) {
            Node *temp = node->GetLeft();
            delete node;
            return temp;
        }

        // ---- Case 3: two children ----
        Node *successor = FindMin(node->GetRight());

        node->SetData(successor->GetData());
        node->SetKey(successor->GetKey());

        node->SetRight(Remove(node->GetRight(), successor->GetKey()));
    }
    return node;
}

// Finding smallest element
Node *BST::FindMin(Node *node) {
    while (node->GetLeft() != nullptr) {
        node = node->GetLeft();
    }
    return node;
}

// Traversal
void BST::PrintInOrder() const {
    InOrder(root);
}
void BST::InOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    InOrder(node->GetLeft());
    std::cout << node->GetKey() << std::endl;
    InOrder(node->GetRight());

}

void BST::PrintPreOrder() const {
    PreOrder(root);
}
void BST::PreOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->GetKey() << std::endl;
    PreOrder(node->GetLeft());
    PreOrder(node->GetRight());
}

void BST::PrintPostOrder() const {
    PostOrder(root);
}
void BST::PostOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    PostOrder(node->GetLeft());
    PostOrder(node->GetRight());
    std::cout << node->GetKey() << std::endl;
}