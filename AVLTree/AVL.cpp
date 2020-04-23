#include "AVL.h"
#include "Node.h"
#include <cstdlib>
#include <iostream>

using namespace std;

NodeInterface * AVL::getRootNode() const {
    return this->root;
}

AVL::~AVL() {
    clear();
}

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
bool AVL::add(int data) {
    return insert(root, data);
}

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
bool AVL::remove(int data) {
    return take_out(root, data);
}

bool AVL::take_out(Node*& T, int data) {
    if (T == NULL) {
        return false;
    }
    if (T->getData() > data) {
        bool to_return = take_out(T->left, data);
		update_height(T);
        if (imbalanced(T)) {
            balance(T);
        }
        update_height(T);
        return to_return;
    }
    if (T->getData() < data) {
        bool to_return = take_out(T->right, data);
		update_height(T);
        if (imbalanced(T)) {
            balance(T);
        }
        update_height(T);
        return to_return;
    }
    if (T->getData() == data) { // found what to delete
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
            bool return_this = take_out(T->left, T->data);
			update_height(T);
			if (imbalanced(T)) {
				balance(T);
			}
			return return_this;
        }
    }
}

int AVL::high_left(Node* T) {
    if (T->right == NULL) {
        return T->data;
    }
    else {
        return high_left(T->right);
    }
}

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
void AVL::clear() {
    clear_all(root);
    this->root = NULL;
}

void AVL::clear_all(Node* T) {
    if (T != NULL) {
        clear_all(T->left);
        clear_all(T->right);
        delete T;
    }
}

bool AVL::insert(Node *& T, int val) {
    if (T == NULL) {
        T = new Node(val);
        return true;
    }
    if (T->data == val) {
        return false;
    }
    if (T->data > val) {
        bool returnval = insert(T->left, val);
        if (imbalanced(T)) {
            balance(T);
        }
        update_height(T);
        return returnval;
    }
    else {
        bool returnval = insert(T->right, val);
        if (imbalanced(T)) {
            balance(T);
        }
        update_height(T);
        return returnval;
    }
}

int AVL::get_height(Node *T) {
    if (T == NULL) {
        return -1;
    }
    else {
        return T->height;
    }
}

bool AVL::imbalanced(Node *T) {
    int diff;
    diff = abs( ( get_height(T->left) - get_height(T->right) ) );
    if (diff > 1) {
        return true;
    }
    else {
        return false;
    }
}

void AVL::balance(Node *& T) {
    if (getCase(T) == 1) {
        right_rotate(T);
		return;
    }
    if (getCase(T) == 2) {
        left_rotate(T);
		return;
    }
    if (getCase(T) == 3) {
        left_rotate(T->left);
        right_rotate(T);
		return;
    }
    if (getCase(T) == 4) {
        right_rotate(T->right);
        left_rotate(T);
		return;
    }
}

void AVL::update_height(Node *& T) {
    T->height = 1 + get_max(get_height(T->left), get_height(T->right));
}

int AVL::get_max(int left, int right) {
    if (left >= right) {
        return left;
    }
    else {
        return right;
    }
}

// deleting k->right 

void AVL::left_rotate(Node *& matriarch) {
    Node * k = matriarch->right;
    matriarch->right = k->left;
    Node * tmp = matriarch;
    matriarch = k;
    matriarch->left = tmp;
    update_height(tmp);
    update_height(matriarch);
}

void AVL::right_rotate(Node *& matriarch) {
    Node * k = matriarch->left;
    matriarch->left = k->right;
    Node * tmp = matriarch;
    matriarch = k;
    matriarch->right = tmp;
    update_height(tmp);
    update_height(matriarch);
}

int AVL::getCase(Node * T) {
    if (get_height(T->left) > get_height(T->right)) { // left - tbd
        if (get_height(T->left->left) >= get_height(T->left->right) ) { // left - left
            return 1;
        }
        else {
            return 3;
        }
    }
    else { // right - tbd
        if (get_height(T->right->right) >= get_height(T->right->left)) { // right - right
            return 2;
        }
        else {
            return 4;
        }
    }
}