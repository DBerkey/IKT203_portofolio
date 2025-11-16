#include <iostream>
#include <ostream>
#include "../include/AVL.h"

AVL::AVL() : root(nullptr) {}

// Public destructor
AVL::~AVL() {
    Destroy(root);
}

// Private destroy function
void AVL::Destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    Destroy(node->GetLeft());
    Destroy(node->GetRight());
    delete node;
}

int AVL::Height(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->GetHeight();
}

int AVL::GetBalance(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return Height(node->GetLeft()) - Height(node->GetRight());
}

// RR
Node *AVL::RotateRight(Node *y) {
    Node *x = y->GetLeft();          // Left-heavy child, new root
    Node *t2 = x->GetRight();        // Child node, not to be lost

    // Perform rotation
    x->SetRight(y);                  // x becomes parent of y
    y->SetLeft(t2);                  // T2 moves to y's left

    // Recalculate height
    int yHeight = std::max(Height(y->GetLeft()), Height(y->GetRight())) + 1;
    y->SetHeight(yHeight);
    int xHeight = std::max(Height(x->GetLeft()), Height(x->GetRight())) + 1;
    x->SetHeight(xHeight);

    // New subtree root
    return x;
}

// RL
Node *AVL::RotateRightLeft(Node *node) {
    node->SetRight(RotateRight(node->GetRight()));

    return RotateLeft(node);
}

// LL
Node *AVL::RotateLeft(Node *x) {
    Node *y = x->GetRight();          // Right-heavy child, new root
    Node *t2 = y->GetLeft();          // t2 will move under x

    // Perform rotation
    y->SetLeft(x);                    // y becomes parent of x
    x->SetRight(t2);                  // t2 moves to x's right

    // Recalculate heights
    x->SetHeight(std::max(Height(x->GetLeft()), Height(x->GetRight())) + 1);
    y->SetHeight(std::max(Height(y->GetLeft()), Height(y->GetRight())) + 1);

    // New subtree root
    return y;
}

// LR
Node *AVL::RotateLeftRight(Node *node) {
    node->SetLeft(RotateLeft(node->GetLeft()));

    return RotateRight(node);
}

// Public insert function
void AVL::Insert(const std::string &key, double value) {
    root = Insert(root, key, value);
}

// Recursive insert helper
Node *AVL::Insert(Node *node, const std::string &key, double value) {
    if (node == nullptr) {
        return new Node(value, key, nullptr, nullptr);
    }
    if (key < node->GetKey()) {
        node->SetLeft(Insert(node->GetLeft(), key, value));
    }
    else if (key > node->GetKey()) {
        node->SetRight(Insert(node->GetRight(), key, value));
    }
    else {
        node->SetData(value);
        return node;
    }

    int newHeight = std::max(Height(node->GetLeft()), Height(node->GetRight())) + 1;
    node->SetHeight(newHeight);

    int balance = GetBalance(node);

    // LL
    if (balance > 1 && key < node->GetLeft()->GetKey()) {
        return RotateRight(node);
    }
    // RR
    if (balance < -1 && key > node->GetRight()->GetKey()) {
        return RotateLeft(node);
    }
    // LR
    if (balance > 1 && key > node->GetLeft()->GetKey()) {
        return RotateLeftRight(node);
    }
    // RL
    if (balance < -1 && key < node->GetRight()->GetKey()) {
        return RotateRightLeft(node);
    }
    return node;
}

// Public search
Node *AVL::Search(const std::string &key) const {
    return Search(root, key);
}

// Recursive search
Node *AVL::Search(Node *node, const std::string &key) {
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

double AVL::searchValues(const std::string &key) const {
    Node *node = Search(root, key);
    if (node == nullptr) {
        throw std::runtime_error("Error, no value.");
    }
    return node->GetData();
}

// Public delete function
void AVL::Remove(const std::string& key) {
    root = Remove(root, key);
}

// Recursive delete function
Node *AVL::Remove(Node *node, const std::string &key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->GetKey()) {
        node->SetLeft(Remove(node->GetLeft(), key));
    }
    else if (key > node->GetKey()) {
        node->SetRight(Remove(node->GetRight(), key));
    }
                // ----     Node Found!     ----

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

    // Update height
    node->SetHeight(std::max(Height(node->GetLeft()), Height(node->GetRight())) + 1);

    int balance = GetBalance(node);

    // LL
    if (balance > 1 && GetBalance(node->GetLeft()) >= 0) {
        return RotateRight(node);
    }
    // LR
    if (balance > 1 && GetBalance(node->GetLeft()) < 0) {
        return RotateLeftRight(node);
    }
    // RR
    if (balance < -1 && GetBalance(node->GetRight()) <= 0) {
        return RotateLeft(node);
    }
    // RL
    if (balance < -1 && GetBalance(node->GetRight()) > 0) {
        return RotateRightLeft(node);
    }
    return node;
}

// Finding smallest element
Node *AVL::FindMin(Node *node) {
    while (node->GetLeft() != nullptr) {
        node = node->GetLeft();
    }
    return node;
}

// Traversal
void AVL::PrintInOrder() const {
    InOrder(root);
}
void AVL::InOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    InOrder(node->GetLeft());
    std::cout << node->GetKey() << std::endl;
    InOrder(node->GetRight());

}

void AVL::PrintPreOrder() const {
    PreOrder(root);
}
void AVL::PreOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->GetKey() << std::endl;
    PreOrder(node->GetLeft());
    PreOrder(node->GetRight());
}

void AVL::PrintPostOrder() const {
    PostOrder(root);
}
void AVL::PostOrder(Node* node) {
    if (node == nullptr) {
        return;
    }
    PostOrder(node->GetLeft());
    PostOrder(node->GetRight());
    std::cout << node->GetKey() << std::endl;
}