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
    this->root = nullptr;
}

BST::BST(std::initializer_list<int> il) {
    this->root = nullptr;
    for(auto x : il) {
        add_node(x);
    }
}

static BST::Node* trv(BST::Node* u) {
    if(u == nullptr) return nullptr;
    auto v = new BST::Node(u->value, nullptr, nullptr);
    v->left = trv(u->left);
    v->right = trv(u->right);
    return v;
}

BST::BST(const BST& rhs) {
    if(rhs.root == nullptr) this->root = nullptr;
    else this->root = trv(rhs.root);
}

BST::BST(BST&& rhs) noexcept {
    this->root = rhs.root;
    rhs.root = nullptr;
}

BST& BST::operator=(const BST& rhs) {
    if(this == &rhs) return *this;
    this->root = trv(rhs.root);
    return *this;
}

BST& BST::operator=(BST&& rhs) noexcept {
    this->root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;
}

BST& operator++(BST& u) {
    u.bfs([](BST::Node*& node) {
        node->value += 1;
    });
    return u;
}

BST operator++(BST& u, int) {
    BST t(u);
    u.bfs([](BST::Node*& node) {
        node->value += 1;
    });
    return t;
}

BST::Node*& BST::get_root() {
    return this->root;
}

void BST::bfs(std::function<void(Node*&)> func) {
    if(this->root == nullptr) return;
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

BST::Node** BST::find_node(int value) {
    auto cur_node = get_root();
    while (cur_node) {
        if(value < cur_node->value) {
            cur_node = cur_node->left;
        } else if(value > cur_node->value) {
            cur_node = cur_node->right;
        } else {
            break;
        }
    }
    if(cur_node == nullptr) {
        return nullptr;
    }
    auto res = new Node*(cur_node);
    return res;
}

BST::Node** BST::find_parent(int value) {
    auto cur = get_root();
    Node* prev = nullptr;
    while (cur) {
        if(value < cur->value) {
            prev = cur;
            cur = cur->left;
        } else if(value > cur->value) {
            prev = cur;
            cur = cur->right;
        } else {
            break;
        }
    }
    if(cur == nullptr) {
        return nullptr;
    }
    auto res = new Node*(prev);
    return res;
}

// This is not real successor! confusing!
BST::Node** BST::find_successor(int value) {
    auto res = find_node(value);
    if (res == nullptr or (*res)->left == nullptr) {
        return nullptr;
    }
    auto cur = *res;
    cur = cur->left;
    while (cur->right) {
        cur = cur->right;
    }
    return new Node *(cur);
}

bool BST::delete_node(int value) {
    auto cur = find_node(value);
    auto parent = find_parent(value);
    if(cur == nullptr) {
        return false;
    }
    if((*cur)->left == nullptr and (*cur)->right == nullptr) {
        if((*cur) == get_root()) {
            this->root = nullptr;
        } else {
            if((*cur)->value < (*parent)->value) {
                (*parent)->left = nullptr;
            } else {
                (*parent)->right = nullptr;
            }
        }
    } else if((*cur)->left != nullptr and (*cur)->right != nullptr) {
        auto succ = find_successor(value);
        Node* tmp = new Node{(*succ)->value, (*cur)->left, (*cur)->right};
        delete_node((*succ)->value);
        if((*cur) == get_root()) {
            tmp->left = this->root->left;
            tmp->right = this->root->right;
            this->root = tmp;
        } else {
            if((*parent)->left == (*cur)) {
                (*parent)->left = tmp;
            } else {
                (*parent)->right = tmp;
            }
        }
    } else {
        Node* tmp = nullptr;
        if((*cur)->left) {
            tmp = (*cur)->left;
        } else {
            tmp = (*cur)->right;
        }
        if((*cur) == get_root()) {
            tmp->left = this->root->left;
            tmp->right = this->root->right;
            this->root = tmp;
        } else {
            if((*parent)->left == (*cur)) {
                (*parent)->left = tmp;
            } else {
                (*parent)->right = tmp;
            }
        }
    }
    return true;
}
