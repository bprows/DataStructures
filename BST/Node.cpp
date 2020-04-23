#include "Node.h"

using namespace std;

Node::Node(int val) {
    data = val;
}

int Node::getData() const {
    return this->data;
}

Node * Node::getRightChild() const {
    return this->right;
}

Node * Node::getLeftChild() const {
    return this->left;
}

int Node::getHeight() {
    return this->height;
}