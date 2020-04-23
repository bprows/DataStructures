#include "QS.h"
#include <string>
#include <iostream>

using namespace std;

QS::~QS() {
    cout << "destructor called" << endl;
    cout << "deleting my_Array pointers." << endl;
    delete[] my_array;
}

QS::QS() {
    // create a baseline array.
    my_array = new (nothrow) int[capacity];
}

bool QS::createArray(int capacity) {
    this->capacity = capacity;
    if (my_array != nullptr) {
        cout << "Deleting previous array" << endl;
        clear();
    }
    
    my_array = new (nothrow) int[capacity];
    insertion = 0;  // reset insertion index
    end = -1;
    pivot = 0;
    pivot2 = 0;
    
    if (my_array == nullptr) {
        cout << "Allocation failed." << endl;
        return false;
    }
    return true;
}

bool QS::addToArray(int value) {
    if (insertion >= capacity) {
        return false;
    }
    else {
        my_array[insertion] = value;
        insertion++;
        end++;
        return true;
    }
}

string QS::getArray() const {
    string output;
    if (my_array != nullptr) {
        for (int i = 0; i < insertion; i++) {
            if (i == 0) {
                output = to_string(my_array[i]);
            }
            else {
                output = output + "," + to_string(my_array[i]);
            }
        }
    }
    return output;
}

int QS::getSize() const {
    return insertion;
}

void QS::clear() {
    //delete[] my_array;
    insertion = 0;
    end = 0;
    my_array = nullptr;
}

int QS::partition(int left, int right, int pivotIndex) {
    if (insertion == 0 || // empty array
        left >= right || // left greater than right
        left < 0 || // left out of bounds
        right >= insertion || // right out of bounds
        left > pivotIndex || 
        pivotIndex > right ) { // pivot not between left and right
        return -1;
    }
    int up, down, tmp, pivot;
    up = left + 1;
    down = right;
    // swap the pivot to be at left
    pivot = my_array[pivotIndex];
    my_array[pivotIndex] = my_array[left];
    my_array[left] = pivot;
    while (up <= down) { // until we meet in the middle
        // find a value that is greater than the pivot.
        while (my_array[up] <= pivot && up < right) { // could swap down for right
            up++;
        } // now up is the index of the first value greater than pivot
        while (my_array[down] > pivot && down > left) {
            down--;
        }
        //swap up with something smaller than pivot.
        // if data already ordered, thne rip
        if (up < down) {
            tmp = my_array[up];
            my_array[up] = my_array[down];
            my_array[down] = tmp;
        }
        up++;
    }
    // down should hold the highest index smaller than pivot. 
    // swap pivot and down to get the pivot in the right place, dividing the data
    my_array[left] = my_array[down];
    my_array[down] = pivot;
    return down;
}


int QS::medianOfThree(int left, int right) {
    if (insertion == 0 || left >= right || left < 0 || right > insertion - 1) {
        cout << "bad input" << endl;
        return -1;
    }
    else {
        int middle;
        int tmp;
        middle = (left + right) / 2;
        
        while (!sorted(left, middle, right)) {
            if (my_array[left] > my_array[middle]) {
                int tmp = my_array[middle];
                my_array[middle] = my_array[left];
                my_array[left] = tmp;
            }
            if (my_array[middle] > my_array[right]) {
                int tmp = my_array[right];
                my_array[right] = my_array[middle];
                my_array[middle] = tmp;
            }
        }
        return middle;
    }
    return -1;
}

void QS::sortAll() {
    // have my_array
    // medainOfThree on start and end of subarray to sort
    // call parition on subarray with pivot index from above.

    // base cases
    if (pivot == -1) {
        return;
    }
    if (pivot2 == -1) {
        return;
    }

    // left side
    pivot = medianOfThree(start, end);
    split = partition(start, end, pivot);
    // right side
    pivot2 = medianOfThree(end + 1, end_last);
    split2 = partition(end + 1, end_last, pivot2);

    // update parameters
    //start stays the same
    end_last = end;
    end = pivot;

    cout << "sortAll()" << endl;

    sortAll();
}



bool QS::sorted(int x, int y, int z) {
    if ( (my_array[x] <= my_array[y]) && (my_array[y] <= my_array[z]) ) {
        return true;
    }
    return false;
}

