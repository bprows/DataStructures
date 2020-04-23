#include <iostream>
#include <time.h>

// TODO: include the appropriate library for that class
#include <set>
#include <list>
#include "HashSet.h"    // this was the name of my header file for my hash set class

using namespace std;

// takes as input the number of items to insert into the set
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments. Need to input tableSize." << endl;
        return 0;
    }
    
    int N = atoi(argv[1]);

    // instantiate a set object;
    HashSet *s = new HashSet(N);
    
    cout << "Use the following to functions: " << endl;
    cout << "i = insert" << endl;
    cout << "f = find" << endl;
    cout << "d = delete" << endl;
    cout << "s = size" << endl;
    cout << "x - cancel" << endl << endl;
    cout << "Enter option: " << endl;
    char option;
    cin >> option;
    while (option != 'x') {
        
        if (option == 'i') {
            cout << "Enter integer to insert." << endl;
            int data;
            cin >> data;
            if (s->insert(data)) {
                cout << "Inserted " << data << " into HashSet." << endl;
            }
            else {
                cout << "Error inserting " << data << " into HashSet." << endl; 
            }
        }
        
        else if (option == 'f') {
            cout << "Enter integer to find" << endl;
            int data;
            cin >> data;
            if (s->find(data)) {
                cout << data << " is in set" << endl;
            }
            else {
                cout << data << "not in set" << endl;
            }
        }
        
        else if (option == 'd') {
            cout << "Enter integer to erase" << endl;
            int data;
            cin >> data;
            if (s->erase(data)) {
                cout << data << " was erased from set" << endl;
            }
            else {
                cout << data << " was not removed from set" << endl;
            }
        }
        
        else if (option == 's') {
            cout << "size of HashSet: " << s->size() << endl;
        }
        
        else {
            cout << "invalid option." << endl;
        }
        cout << "Enter next option. (i, f, d, s, x)" << endl;
        cin >> option;
    }
    
    cout << "goodbye" << endl;
    
    
    return 0;
}