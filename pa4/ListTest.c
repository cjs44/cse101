/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA4 
* ListTest.c 
* Tests for List ADT 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// tests things that fail preconditions

int main(void){
    List L = newList();
    int a = 3;
    int b = 7;
    int c = 2;
    int d = 9;
    prepend(L, &a);
    //printList(stdout, L);
    //printf("\n3\n");
    append(L, &b);
    append(L, &c);
    //printList(stdout, L);
    //printf("\n3 7 2\n");
    printf("length (3): %d\n", length(L));
    moveFront(L);
    moveNext(L);
    printf("index (1): %d\n", index(L));
    insertBefore(L, &d); 
    //printList(stdout, L);
    //printf("\n3 9 7 2\n");   
    int e = 4;
    prepend(L, &e);
    //printList(stdout, L);
    //printf("\n4 3 9 7 2\n");
    printf("length (5): %d\n", length(L));
    printf("index (3): %d\n", index(L));
    printf("front (4): %d\n", *(int *)front(L));
    printf("back (2): %d\n", *(int *)back(L));
    printf("get (7): %d\n", *(int *)get(L));

    freeList(&L);

    return 0;
}