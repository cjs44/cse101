/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA3 
* FindComponents.c 
* Main function 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){

    // initialize variables
    FILE *in, *out;
    int n = 0;
    int vertex, neighbor = NIL; 
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

    // first line for num of vertices
    fscanf(in, "%d", &n);

    // use that to make graph
    Graph G = newGraph(n);

    // get vertices and their neighbors to make graph (0 0 marks end)
    // get first so it enters loop
    fscanf(in, "%d %d", &vertex, &neighbor);
    while (vertex != 0 && neighbor != 0){
        addArc(G, vertex, neighbor);
        fscanf(in, "%d %d", &vertex, &neighbor);
    }
    
    // print adj list of finished graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // run DFS on G, output to list s
    // s has vertices in order
    List s = newList();
    for (int i = 1; i < n + 1; i++){
        append(s, i);
    }
    DFS(G, s);

    // transpose G, run DFS, output to list s
    Graph GT = transpose(G);
    DFS(GT, s);

    // print the number of SCC
    // each root of an SCC has nil parent
    moveFront(s);
    for (int i = 1; i < n + 1; i++){
        if (getParent(GT, get(s)) == NIL){
            count += 1;
        }
        moveNext(s);
    }
    fprintf(out, "G contains %d strongly connected components:\n", count);

    // print the SCC in topological order
    // read up, print down from root
    count = 0;
    // list to then "print down" for each root
    List SCC = newList();
    moveBack(s);
    for (int i = 1; i < n + 1; i++){
        // add to list front front
        prepend(SCC, get(s));
        if (getParent(GT, get(s)) == NIL){
            count += 1;
            fprintf(out, "Component %d: ", count);
            printList(out, SCC);
            fprintf(out, "\n");
            // clear for next SCC
            clear(SCC);
        }
        movePrev(s);
    }
    
    // free memory and close files 
    freeGraph(&G);
    freeGraph(&GT);
    freeList(&s);
    freeList(&SCC);
    fclose(in);
    fclose(out);

    return 0;
}