/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA8
 * DictionaryTest.cpp
 * Tests for Dictionary ADT
 *************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main(){
    string s;
    string S[] = {
        "caitlin",
        "rowan",
        "amanda",
        "dayana",
        "zoe",
        "victoria",
        "jaime",
        "colton",
        "emily"
    };

    Dictionary A, B;

    // insert into A
    for (int i = 0; i < 8; i++){
        A.setValue(S[i], i + 1);
    }

    // operator=()
    B = A;

    // print
    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << "B.size() = " << B.size() << endl
         << B << endl;
    
    // change B
    B.setValue("sarah", 1);
    B.setValue("fiona", 10);
    B.setValue("steph", 9);

    Dictionary C = B;
    cout << "B.size() = " << B.size() << endl
         << B << endl;
    cout << "C.size() = " << C.size() << endl
         << C << endl;

    // print each dictionary
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;

    // change A
    cout << A.getValue("dayana") << endl;
    A.getValue("dayana") *= 3; // change the value
    cout << A.getValue("dayana") << endl
         << endl;
    // check A
    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << A.pre_string() << endl;

    // remove some pairs from A
    A.remove("caitlin");
    A.remove("amanda");

    // check A
    cout << "A.size() = " << A.size() << endl
         << A << endl;
    cout << A.pre_string() << endl;

    A.begin();
    cout << A.currentKey() << endl;
    
    return 0;
}