#include <iostream>
#include <list>
#include "HashSet.h"

using namespace std;

HashSet::HashSet(int tableSize) {
    N = tableSize;
    current_size = 0;
    htable = new list<int>[N];
}

HashSet::~HashSet() {
    htable = NULL;
}

// returns the number of items in the set
int HashSet::size() {
    cout << "size() called" << endl;
    return current_size;
} 

// returns true if the integer "data" is in the set and false otherwise
bool HashSet::find(int data) {
    cout << "find(" << data << ") called." << endl;
    int spot = hashCode(data);
    return help_find(htable[spot], data);
}

// inserts the integer "data" into the set if that integer is not already in the set
// if the integer "data" is already in the set, the integer should not be inserted
// return true if the function adds the integer to the set, and false otherwise
bool HashSet::insert(int data) {
    int spot = hashCode(data);
    if (!help_find(htable[spot], data)) {
        htable[spot].push_back(data);
        current_size++;
        return true;
    }
    return false;
}

// erases the integer "data" from the set if it is in the set
// return true if the function removes the integer from the set, and false otherwise
bool HashSet::erase(int data) {
    int spot = hashCode(data);
    if (help_find(htable[spot], data)) {
        for (list<int>::iterator it = htable[spot].begin(); it != htable[spot].end(); it++) {
            if (*it == data) {
                htable[spot].erase(it);
                current_size--;
                return true;
            }
        }
    }
    return false;
}

bool HashSet::help_find(list<int> lst, int data) {
    for (list<int>::iterator it = lst.begin(); it != lst.end(); it++) {
        if (*it == data) {
            return true;
        }
    }
    return false;
}

int HashSet::hashCode(int data) {
    return data % N;
}