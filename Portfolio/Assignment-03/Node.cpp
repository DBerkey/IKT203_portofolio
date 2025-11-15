#include "Node.h"

#include <ios>


Node::Node(double data, const std::string &key, Node* left, Node* right)
    : key(key), data(new double(data)), left(left), right(right) {}

Node::~Node() {
    delete data;
}

double Node::GetData() const {
    return *data;
}

Node *Node::GetLeft() const {
    return left;
}

Node *Node::GetRight() const {
    return right;
}

const std::string &Node::GetKey() const {
    return key;
}

void Node::SetData(double newValue) {
    *(this->data) = newValue;
}

void Node::SetLeft(Node *node) {
    left = node;
}

void Node::SetRight(Node *node) {
    right = node;
}

void Node::SetKey(const std::string &key) {
    this->key = key;
}
