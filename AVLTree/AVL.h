#pragma once

#include "Node.h"
#include "AVLInterface.h"

using namespace std;

class AVL: public AVLInterface {
public:
	AVL() {}
	~AVL();

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
	
	bool insert(Node *& T, int val);
	
	bool imbalanced(Node *T);
	
	void balance(Node *& T);
	
	void update_height(Node *& T);
	
	int get_max(int left, int right);
	
	void left_rotate(Node *& matriarch);
	
	void right_rotate(Node *& matriarch);
	
	int get_height(Node *T);
	
	int getCase(Node * T);
	
	bool take_out(Node*& T, int data);
	// bool remove_recursive(Node *& parent, int data);
	
	int high_left(Node* T);
	
	void clear_all(Node* T);
	
private:
    Node* root = NULL;
	
};
