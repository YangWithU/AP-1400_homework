#ifndef BST_H
#define BST_H

#include <functional>
#include <queue>
#include <iostream>
#include <iomanip>

class BST {
public:
    class Node;

    BST();
    BST(std::initializer_list<int>);
    BST(const BST&);
    BST(BST&&) noexcept;

    BST& operator=(const BST&);
    BST& operator=(BST&&) noexcept;

    ~BST();

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};

class BST::Node {
public:
    Node(int value, Node* left, Node* right);
    Node();
    Node(const Node& node);

    int value;
    Node* left;
    Node* right;
};

// normal way: friend ostream& operator <<(...){}
// can't add member func, so overload global '<<' instead
std::ostream& operator<<(std::ostream& os, const BST::Node& node);
bool operator<(const BST::Node& node, int v);
bool operator<=(const BST::Node& node, int v);
bool operator>(const BST::Node& node, int v);
bool operator>=(const BST::Node& node, int v);
bool operator==(const BST::Node& node, int v);

bool operator<(int v, const BST::Node& node);
bool operator<=(int v, const BST::Node& node);
bool operator>(int v, const BST::Node& node);
bool operator>=(int v, const BST::Node& node);

std::ostream& operator<<(std::ostream& os, BST& bst);

// add first, then call
BST& operator++(BST&);

// call first, increase second
BST operator++(BST&, int);

#endif //BST_H