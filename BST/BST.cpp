#include "BST.h"

BST::~BST() {
    clear();
}

NodeInterface * BST::getRootNode() const {
    return this->root;
}

bool BST::add(int data) {
    return insert(root, data);
}

bool BST::insert(Node*& T, int val) {
    if (T == NULL) { // base case the spot where val should be is null
        T = new Node(val);
        return true;
    }
    if (T->getData() == val) { // val already in tree
        return false;
    }
    // recursive step
    if (T->getData() > val) {
        insert(T->left, val);
    }
    else {
        insert(T->right, val);
    }
}
	
bool BST::remove(int data) {
    return take_out(root, data);
}

int BST::high_left(Node* T) {
    if (T->right == NULL) {
        return T->data;
    }
    else {
        return high_left(T->right);
    }
}

bool BST::take_out(Node*& T, int data) {
    if (T == NULL) {
        return false;
    }
    if (T->getData() > data) {
        return take_out(T->left, data);
    }
    if (T->getData() < data) {
        return take_out(T->right, data);
    }
    if (T->getData() == data) {
        if (T->right == NULL && T->left == NULL) { // no children
            delete T;
            T = NULL;
            return true;
        }
        if (T->right != NULL && T->left == NULL) { // child on right
            Node* tmp = T;
            T = T->right;
            delete tmp;
            return true;
        }
        if (T->right == NULL && T->left != NULL) { // child on left
            Node* tmp = T;
            T = T->left;
            delete tmp;
            return true;
        }
        if (T->right != NULL && T->left != NULL) { // child on both
            T->data = high_left(T->left);
            return take_out(T->left, T->data);
        }
    }
}

void BST::clear_all(Node* T) {
    if (T != NULL) {
        clear_all(T->left);
        clear_all(T->right);
        delete T;
    }
}

void BST::clear() {
    clear_all(root);
    this->root = NULL;
}

