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

BST::BST() {
    root = nullptr;
}

BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node *&)> func) {
    std::queue<Node*> q;
    q.push(get_root());
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        func(u);
        if(u->left) {
            q.push(u->left);
        }
        if(u->right) {
            q.push(u->right);
        }
    }
}

// 1.check exist
// 2.maintain order
// 3.insert new node
bool BST::add_node(int value) {
    auto cur_node = get_root();
    if(cur_node == nullptr) {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    while (true) {
        if(value < cur_node->value) {
            if(cur_node->left == nullptr) {
                break;
            }
            cur_node = cur_node->left;
        } else if(value > cur_node->value) {
            if(cur_node->right == nullptr) {
                break;
            }
            cur_node = cur_node->right;
        } else {
            break;
        }
    }
    if(value < cur_node->value) {
        cur_node->left = new Node(value, nullptr, nullptr);
    } else if(value > cur_node->value) {
        cur_node->right = new Node(value, nullptr, nullptr);
    } else {
        return false;
    }
    return true;
}

size_t BST::length() {
    std::size_t cnt = 0;
    bfs([&cnt](BST::Node*& node){
        cnt++;
    });
    return cnt;
}

// when address == nullptr, we wanna output "0"
// so consider output std::stringstream
std::ostream& operator<<(std::ostream& os, BST& bst) {
    std::cout << std::string(80, '*') << '\n';
    bst.bfs([](BST::Node*& node) {
        std::stringstream ssl, ssr;
        if(node->left) ssl << node->left;
        else ssl << "0";
        if(node->right) ssr << node->right;
        else ssr << "0";

        std::cout << std::left << std::setw(16) << node << "=> "
        << "value:" << std::setw(16) << node->value
        << "left:" << std::setw(16) << ssl.str()
        << "right:" << std::setw(16) << ssr.str()
        << '\n';
    });
    std::cout << std::left << "binary search tree size: " << bst.length() << '\n';
    std::cout << std::string(80, '*') << std::endl;
    return os;
}

BST::Node **BST::find_node(int value) {
    return nullptr;
}

