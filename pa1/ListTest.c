/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA1 
* ListTest.c 
* Tests for List ADT 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// tests things that fail preconditions

int main(void){
    List L = newList();
    prepend(L, 3);
    printList(stdout, L);
    printf("\n3\n");
    append(L, 7);
    append(L, 2);
    printList(stdout, L);
    printf("\n3 7 2\n");
    printf("length (3): %d\n", length(L));
    moveFront(L);
    moveNext(L);
    printf("index (1): %d\n", index(L));
    insertBefore(L, 9); 
    printList(stdout, L);
    printf("\n3 9 7 2\n");   
    prepend(L, 4);
    printList(stdout, L);
    printf("\n4 3 9 7 2\n");
    printf("length (5): %d\n", length(L));
    printf("index (3): %d\n", index(L));
    printf("front (4): %d\n", front(L));
    printf("back (2): %d\n", back(L));
    printf("get (7): %d\n", get(L));
    List b = copyList(L);
    printf("equals (true): %d\n", equals(L, b));
    set(L, 1); 
    printList(stdout, L);
    printf("\n4 3 9 1 2\n");
    clear(L);
    append(L, 8);
    append(L, 2);
    moveBack(L);
    movePrev(L);
    printf("get (8): %d\n", get(L));
    insertAfter(L, 5);
    printList(stdout, L);
    printf("\n8 5 2\n");
    deleteFront(L);
    deleteBack(L);
    printList(stdout, L);
    printf("\n5\n");
    freeList(&L);

    return 0;
}