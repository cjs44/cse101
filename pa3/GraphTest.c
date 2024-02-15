/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA3 
* GraphTest.c 
* Tests for Graph ADT 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// tests things that fail preconditions

int main(void){
    /*Graph G = newGraph(9);
    //////////
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 4);
    addArc(G, 3, 2);
    addArc(G, 4, 3);
    addArc(G, 5, 3);
    addArc(G, 5, 6);
    addArc(G, 6, 8);
    addArc(G, 8, 7);
    addArc(G, 7, 5);
    addArc(G, 9, 7);
    /////////////////
    printGraph(stdout, G);
    printf("order (9): %d\n", getOrder(G));
    printf("size (11): %d\n", getSize(G));

    List L = newList();
    for (int i = 1; i <= 9; i++){
        append(L, i);
    }
    DFS(G, L);
    printList(stdout, L);
    printf("parent (6): %d\n", getParent(G, 8));
    printf("discover (11): %d\n", getDiscover(G, 8));
    printf("finish (14): %d\n", getFinish(G, 8));
    
    Graph T = transpose(G);
    DFS(T, L);
    printList(stdout, L); */

/*
    // infile4
    Graph G = newGraph(8);
    //////////
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);
    /////////////////
    printGraph(stdout, G);
    List L = newList();
    for (int i = 1; i <= 8; i++){
        append(L, i);
    }
    DFS(G, L);
    printList(stdout, L);
    printf("\n");
    Graph T = transpose(G);
    DFS(T, L);
    printList(stdout, L); */

    Graph A = newGraph(100);
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    List L = newList();
    for (int i = 1; i <= 100; i++) {
      prepend(L, i);
    }
    DFS(A, L);
    printf("discover (1): %d\n", getDiscover(A, 100));

    // Graph C = copyGraph(G);
    // printGraph(stdout, C);

    freeList(&L);
    freeGraph(&A);

    return 0;
}