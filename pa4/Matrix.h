/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA4
* Matrix.h 
* Matrix ADt interface 
*************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "List.h"

typedef struct EntryObj* Entry;
typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n);
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);

// Access functions -----------------------------------------------------------
// Return the size of square Matrix M.
int size(Matrix M);
// Return the number of non-zero elements in M.
int NNZ(Matrix M);
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M);
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations------------------------------------------------
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

 
// Other operations -----------------------------------------------------------
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero row is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs "(col, val)" giving the column numbers and non-zero values 
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);

#endif
