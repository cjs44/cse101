/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA4
* Matrix.c 
* Matrix ADT implementation 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Matrix.h"

// struct definitions --------------------------------------------------------
// Entry ADT
typedef struct EntryObj* Entry;
typedef struct EntryObj {
    int col;
    double value;
} EntryObj;

// Matrix ADT
typedef struct MatrixObj {
    List *row;
    int size;
    int nz;
} MatrixObj;
//---------------------------------------------------------------------------

// Constructors-Destructors ---------------------------------------------------
// Creates and returns a new empty Entry ADT
Entry newEntry(int col, double value){
    // allocate memory and set defaults
    Entry E = malloc(sizeof(EntryObj));
    assert(E != NULL);
    // set to null and parameter
    E->col = col;
    E->value = value;
    return E;
} 

// Frees all heap memory associated with *pE, and sets *pE to NULL
void freeEntry(Entry* pE){
    // free and null
    if (pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    // allocate memory and set defaults
    Matrix M = malloc(sizeof(MatrixObj));
    assert(M != NULL);
    // allocate and set for the row lists
    M->row = (List *) calloc(n + 1, sizeof(List *));
    // index starts at 1
    for (int i = 1; i < n + 1; i++){
        // newList
        M->row[i] = newList();
    }
    // set to parameter and 0
    M->size = n;
    M->nz = 0;
    return M;
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    // free and null
    if (pM != NULL && *pM != NULL){
        makeZero(*pM);
        // free and null every list
        for (int i = 1; i < size(*pM) + 1; i++){
            if ((*pM)->row[i] != NULL){
                freeList(&((*pM)->row[i]));
                (*pM)->row[i] = NULL;
            }
        }
        free((*pM)->row);
        (*pM)->row = NULL;
        free(*pM);
        *pM = NULL;
    }
}
// ----------------------------------------------------------------------------

// Access functions -----------------------------------------------------------
// Return the size of square Matrix M.
int size(Matrix M){
    if (M != NULL){
        return M->size;
    }
    else {
        fprintf(stderr, "Matrix Error: calling size() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if (M != NULL){
        return M->nz;
    }
    else {
        fprintf(stderr, "Matrix Error: calling NNZ() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A != NULL && B != NULL){
        // not same length or NNZ
        if (size(A) != size(B)){
            // return false
            return 0;
        }
        if (NNZ(A) != NNZ(B)){
            return 0;
        }
        // traverse and check each entry's equivalence (check each row)
        for (int i = 1; i < size(A) + 1; i++){
            // lists to compare
            List ListA = A->row[i];
            List ListB = B->row[i];
            moveFront(ListA);
            moveFront(ListB);
            // traverse the row
            while (index(ListA) >= 0){
                // entry from each list
                Entry EntryA = get(ListA);
                Entry EntryB = get(ListB);
                // not the same col and val, return false
                if (EntryA->col != EntryB->col){
                    return 0;
                }
                if (EntryA->value != EntryB->value){
                    return 0;
                }
                // next entry if it passes other tests
                moveNext(ListA);
                moveNext(ListB);
            }
        }
        return 1;
    }
    else {
        fprintf(stderr, "Matrix Error: calling equals() on at least one empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}
// ----------------------------------------------------------------------------

// Manipulation procedures ----------------------------------------------------
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    // set to 0
    M->nz = 0;
    // delete Entrys for each row
    for (int i = 1; i < size(M) + 1; i++){
        // list to compare
        List R = M->row[i];
        // traverse the row and free/delete each entry
        moveFront(R);
        while (index(R) >= 0){
            // front as new entry
            Entry F = get(R);
            freeEntry(&F);
            moveNext(R);
        }
        clear(R);
    }
}

// Changes the ith row, jth col of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    // precondition
    if ((1 <= i && i <= size(M)) && (1 <= j && j <= size(M))){
        // row list to edit
        List L = M->row[i];
        // passed value is 0
        if (x == 0.0){
            if (length(L) != 0){
                // traverse list
                moveFront(L);
                while (index(L) >= 0){
                    Entry E = get(L);
                    // if j is there, delete the entry
                    if (E->col == j){
                        freeEntry(&E);
                        delete(L);
                        M->nz -= 1;
                        break;
                    }
                    moveNext(L);
                }
            }
        } 
        else {
            // flag to track if it is done
            int flag = 0;
            // new entry to add
            Entry NE = NULL;
            if (length(L) != 0){
                // traverse
                moveFront(L);
                while (index(L) >= 0){
                    Entry E = get(L);
                    // found j
                    if (E->col == j){
                        E->value = x;
                        flag = 1;
                        break;
                    }
                    // j needs to be before current 
                    if (E->col > j){
                        NE = newEntry(j, x);
                        insertBefore(L, NE);
                        flag = 1;
                        break;
                    }
                    moveNext(L);
                }
            }
            // append the new entry
            if (!flag) {
                NE = newEntry(j, x);
                append(L, NE);
            }
            // increase
            M->nz += 1;
        }
    } 
    else {
        fprintf(stderr, "Matrix Error: calling changeEntry() on Entry out of range\n");
        exit(EXIT_FAILURE);
    }
}
// ----------------------------------------------------------------------------

// Matrix Arithmetic operations------------------------------------------------
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A != NULL){
        Matrix C = newMatrix(size(A));
        // copy each A entry to C
        for (int i = 1; i < size(A) + 1; i++){
            // list to copy
            List L = A->row[i];
            // check that it's not empty
            if (length(L) != 0){
                moveFront(L);
                // traverse the row
                while (index(L) >= 0){
                    // new entry with A contents
                    Entry E = newEntry(((Entry)get(L))->col, ((Entry)get(L))->value);
                    // append to row
                    append(C->row[i], E);
                    C->nz += 1;
                    // next
                    moveNext(L);
                }
            }
        }
        return C;
    }
    else {
        fprintf(stderr, "Matrix Error: calling copy() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if (A != NULL){
        Matrix T = newMatrix(size(A));
        for (int i = 1; i < size(A) + 1; i++){
            // list to traverse
            List L = A->row[i];
            // check it's not empty
            if (length(L) != 0){
                moveFront(L);
                // traverse the row
                while (index(L) >= 0){
                    // value at (i, j) becomes value at (j, i)
                    Entry E = get(L);
                    changeEntry(T, E->col, i, E->value);
                    // next
                    moveNext(L);
                }
            }
        }
        return T;
    }
    else {
        fprintf(stderr, "Matrix Error: calling transpose() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if (A != NULL){
        Matrix X = newMatrix(size(A));
        for (int i = 1; i < size(A) + 1; i++){
            List L = A->row[i];
            moveFront(L);
            // traverse the row
            while (index(L) >= 0){
                // new entry with A contents
                changeEntry(X, i, ((Entry)get(L))->col, ((Entry)get(L))->value * x);
                moveNext(L);
            }
        }
        return X;
    }
    else {
        fprintf(stderr, "Matrix Error: calling scalarMult() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// helper function for sum
// return row list with sum of two row A and B
List add(List A, List B){
    List res = newList();
    // traverse
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0){
        Entry EA = get(A);
        Entry EB = get(B);
        // if A's current col is less than B's current col, insert A's entry
        if (EA->col < EB->col){
            Entry NA = newEntry(EA->col, EA->value);
            append(res, NA);
            moveNext(A);
        }
        // if B's current col is less than A's current col, insert B's entry
        else if (EB->col < EA->col){
            Entry NB = newEntry(EB->col, EB->value);
            append(res, NB);
            moveNext(B);
        }
        // if both entries are in the same col, add their values and insert new entry
        else if (EA->col == EB->col){
            double s = EA->value + EB->value;
            if (s != 0) {
                Entry ES = newEntry(EA->col, s);
                append(res, ES);
            }
            moveNext(A);
            moveNext(B);
        }
    }
    // append any remaining 
    while (index(A) >= 0){
        Entry NA = newEntry(((Entry)get(A))->col, ((Entry)get(A))->value);
        append(res, NA);
        moveNext(A);
    }
    while (index(B) >= 0){
        Entry NB = newEntry(((Entry)get(B))->col, ((Entry)get(B))->value);
        append(res, NB);
        moveNext(B);
    }
    return res;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (A != NULL && B != NULL){
        // precondition
        if (size(A) == size(B)){
            Matrix AB = NULL;
            // if they are the same, just mult by 2
            if (A == B){
                AB = scalarMult(2, A);
            }
            else {
                AB = newMatrix(size(A));
                for (int i = 1; i < size(A) + 1; i++){
                    List N = add(A->row[i], B->row[i]);
                    AB->row[i] = N;
                    AB->nz += length(N);
                }
            }
            return AB;
        }
        else {
            fprintf(stderr, "Matrix Error: calling sum() on matrices of different sizes\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        fprintf(stderr, "Matrix Error: calling sum() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// helper function for diff
// return row list with diff of two row A and B
List sub(List A, List B){
    List res = newList();
    // traverse
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0){
        Entry EA = get(A);
        Entry EB = get(B);
        // not same col, sub then move next in the lesser one
        if (EA->col < EB->col){
            Entry NA = newEntry(EA->col, EA->value);
            append(res, NA);
            moveNext(A);
        }
        else if (EB->col < EA->col){
            Entry NB = newEntry(EB->col, -EB->value);
            append(res, NB);
            moveNext(B);
        }
        // entry in same col, need to sub
        else if (EA->col == EB->col){
            double d = EA->value - EB->value;
            if (d != 0){
                Entry ED = newEntry(EA->col, d);
                append(res, ED);
            }
            moveNext(A);
            moveNext(B);
        }
    }
    // append any remaining
    while (index(A) >= 0){
        Entry NA = newEntry(((Entry)get(A))->col, ((Entry)get(A))->value);
        append(res, NA);
        moveNext(A);
    }
    while (index(B) >= 0){
        Entry NB = newEntry(((Entry)get(B))->col, -((Entry)get(B))->value);
        append(res, NB);
        moveNext(B);
    }
    return res;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (A != NULL){
        // precondition
        if (size(A) == size(B)){
            Matrix AB = newMatrix(size(A));
            // if they are the same, return is empty
            // else, subtract
            if (A != B){
                for (int i = 1; i < size(A) + 1; i++){
                    List N = sub(A->row[i], B->row[i]);
                    AB->row[i] = N;
                    AB->nz += length(N);
                }
            }
            return AB;
        }
        else {
            fprintf(stderr, "Matrix Error: calling diff() on matrices of different sizes\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        fprintf(stderr, "Matrix Error: calling diff() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}

// helper function for product
// compute the vector dot product of two row P and Q
double vectorDot(List P, List Q){
    double res = 0.0;
    // make sure neither is empty
    if (length(P) != 0 && length(Q) != 0){
        moveFront(P);
        moveFront(Q);
        while (index(P) >= 0 && index(Q) >= 0){
            Entry EP = get(P);
            Entry EQ = get(Q);
            // entry in same col, need to multiply
            if (EP->col == EQ->col){
                res += EP->value * EQ->value;
                moveNext(P);
                moveNext(Q);
            }
            // not same col, move next in the lesser one
            else if (EP->col < EQ->col){
                moveNext(P);
            }
            else if (EP->col > EQ->col){
                moveNext(Q);
            }
        }
    }
    // one empty list makes the res 0
    return res;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if (A != NULL){
        // precondition
        if (size(A) == size(B)){
            // result
            Matrix AB = newMatrix(size(A));
            // transpose B
            Matrix TB = transpose(B);
            for (int i = 1; i < size(A) + 1; i++){
                for (int j = 1; j < size(A) + 1; j++){
                    List L1 = A->row[i];
                    List L2 = TB->row[j];
                    double res = vectorDot(L1, L2);
                    changeEntry(AB, i, j, res);
                }                    
            }
            // free transpose matrix
            freeMatrix(&TB);
            return AB;
        }
        else {
            fprintf(stderr, "Matrix Error: calling product() on matrices of different sizes\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        fprintf(stderr, "Matrix Error: calling product() on empty Matrix\n");
        exit(EXIT_FAILURE);
    }
}
// ----------------------------------------------------------------------------

// Other operations -----------------------------------------------------------
// Prints a string representation of Matrix M to filestream out. Zero row 
// are not printed. Each non-zero row is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs "(col, val)" giving the col numbers and non-zero values 
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    // 1: (x, y) (x, y) (x, y)
    for (int i = 1; i < size(M) + 1; i++){
        List R = M->row[i];
        // only print nz row
        if (length(R) > 0){
            // print row num
            fprintf(out, "%d:", i);
            // traverse row
            moveFront(R);
            while (index(R) >= 0){
                Entry E = get(R);
                fprintf(out, " (%d, %.1f)", E->col, E->value);
                moveNext(R);
            }
            fprintf(out, "\n");
        }
    }

}
// ----------------------------------------------------------------------------
