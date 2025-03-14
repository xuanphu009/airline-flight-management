#pragma once
#include"Passenger.h"
#include <cstring>




struct Node {
    Passenger data;
    Node *left;
    Node *right;
    int height;
    Node(Passenger _data);
    Node();
};

struct AVL_TREE {
    Node * root = nullptr;
    int get_height(Node *x);
    int max(int a, int b);
    int get_balance(Node *x);
    Node* get_root();
    Node* right_rotate(Node *x);
    Node* left_rotate(Node* x);
    Node *insert(Node *x, Passenger data);
    Node *min_val_subtree(Node *node);
    Node *erase(Node *x, Passenger data);
    Node *search(Node *x, char *CMND);
};