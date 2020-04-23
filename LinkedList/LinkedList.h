#pragma once
#include "LinkedListInterface.h"
#include <string>
#include <iostream>  
#include <sstream>
#include <stdexcept>

using namespace std;

template<typename T>

class LinkedList: public LinkedListInterface <T> {
    class Node {
        public:
        T item;
        Node* next;
    };
public:

	LinkedList(void) {};
	~LinkedList() {
		clear();
	};

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value) {
	    if (find(value)) {
	        return;
	    }
	    
	    // case 1, there is no head yet.
	    if (this->head == NULL) {
	       head = new Node();
	       head->item = value;
	       head->next = NULL;
	    }
	    else { // there already is a head
	        Node* newhead = new Node();
	        newhead->item = value;
	        newhead->next = this->head;
	        this->head = newhead;
	    }
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value) {
	    if (find(value)) {
	        return;
	    }
	    
	    if (this->head == NULL) {
	        insertHead(value);
	    }
	    else {
	        Node* another = new Node();
	        another->item = value;
	        another->next = NULL;
	        Node* tmp = this->head;
	        while (tmp->next != NULL) {
	            tmp = tmp->next;
	        }
	        tmp->next = another;
	    }
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode) {
	    if (!find(insertionNode)) { //insertionNode not found
	        return;
	    }
	    if (find(value)) { // value already in list.
	    	return;
	    }
	    // go find it
	    Node* tmp = head;
	    while (tmp != NULL) {
	        if (tmp->item == insertionNode) { // found it 
	            Node* another = new Node();
	            another->item = value;
	            another->next = tmp->next;
	            tmp->next = another;
	            return;
	        }
	        else {
	            tmp = tmp->next;
	        }
	    }
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value) {
		if (find(value)) { // value actually exists in list
			Node* tmp = head;
			if (value == head->item) { // case 1: removing the head
				this->head = tmp->next; // set new head node.
				delete tmp; // delete tmp pointer
				return;
			}
			while (value != tmp->next->item) {
				tmp = tmp->next;	
			}
			// tmp ->next is what we are getting rid of.
			Node* tmp2 = tmp->next; // what we are removing.
			tmp->next = tmp2->next; // point to the next next object
			delete tmp2;
		}
		return;
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear() {
		while(this->head != NULL) {
			remove(this->head->item); // calling remove on the head of the list until head is NULL
		}
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index) {
		if (index >= this->size() || index < 0) {
			// throw an out of range exception.
			throw std::out_of_range("at " + to_string(index) + " out_of_range");
		}
		int loc = 0;
		Node* tmp = head;
		while (loc != index) {
			tmp = tmp->next;
			loc++;
		}
		return tmp->item;
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size() {
	    Node* tmp = head;
	    int size = 0;
	    while (tmp != NULL) {
	        size++;
	        tmp = tmp->next;
	    }
	    return size;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString() {
		if (head == NULL) {
			return "";
		}
	    Node* tmp = head;
	    stringstream ss;
	    while (tmp != NULL) {
	    	if (tmp == head) {
	    		ss << tmp->item;
	    	}
	    	else {
	    		ss << " " << tmp->item;
	    	}
	        tmp = tmp->next;
	    }
	    string s = ss.str();
	    return s;
	}
	
	// helper function to make sure there are no duplicates
	bool find(T value) {
	    bool found = false;
	    if (head != NULL) {
	        Node* tmp = head;
	        while(tmp != NULL) {
	            if (tmp->item == value) {
	                return true;
	            }
	            tmp = tmp->next;
	        }
	    }
	    return found;
	}
	
	private:
	Node* head = NULL;

};

/////////////////////////////////////////////////////////////////////////////////
/*
#pragma once

template <typename ItemType>

class LinkedList {
  class Node {
    ItemType item;
    Node* next;
  };
  Node* head;
  int size;

  void insert(int index, const ItemType& item) {

  }

  ItemType remove(int index) {
    return ItemType();
  }

  int find(const ItemType& item) {
    return -1;
  }
};

*/
