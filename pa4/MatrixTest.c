/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA4 
* MatrixTest.c 
* Tests for Matrix ADT 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

// tests things that fail preconditions

int main(void){
    Matrix M = newMatrix(3);
    Matrix A = newMatrix(3);
    ////////// in 1
    changeEntry(M, 1, 1, 1);
    changeEntry(M, 1, 2, 2);
    changeEntry(M, 1, 3, 3);
    changeEntry(M, 2, 1, 4);
    changeEntry(M, 2, 2, 5);
    changeEntry(M, 2, 3, 6);
    changeEntry(M, 3, 1, 7);
    changeEntry(M, 3, 2, 8);
    changeEntry(M, 3, 3, 9);
    
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);
    changeEntry(A, 3, 1, 1);
    changeEntry(A, 3, 2, 1);
    changeEntry(A, 3, 3, 1);
    /////////////////
    printf("nz (9): %d\n", NNZ(M));
    printMatrix(stdout, M);
    printf("\n");
    printf("nz (5): %d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");
    printf("equals: %d\n", equals(M, A));

    printf("copy of A\n");
    Matrix B = copy(A);
    printf("equals: %d\n", equals(A, B));

    printf("transpose of M\n");
    Matrix MT = transpose(M);
    printMatrix(stdout, MT);
    printf("\n");

    printf("M * 3\n");
    Matrix scalar = scalarMult(3.0, M);
    printMatrix(stdout, scalar);
    printf("\n");

    printf("M + A\n");
    Matrix add = sum(M, A);
    printMatrix(stdout, add);
    printf("\n");

    printf("M - A\n");
    Matrix sub = diff(M, A);
    printMatrix(stdout, sub);
    printf("\n");

    printf("M * A\n");
    Matrix p = product(M, A);
    printMatrix(stdout, p);
    printf("\n");


    freeMatrix(&M);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&MT);
    freeMatrix(&scalar);
    freeMatrix(&add);
    freeMatrix(&sub);
    freeMatrix(&p);
    return 0;
}