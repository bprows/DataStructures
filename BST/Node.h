
#pragma once

#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {

public:
	Node(int val);
	~Node() {}

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int getData() const;

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	Node * getLeftChild() const;

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	Node * getRightChild() const;
private:
	friend class BST;
    Node* right = NULL;
    Node* left = NULL;
    int data;

};