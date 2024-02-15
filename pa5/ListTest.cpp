/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA5
 * ListTest.cpp
 * Tests for List ADT
 *************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include "List.h"

using namespace std;

int main(){
    List A;
    A.insertAfter(1);
    A.insertBefore(1);
    A.insertAfter(3);
    A.insertAfter(2);
    cout << "List A: " << A << endl;
    A.moveFront();
    A.moveNext();
    A.moveNext();
    cout << "pos (2): " << A.position() << endl;
    A.insertAfter(2);
    cout << "List A: " << A << endl;
    cout << "length (5): " << A.length() << endl;
    cout << "front (1): " << A.front() << endl;
    cout << "back (1): " << A.back() << endl;
    A.moveNext();
    A.eraseAfter();
    A.eraseBefore();
    cout << "List A: " << A << endl;
    cout << "prev: " << A.peekPrev() << endl;
    A.clear();

    List L;
    L.insertAfter(1);
    L.insertAfter(3);
    L.insertAfter(1);
    L.insertAfter(1);
    L.insertAfter(2);
    L.insertAfter(1);
    L.insertAfter(1);
    cout << "List L: " << L << endl;
    L.moveNext();
    L.moveNext();
    L.moveNext();
    L.moveNext();
    L.moveNext();
    cout << "pos (5): " << L.position() << endl;
    // L.cleanup();
    // cout << "List L: " << L << endl;
    // cout << "pos (2): " << L.position() << endl;
    L.clear();

    return 0;
}