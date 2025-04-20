#include "../include/AVL_TREE.h"

Node::Node(Passenger _data) : data(_data), height(1), left(nullptr), right(nullptr) {}
Node::Node() : data(), height(1), left(nullptr), right(nullptr) {} // Added default initialization for consistency

int AVL_TREE::get_height(Node *x) {
    if (x == nullptr) return 0;
    return x->height;
}

int AVL_TREE::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL_TREE::get_balance(Node *x) {
    if (x == nullptr) return 0;
    return get_height(x->left) - get_height(x->right);
}

Node* AVL_TREE::get_root() {
    return root;
}

Node* AVL_TREE::right_rotate(Node *x) {
    Node *y = x->left;
    Node *z = y->right;
    y->right = x;
    x->left = z;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

Node* AVL_TREE::left_rotate(Node* x) {
    Node *y = x->right;
    Node *z = y->left;
    y->left = x;
    x->right = z;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

Node *AVL_TREE::insert(Node *x, Passenger data) {
    if (x == nullptr) {
        return new Node(data);
    }
    int cmp = strcmp(x->data.CMND, data.CMND);
    if (cmp > 0) {
        x->left = insert(x->left, data);
    } else if (cmp < 0) {
        x->right = insert(x->right, data);
    } else {
        // Duplicate CMND detected, do not insert
        return x;
    }

    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    int balance = get_balance(x);
    if (balance > 1 && strcmp(data.CMND, x->left->data.CMND) < 0) {  // LL case
        return right_rotate(x);
    }
    if (balance > 1 && strcmp(data.CMND, x->left->data.CMND) > 0) {  // LR case
        x->left = left_rotate(x->left);
        return right_rotate(x);
    }
    if (balance < -1 && strcmp(data.CMND, x->right->data.CMND) > 0) {  // RR case
        return left_rotate(x);
    }
    if (balance < -1 && strcmp(data.CMND, x->right->data.CMND) < 0) {  // RL case
        x->right = right_rotate(x->right);
        return left_rotate(x);
    }
    return x;
}

Node *AVL_TREE::min_val_subtree(Node *node) {
    Node *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node *AVL_TREE::erase(Node *x, Passenger data) {
    if (x == nullptr)
        return x;
    int cmp = strcmp(data.CMND, x->data.CMND);
    if (cmp < 0)
        x->left = erase(x->left, data);
    else if (cmp > 0)
        x->right = erase(x->right, data);
    else {
        if ((x->left == nullptr) || (x->right == nullptr)) {
            Node *temp = x->left ? x->left : x->right;
            if (temp == nullptr) {
                temp = x;
                x = nullptr;
            } else
                *x = *temp;
            delete temp;
        } else {
            Node *temp = min_val_subtree(x->right);
            x->data = temp->data;
            x->right = erase(x->right, temp->data);
        }
    }
    if (x == nullptr)
        return x;
    x->height = 1 + max(get_height(x->left), get_height(x->right));
    int balance = get_balance(x);
    if (balance > 1 && get_balance(x->left) >= 0) {
        return right_rotate(x);
    }
    if (balance > 1 && get_balance(x->left) < 0) {
        x->left = left_rotate(x->left);
        return right_rotate(x);
    }
    if (balance < -1 && get_balance(x->right) <= 0) {
        return left_rotate(x);
    }
    if (balance < -1 && get_balance(x->right) > 0) {
        x->right = right_rotate(x->right);
        return left_rotate(x);
    }
    return x;
}

Node *AVL_TREE::search(Node *x, char *CMND) {
    if (CMND == nullptr)
        return nullptr;
    Node* cur = x; // Fixed to use parameter x instead of root
    while (cur != nullptr) {
        if (cur->data.CMND == nullptr)
            return nullptr;
        int cmp = std::strcmp(CMND, cur->data.CMND);
        if (cmp == 0) {
            return cur;
        } else if (cmp < 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return nullptr;
}