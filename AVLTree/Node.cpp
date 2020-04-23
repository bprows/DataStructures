#include "Node.h"
#include <cstddef>

using namespace std;

Node::Node(int val) {
    data = val;
    height = 0;
}

int Node::getData() const {
    return this->data;
}

NodeInterface * Node::getLeftChild() const {
    return this->left;
}

NodeInterface * Node::getRightChild() const {
    return this->right;
}

int Node::getHeight() {
    return this->height;
}