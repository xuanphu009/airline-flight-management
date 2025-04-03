#include "../include/AVL_TREE.h"


Node::Node(Passenger _data) : data(_data), height(1), left(nullptr), right(nullptr) {}
Node::Node() : left(nullptr), right(nullptr) {};

int AVL_TREE::get_height(Node *x) {
    if(x == nullptr) return 0;
    return x->height;
}   
int AVL_TREE::max(int a, int b){
    return (a > b) ? a : b;
}
int AVL_TREE::get_balance(Node *x) {
    if(x == nullptr) return 0;
    return  get_height(x->left) - get_height(x->right);
}
Node* AVL_TREE::get_root() {
    return root;
}
Node* AVL_TREE::right_rotate(Node *x) {
    Node *y = x->left;
    Node *z = y->right;
    y->right = x;
    x->left = z;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return y;
}
Node* AVL_TREE::left_rotate(Node* x) {
    Node *y = x->right;
    Node *z = y->left;
    y->left = x;
    x->right = z;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return y;
}
Node *AVL_TREE::insert(Node *x, Passenger data) {
    if(x == nullptr) {
        return new Node(data);
    }
    // x->data.CMND > data.CMND
    if(strcmp(x->data.CMND, data.CMND) > 0) {
        x->left = insert(x->left, data);
    } else { //x->data.CMND < data.CMND
        x->right = insert(x->right, data);
    }

    x->height = max(get_height(x->left), get_height(x->right)) + 1;


    int balance = get_balance(x);
    if(balance > 1 && strcmp(data.CMND, x->left->data.CMND) < 0) {  // LL case
        return right_rotate(x);
    }
    if(balance > 1 && strcmp(data.CMND, x->left->data.CMND) > 0) {  // LR case
        x->left = left_rotate(x->left);
        return right_rotate(x);
    }
    if(balance < -1 && strcmp(data.CMND, x->right->data.CMND) > 0) {  // RR case
        return left_rotate(x);
    }
    if(balance < -1 && strcmp(data.CMND, x->right->data.CMND) < 0) {  // RL case
        x->right = right_rotate(x->right);
        return left_rotate(x);
    }
    
    return x;
}
Node *AVL_TREE::min_val_subtree(Node *node){
    Node *current = node;
    while (current->left != NULL)
       current = current->left;
    return current;
 }
Node *AVL_TREE::erase(Node *x, Passenger data){
    if (x == NULL)
       return x;
    if (strcmp(data.CMND, x->data.CMND) < 0)
       x->left = erase(x->left, data);
    else if (strcmp(data.CMND, x->data.CMND) > 0)
       x->right = erase(x->right, data);
    else {
        if ((x->left == NULL) || (x->right == NULL)) {
            Node *temp = x->left ? x->left : x->right;
            if (temp == NULL) {
                temp = x;
                x = NULL;
            } else
                *x = *temp;
            delete temp;
        } else {
          Node *temp = min_val_subtree(x->right);
          x->data = temp->data;
          x->right = erase(x->right, temp->data);
        }
    }
    if (x == NULL)
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
    if (x == nullptr) return nullptr;
    if (strcmp(CMND, x->data.CMND) < 0)
       return search(x->left, CMND);
    else if (strcmp(CMND, x->data.CMND) > 0)
       return search(x->right, CMND);
    else {
        return x;
    }
}