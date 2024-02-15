/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA2 
* FindPath.c 
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
    // reading
    int n = 0;
    int vertex, neighbor = NIL; 

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
        addEdge(G, vertex, neighbor);
        fscanf(in, "%d %d", &vertex, &neighbor);
    }
    
    // print adj list of finished graph
    printGraph(out, G);
    fprintf(out, "\n");

    // print distances and shortest using bfs
    // 0 0 marks end
    fscanf(in, "%d %d", &vertex, &neighbor);
    while (vertex != 0 && neighbor != 0){
        // call BFS from vertex
        BFS(G, vertex);
        // path
        if (getDist(G, neighbor) != INF){
            int dist = getDist(G, neighbor);
            fprintf(out, "The distance from %d to %d is %d\n", vertex, neighbor, dist);
            // list for the path from vertex to neighbor
            List P = newList();
            getPath(P, G, neighbor);
            fprintf(out, "A shortest %d-%d path is: ", vertex, neighbor);
            printList(out, P);
            fprintf(out, "\n\n");
            // free list
            freeList(&P);
        }
        // no path
        if (getDist(G, neighbor) == INF){
            fprintf(out, "The distance from %d to %d is infinity\n", vertex, neighbor);
            fprintf(out, "No %d-%d path exists\n", vertex, neighbor);
        }
        // next pair
        fscanf(in, "%d %d", &vertex, &neighbor);
    }

    // free memory and close files 
    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;
}