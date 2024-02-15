/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA2 
* GraphTest.c 
* Tests for Graph ADT 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// tests things that fail preconditions

int main(void){
    Graph G = newGraph(4);
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 3);
    addEdge(G, 2, 4);
    printGraph(stdout, G);
    BFS(G, 2);
    printf("source (2): %d\n", getSource(G));
    printf("distance (1): %d\n", getDist(G, 4));
    printf("parent (2): %d\n", getParent(G, 3));
    printf("order (4): %d\n", getOrder(G));
    printf("size (4): %d\n", getSize(G));
    BFS(G, 1);
    printf("distance (2): %d\n", getDist(G, 4));
    printf("parent (2): %d\n", getParent(G, 4));
    List L = newList();
    getPath(L, G, 4);
    printList(stdout, L);

    freeList(&L);
    freeGraph(&G);

    return 0;
}