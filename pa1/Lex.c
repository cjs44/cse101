/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA1 
* Lex.c 
* Main function 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

    // initialize variables
    FILE *in, *out;
    char buff[MAX_LEN];
    char **stringArr;
    int count = 0;

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

    // count lines in file
    while (fgets(buff, MAX_LEN, in) != NULL){
        count++;
    }

    // allocate for string array
    stringArr = (char **) calloc(count, sizeof(char *));

    // reset to reread file
    rewind(in);

    // read from input file
    // buffer index
    int buffIndex = 0;
    while (fgets(buff, MAX_LEN, in) != NULL){
        // allocate for char pointer
        char *c = (char *) calloc(MAX_LEN, sizeof(char));
        stringArr[buffIndex] = c;
        buffIndex += 1;
        // last char in buffer is \0 to indicate the end
        strcpy(c, buff); 
        buff[strlen(buff) - 1] = '\0';
    }

    // create list
    List L = newList();
    // add 0 so it is not empty
    append(L, 0);
    
    // sort entire file using line count and cursor
    // start i at 1 since we already added 0 above
    for (int i = 1; i < count; i++){
        // set the cursor at the back of the list
        moveBack(L);
        // make sure index isn't -1
        // move the cursor towards the front if the array at the cursor should be after the i
        while (index(L) >= 0 && strcmp(stringArr[get(L)], stringArr[i]) >= 0){
            movePrev(L);
        }
        // move the i after the cursor since it is "bigger"
        if (index(L) >= 0){
            insertAfter(L, i);
        }
        // i at beginning of list since it is "smallest"
        else {
            prepend(L, i);
        }
    }

    // print in correct order
    moveFront(L);
    while (index(L) >= 0){
        int x = get(L);
        fprintf(out, "%s\n", stringArr[x]);        
        moveNext(L);
    }

    // free memory and close files 
    for (int i = 0; i < count; i++){
        free(stringArr[i]);
    }
    free(stringArr);
    freeList(&L);
    fclose(in);
    fclose(out);

    return 0;
}