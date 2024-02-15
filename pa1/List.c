/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA1 
* List.c 
* List ADT implementation 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// struct definitions --------------------------------------------------------
// Node ADT
typedef struct NodeObj* Node;
typedef struct NodeObj {
    int value;
    Node prev;
    Node next;
} NodeObj;

// List ADT
typedef struct ListObj {
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;
//---------------------------------------------------------------------------

// Constructors-Destructors ---------------------------------------------------
// Creates and returns a new empty Node ADT
Node newNode(int x){
    // allocate memory and set defaults
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    // set to null and parameter
    N->value = x;
    N->prev = NULL;
    N->next = NULL;
    return N;
} 

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeNode(Node* pN){
    // free and null
    if (pN && *pN){
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List ADT
List newList(void){
    // allocate memory and set defaults
    List L = malloc(sizeof(ListObj));
    assert(L != NULL);
    // set to null and 0
    L->front = L->cursor = L->back = NULL;
    L->index = -1;
    L->length = 0;
    return L;
} 

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL){
    // free and null
    if (pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}
// ----------------------------------------------------------------------------

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L){
    if (L != NULL){
        return L->length;
    }
    else {
        fprintf(stderr, "List Error: calling length() on empty List\n");
        exit(EXIT_FAILURE);
    }

}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if (L != NULL){
        return L->index;
    }
    else {
        fprintf(stderr, "List Error: calling index() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// Returns front element of L. Pre: length()>0
int front(List L){
    // precondition
    if (length(L) <= 0){
        // error message
        fprintf(stderr, "List Error: calling front() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->value;
}

// Returns back element of L. Pre: length()>0
int back(List L){
    // precondition
    if (length(L) <= 0){
        // error message
        fprintf(stderr, "List Error: calling back() on empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->value;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    // precondition
    if (length(L) <= 0){
        fprintf(stderr, "List Error: calling get() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        fprintf(stderr, "List Error: calling get() on List without defined cursor index\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->value;
}

// Returns true iff Lists A and B are in same state
// false otherwise
bool equals(List A, List B){
    // check if both are ! NULL
    if (A && B){
        // check if same length
        if (length(A) != length(B)){
            return false;
        }
        // current nodes to check
        Node aN = A->front;
        Node bN = B->front;
        // bool to track same state
        bool result = true;
        while (result && aN){
            if (aN->value == bN->value){
                result = true;
            }
            else {
                result = false;
            }
            aN = aN->next;
            bN = bN->next;
        }
        return result;
    }
    else {
        fprintf(stderr, "List Error: calling equals() on one or more empty Lists\n");
        exit(EXIT_FAILURE);
    }
}
// ----------------------------------------------------------------------------

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    // delete nodes
    while (L->front){
        deleteFront(L);
    }
    // set to NULL and 0
    L->front = L->cursor = L->back = NULL;
    L->index = -1;
    L->length = 0;
}

// Overwrites the cursor element’s data with x. 
// Pre: length()>0, index()>=0
void set(List L, int x){
    // preconditions
    if (length(L) > 0 && index(L) >= 0){
        L->cursor->value = x;
    }
    else {
        if (length(L) == 0){
            fprintf(stderr, "List Error: calling set() on empty List\n");
            exit(EXIT_FAILURE);
        }
        else {
            fprintf(stderr, "List Error: calling set() on List without defined cursor index\n");
            exit(EXIT_FAILURE);
        }
    }
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    // precondition
    if (length(L) > 0){
        // set cursor to the front
        L->cursor =L->front;
        L->index = 0;
    }
    else {
        fprintf(stderr, "List Error: calling moveFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    // precondition
    if (length(L) > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    } 
    else {
        fprintf(stderr, "List Error: calling moveBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined 
// do nothing
void movePrev(List L){
    if (L->cursor && index(L) != 0){
        // this will be the node right before the cursor
        L->cursor = L->cursor->prev;
        L->index -= 1;
    }
    else if (L->cursor && index(L) == 0){
        L->cursor = NULL;
        L->index = -1;
    }
} 

// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L){
    if (L->cursor && index(L) != length(L) - 1){
        // this will be the node after the cursor
        L->cursor = L->cursor->next;
        L->index += 1;
    }
    else if (L->cursor && index(L) == length(L) - 1){
        L->cursor = NULL;
        L->index = -1;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){
    // non empty
    if (length(L) != 0){
        // create new node
        Node new = newNode(x);
        //make new node the front
        new->next = L->front;
        L->front->prev = new;
        L->front = new;
        // increase index of cursor if defined
        if (index(L) >= 0){
            L->index += 1;
        }
        // increase length
        L->length += 1;
    }
    // empty
    else if (length(L) == 0) {
        // create new node
        Node new = newNode(x);
        // make the new node the front and back
        L->front = new;
        L->back = new;
        // increase length
        L->length += 1;
    }
}

// Insert new element into L. If L is non-empty, 
// insertion takes place after back element.
void append(List L, int x){
    // non empty
    if (length(L) != 0){
        // create new node
        Node new = newNode(x);
        //make new node the front
        new->prev = L->back;
        L->back->next = new;
        L->back = new;
        // increase length
        L->length += 1;
    }
    // empty
    else if (length(L) == 0){
        // create new node
        Node new = newNode(x);
        // make the new node the front
        L->front = new;
        L->back = new;
        // increase length
        L->length += 1;
    }
}

// Insert new element before cursor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    // preconditions
    if (length(L) > 0 && index(L) >= 0){
        if (index(L) == 0){
            prepend(L, x);
        }
        else {
            Node new = newNode(x);
            L->cursor->prev->next = new;
            new->prev = L->cursor->prev; 
            L->cursor->prev = new;
            new->next = L->cursor;
            // increase cursor index
            L->index += 1;
            // increase length
            L->length += 1;
        }
    }
    else {
        if (length(L) == 0){
            fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
            exit(EXIT_FAILURE);
        }
        else {
            fprintf(stderr, "List Error: calling insertBefore() on List without defined cursor index\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    // preconditions
    if (length(L) > 0 && index(L) >= 0){
        if (index(L) == length(L) - 1){
            append(L, x);
        }
        else {
            Node new = newNode(x);
            L->cursor->next->prev = new;
            new->next = L->cursor->next;
            L->cursor->next = new;
            new->prev = L->cursor;
            // increase length
            L->length += 1;
        } 
    }
    else {
        if (length(L) == 0){
            fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
            exit(EXIT_FAILURE);
        }
        else {
            fprintf(stderr, "List Error: calling insertAfter() on List without defined cursor index\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
    // precondition
    if (length(L) > 0){
        // only one node
        if (length(L) == 1) {
            freeNode(&L->front);
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }
        else {
            // new front
            L->front = L->front->next;
            // free and null current front
            freeNode(&L->front->prev);
            // decrease index
            L->index -= 1;
            // cursor gone
            if (L->index < 0){
                L->cursor = NULL;
            }
        }
        // decrease length
        L->length -= 1;
    }
    else {
        fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
    // precondition
    if (length(L) > 0){
        // only one node
        if (length(L) == 1) {
            freeNode(&L->back);
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }
        else {
            // new back node
            L->back = L->back->prev;
            // free and null current back
            freeNode(&L->back->next);
            // cursor gone
            if (L->index == L->length - 1){
                L->cursor = NULL;
                L->index = -1;
            }
        }
        // decrease length
        L->length -= 1;
    }
    else {
        fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    // preconditions
    if (length(L) > 0 && index(L) >= 0){
        // check if front or back
        if (L->cursor == L->front){
            deleteFront(L);
        }
        else if (L->cursor == L->back){
            deleteBack(L);
        }
        else {
            // connect prev and next nodes of cursor
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            // free and null cursor
            freeNode(&L->cursor);
            L->cursor = NULL;
            L->index = -1;
            // decrease length
            L->length -= 1;
        }
    }
    else {
        if (length(L) == 0){
            fprintf(stderr, "List Error: calling delete() on empty List\n");
            exit(EXIT_FAILURE);
        }
        else {
            fprintf(stderr, "List Error: calling delete() on List without defined cursor index\n");
            exit(EXIT_FAILURE);
        }
    }
}
// ----------------------------------------------------------------------------
 
// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a 
// string representation of L consisting 
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
    // check L exists
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    // original index and cursor of L
    int oIndex = L->index;
    Node oCursor = L->cursor;
    moveFront(L);
    while (index(L) >= 0){
        int x = get(L);
        fprintf(out, "%d ", x);        
        moveNext(L);
    }
    // result L to original state
    L->index = oIndex;
    L->cursor = oCursor;
}

// Returns a new List representing the same integer 
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
List copyList(List L){
    // check L exists
    if (L == NULL) {
        fprintf(stderr, "List Error: calling copyList() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    // original index and cursor of L
    int oIndex = L->index;
    Node oCursor = L->cursor;
    // create new list
    List nL = newList();
    // empty list
    if (length(L) == 0){
        return nL;
    }
    // current node to copy
    moveFront(L);
    while (index(L) >= 0){
        int x = get(L);
        append(nL, x);        
        moveNext(L);
    }
    // result L to original state
    L->index = oIndex;
    L->cursor = oCursor;
    return nL;
}
// ----------------------------------------------------------------------------
