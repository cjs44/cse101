/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA4 
* Sparse.c 
* Main function 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char * argv[]){

    // initialize variables
    FILE *in, *out;
    // line one of infile
    int n = 0;
    int ACount, BCount = 0; 
    // each line for row column value
    int row, col = 0;
    double val = 0.0;

    // check command line for correct number of arguments
    if ( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    out = fopen(argv[2], "w");
    if (out == NULL){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // first line for nums
    fscanf(in, "%d %d %d\n\n", &n, &ACount, &BCount);

    // use that to make matrices
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // scan lines that correspond to pairs in matrix A
    for (int i = 1; i < ACount + 1; i++){
        fscanf(in, "%d %d %lf\n", &row, &col, &val);
        // add to matrix
        changeEntry(A, row, col, val);
    }

    // scan lines that correspond to pairs in matrix B
    for (int i = 1; i < BCount + 1; i++){
        fscanf(in, "%d %d %lf\n", &row, &col, &val);
        // add to matrix
        changeEntry(B, row, col, val);
    }

    // print A and B
    fprintf(out, "A has %d non-zero entries:\n", ACount);
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", BCount);
    printMatrix(out, B);
    fprintf(out, "\n");

    // print operation results
    // 1.5 * A
    fprintf(out, "(1.5)*A =\n");
    Matrix M1 = scalarMult(1.5, A);
    printMatrix(out, M1);
    fprintf(out, "\n");

    // A + B
    fprintf(out, "A+B =\n");
    Matrix M2 = sum(A, B);
    printMatrix(out, M2);
    fprintf(out, "\n");

    // A + A
    fprintf(out, "A+A =\n");
    Matrix M3 = sum(A, A);
    printMatrix(out, M3);
    fprintf(out, "\n");

    // B - A
    fprintf(out, "B-A =\n");
    Matrix M4 = diff(B, A);
    printMatrix(out, M4);
    fprintf(out, "\n");

    // A - A
    fprintf(out, "A-A =\n");
    Matrix M5 = diff(A, A);
    printMatrix(out, M5);
    fprintf(out, "\n");

    // transpose
    fprintf(out, "Transpose(A) =\n");
    Matrix M6 = transpose(A);
    printMatrix(out, M6);
    fprintf(out, "\n");

    // A * B
    fprintf(out, "A*B =\n");
    Matrix M7 = product(A, B);
    printMatrix(out, M7);
    fprintf(out, "\n");
    
    // B * B
    fprintf(out, "B*B =\n");
    Matrix M8 = product(B, B);
    printMatrix(out, M8);

    // free memory and close files 
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&M1);
    freeMatrix(&M2);
    freeMatrix(&M3);
    freeMatrix(&M4);
    freeMatrix(&M5);
    freeMatrix(&M6);
    freeMatrix(&M7);
    freeMatrix(&M8);
    fclose(in);
    fclose(out);

    return 0;
}