/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA5
* Shuffle.c 
* Shuffle function 
*************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "List.h"

using namespace std;

/* shuffle() will alter its List& (List reference) argument D by performing one shuffle operation. Function main() 
will read a single command line argument, which will be a positive integer specifying the maximum number of cards  
in a deck. For each 𝑛 in the range 1 up to this maximum, your program will perform shuffles until the list 
(0, 1, 2, … , 𝑛 − 1) is brought back to its original order, 2 counting the number of shuffles as it goes.
 It will print a table to standard output giving this count, for each value of 𝑛. */

void shuffle(List& D){
    // variables
    List Left;
    List Right;
    int DLen = D.length();
    int LeftLen = DLen / 2;
    int RightLen = DLen - LeftLen;

    // traverse D, appending the halves to left and right
    D.moveFront();
    for (int i = 1; i < LeftLen + 1; i++){
        Left.insertBefore(D.peekNext());
        D.moveNext();
    }
    for (int i = 1; i < RightLen + 1; i++){
        Right.insertBefore(D.peekNext());
        D.moveNext();
    }

    // alternate from  left and right, adding to D
    // clear D
    D.clear();
    // move back to front
    Left.moveFront();
    Right.moveFront();
    // use left length since that will be <= right length
    for (int i = 1; i < LeftLen + 1; i++){
        // start from right
        D.insertBefore(Right.peekNext());
        Right.moveNext();
        D.insertBefore(Left.peekNext());
        Left.moveNext();
    }

    // if size is odd, there is one more from right to add
    if (DLen % 2 != 0){
        D.insertBefore(Right.peekNext());
    }

    // move cursor back to front of D
    D.moveFront();
}

// main
int main (int argc, char* argv[]){
    // check command line for correct number of arguments
    if (argc != 2){
        cerr << "Usage: <number of cards>" << endl;
        return(EXIT_FAILURE);
    }

    // get argument
    int size = atoi(argv[1]);

    // shuffle and output
    List A;
    List B;
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int i = 1; i < size + 1; i++){
        // fill A and B
        for (int x = 1; x < i + 1; x++){
            // fills from 1 to i
            A.insertBefore(x);
            B.insertBefore(x);
        }
        // shuffle until the same
        // count shuffles
        shuffle(A);
        int count = 1;
        while(!(A == B)){
            shuffle(A);
            count += 1;
        }
        // " 1               1"
        cout << " " << i << "               " << count << endl;
        // clear
        A.clear();
        B.clear();
    }

    return 0;
}
