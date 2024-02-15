/************************************************
 * Caitlin Smith - csmith44
 * 2023 Spring CSE101 PA5
 * List.cpp
 * List ADT
*************************************************/

#include <string>
#include <iostream>
#include <stdexcept>
#include "List.h"

// Node Constructor -------------------------------------------------------
// Creates Node in the empty state.
List::Node::Node(ListElement x){
    data = x;
    prev = nullptr;
    next = nullptr;
}
//---------------------------------------------------------------------------

// Class Constructors & Destructors ----------------------------------------
// Creates new List in the empty state.
List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    // pointing to each other
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    // cursor
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List &L){
    // new list
    frontDummy = new Node(0);
    backDummy = new Node(0);
    // pointing to each other
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    // cursor
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    
    // put elements from L into the new list, traverse
    Node *N = L.frontDummy->next;
    while(N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
}

// Destructor
List::~List(){
    // traverse and delete nodes
    Node *N = frontDummy->next;
    while(N != nullptr){
        delete N->prev;
        N = N->next;
    }
    delete backDummy;
    //clear();
    frontDummy = nullptr;
    backDummy = nullptr;
}
//---------------------------------------------------------------------------

// Access functions --------------------------------------------------------
// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    // precondition
    if (num_elements > 0){
        return frontDummy->next->data;
    }
    else {
        throw std::length_error("List: front(): call on empty list");
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    // precondition
    if (num_elements > 0){
        return backDummy->prev->data;
    }
    else {
        throw std::length_error("List: back(): call on empty list");
    }
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    // precondition
    if (pos_cursor < num_elements){
        return afterCursor->data;
    }
    else {
        throw std::range_error("List: peekNext(): cursor at back of list");
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    // precondition
    if (pos_cursor > 0){
        return beforeCursor->data;
    }
    else {
        throw std::range_error("List: peekPrev(): cursor at front of list");
    }
}
//---------------------------------------------------------------------------

// Manipulation procedures -------------------------------------------------
// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    // traverse
    moveFront();
    while (afterCursor != backDummy){
        eraseAfter();
    }
    pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    if (num_elements != 0){
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
    }
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    if (num_elements != 0){
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
        pos_cursor = num_elements;
    }
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext(){
    // precondition
    if (pos_cursor < num_elements){
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor += 1;
        return beforeCursor->data;
    }
    else {
        throw std::range_error("List: moveNext(): cursor at back of list");
    }
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev(){
    // precondition
    if (pos_cursor > 0){
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor -= 1;
        return afterCursor->data;
    }
    else {
        throw std::range_error("List: movePrev(): cursor at front of list");
    }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    // new node
    Node *N = new Node(x);
    // "insert" N
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    // increase size
    num_elements += 1;
    // cursor pos stays
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    // new node
    Node *N = new Node(x);
    // "insert" N
    N->prev = beforeCursor;
    N->next = afterCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    // increase size
    num_elements += 1;
    // cursor pos increases
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    // precondition
    if (pos_cursor < num_elements){
        afterCursor->data = x;
    }
    else {
        throw std::range_error("List: setAfter(): cursor at back of list");
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    // precondition
    if (pos_cursor > 0){
        beforeCursor->data = x;
    }
    else {
        throw std::range_error("List: setBefore(): cursor at front of list");
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    // precondition
    if (pos_cursor < num_elements){
        // connect elements on either side of deleted one
        beforeCursor->next = afterCursor->next;
        afterCursor->next->prev = beforeCursor;
        // delete after cursor
        delete afterCursor;
        // set new after cursor
        afterCursor = beforeCursor->next;
        // edit size
        num_elements -=1;
    }
    else {
        throw std::range_error("List: eraseAfter(): cursor at back of list");
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    // precondition
    if (pos_cursor > 0){
        // connect elements on either side of deleted one
        afterCursor->prev = beforeCursor->prev;
        beforeCursor->prev->next = afterCursor;
        // delete before cursor
        delete beforeCursor;
        // set new before cursor
        beforeCursor = afterCursor->prev;
        // edit size
        num_elements -=1;
        // cursor pos decreases
        pos_cursor -= 1;
    }
    else {
        throw std::range_error("List: eraseBefore(): cursor at front of list");
    }
}
//---------------------------------------------------------------------------

// Other Functions ---------------------------------------------------------
// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x){
    // traverse
    Node *N = afterCursor;
    while (N != backDummy){
        if (x == N->data){
            moveNext();
            // final cursor position
            return pos_cursor;
        }
        N = N->next;
        moveNext();
    }
    moveBack();
    return -1; 
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x){
    // traverse
    Node *N = beforeCursor;
    while (N != frontDummy){
        if (x == N->data){
            movePrev();
            // final cursor position
            return pos_cursor;
        }
        N = N->prev;
        movePrev();
    }
    moveFront();
    return -1; 
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrence of each element, and removing all other occurrences. The cursor
// is not moved with respect to the retained elements, i.e., it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    // variables
    int original = pos_cursor;
    int check = 0;
    int another = 0;
    Node* N = frontDummy->next;
    // traverse the entire list
    // move cursor to front    
    moveFront();
    while (N != backDummy){
        another = 0;
        moveFront();
        while (pos_cursor != num_elements){
            // after cursor
            check = peekNext();
            // delete the next occurence
            if (check == N->data && another){
                eraseAfter();
                // if you are deleting something before the og cursor, reduce it
                if (pos_cursor < original){
                    original -= 1;
                }
            }
            // move to next
            else if (check == N->data && !another){
                another = 1;
                moveNext();
            }
            else {
                moveNext();
            }
        }
        N = N->next;
    }
    // put the cursor back in the right place
    moveFront();
    while (pos_cursor < original){
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const{
    // new list
    List C;
    // N this
    Node *N = this->frontDummy->next;
    while (N != this->backDummy){
        C.insertBefore(N->data);
        N = N->next;
    }
    // M L
    Node *M = L.frontDummy->next;
    while (M != L.backDummy){
        C.insertBefore(M->data);
        M = M->next;
    }
    C.moveFront();
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";
    for (N = frontDummy->next; N != backDummy; N = N->next){
        s += std::to_string(N->data)+" ";
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const{
    // variables
    bool res = false;
    Node *N = nullptr;
    Node *M = nullptr;
    // same size
    res = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    // traverse
    while (res && N != backDummy){
        // check data equality
        res = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return res;
}
//---------------------------------------------------------------------------

// Overloaded Operators ------------------------------------------------------
// operator<<()
// Inserts string representation of L, as defined by member function to_string(),
// into stream.
std::ostream& operator<<( std::ostream& stream,  const List& L ) {
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if List A equals List B, as defined by member
// function equals().
bool operator==(const List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L, then returns a reference
// to this List.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }

   // return this with the new data installed
   return *this;
}
//---------------------------------------------------------------------------
