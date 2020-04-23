#pragma once

#include "Node.h"
#include "BSTInterface.h"

using namespace std;

class BST : public BSTInterface {
public:
	BST() {}
	~BST();

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	bool insert(Node*& T, int val);
	
	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);
	
	bool take_out(Node*& T, int data);
	
	int high_left(Node* T);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	
	void clear_all(Node* T);
	
	void clear();
	
	
private:
	Node* root;
	
};