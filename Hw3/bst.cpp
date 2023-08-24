#include "bst.h"

BST::Node::Node(int value, Node *left, Node *right) : value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node &node) {
    value = node.value;
    left = node.left;
    right = node.right;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
    os << node.value;
    return os;
}

bool operator<=(const BST::Node& node, int v) {
    return node.value <= v;
}

bool operator<(const BST::Node& node, int v) {
    return node.value < v;
}

bool operator>(const BST::Node& node, int v) {
    return node.value > v;
}

bool operator>=(const BST::Node& node, int v) {
    return node.value >= v;
}

bool operator==(const BST::Node& node, int v) {
    return node.value == v;
}

bool operator>(int v, const BST::Node& node) {
    return v > node.value;
}

bool operator<(int v, const BST::Node& node) {
    return v < node.value;
}

bool operator>=(int v, const BST::Node& node) {
    return v >= node.value;
}

bool operator<=(int v, const BST::Node& node) {
    return v <= node.value;
}

bool operator==(int v, const BST::Node& node) {
    return v == node.value;
}

BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node *&)> func) {
    std::queue<Node*> q;
    q.push(get_root());
    while (!q.empty()) {
        auto u = q.front(); q.pop();

    }
}

size_t BST::length() {
    return 0;
}







