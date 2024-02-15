/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA3 
* Graph.c 
* Graph ADT implementation 
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"

// GraphObj struct definition
typedef struct GraphObj{
    // neighbors (adjacency list)
    List *nArr;
    // white = 0, gray = 1, black = 2
    int *color;
    int *parent;
    // time
    int *discover;
    int *finish;
    // num vertices
    int order;
    // num edges
    int size;
} GraphObj;

// Constructors-Destructors ------------------------
// returns a Graph pointing to a newly created GraphObj 
// representing a graph having n vertices and no edges.
Graph newGraph(int n){
    // allocate memory
    Graph G = calloc(1, sizeof(GraphObj));
    assert(G != NULL);
    // create arrays (size n + 1)
    G->nArr = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    // set defaults for every element in the arrays
    // loop from 1 so index is same as vertex value
    for (int i = 1; i < n + 1; i++){
        G->nArr[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    // set other defaults
    G->order = n;
    G->size = 0;
    return G;
}

//  frees all heap memory associated with the Graph 
// *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    // free and null
    if (pG != NULL && *pG != NULL){
        // free and null every list
        for (int i = 1; i < getOrder(*pG) + 1; i++){
            freeList(&(*pG)->nArr[i]);
        }
        free((*pG)->nArr);
        (*pG)->nArr = NULL;
        free((*pG)->color);
        (*pG)->color = NULL;
        free((*pG)->parent);
        (*pG)->parent = NULL;
        free((*pG)->discover);
        (*pG)->discover = NULL;
        free((*pG)->finish);
        (*pG)->finish = NULL;
        free(*pG);
        *pG = NULL;
    }
}
// ------------------------------------------------

// Access functions ------------------------------
// return the order of G
int getOrder(Graph G){
    if (G != NULL){
        return G->order;
    }
    else {
        fprintf(stderr, "Graph Error: calling getOrder() on empty Graph\n");
        exit(EXIT_FAILURE);
    }
}

// return the size of G
int getSize(Graph G){
    if (G != NULL){
        return G->size;
    }
    else {
        fprintf(stderr, "Graph Error: calling getSize() on empty Graph\n");
        exit(EXIT_FAILURE);
    }
}

// return the parent of vertex u in the tree 
// can be NIL
// precondition: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u){
    // preconditions
    if (1 <= u && u <= getOrder(G)){
        return G->parent[u];
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling getParent() out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// returns the discover time of the vertex u
// UNDEF if DFS() has not yet been called
// precondition: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
    // precondition
    if (1 <= u && u <= getOrder(G)){
        return G->discover[u];
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling getDiscover() out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// returns the finish time of the vertex u
// UNDEF if DFS() has not yet been called
// precondition: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
    // precondition
    if (1 <= u && u <= getOrder(G)){
        return G->finish[u];
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling getFinish() out of bounds\n");
        exit(EXIT_FAILURE);
    }
}
// ------------------------------------------------

// Manipulation procedures ------------------------
// inserts a new edge joining u to v, i.e. u is added to the adjacency 
// List of v, and v to the adjacency List of u
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
    // precondition
    if ((1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G))){
        addArc(G, v, u);
        addArc(G, u, v);
        // decrease size one because 2 was added from addArc calls
        G->size -= 1;
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling addEdge() with arguments out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// inserts a new directed edge from u to v, i.e. v is added to the adjacency 
// List of u (but not u to the adjacency List of v)
// precondition: two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
    // precondition
    if ((1 <= u && u <= getOrder(G)) && (1 <= v && v <= getOrder(G))){
        // check that it hasn't already been added 
        moveFront(G->nArr[u]);
        for (int i = 1; i < length(G->nArr[u]) + 1; i++){
            if (get(G->nArr[u]) != v){
                moveNext(G->nArr[u]);
            }
            else {
                return;
            }
        }
        // insert in order (like in Lex.c)
        // empty List
        if (length(G->nArr[u]) == 0){
            append(G->nArr[u], v);
        }
        // set the cursor at the back of the list
        moveBack(G->nArr[u]);
        // make sure index isn't -1
        // move the cursor towards the front if the array at the cursor should be after the i
        while (index(G->nArr[u]) >= 0 && get(G->nArr[u]) > v){
                movePrev(G->nArr[u]);
        }
        // move the i after the cursor since it is bigger
        if (index(G->nArr[u]) >= 0){
            if (get(G->nArr[u]) != v){
                insertAfter(G->nArr[u], v);
            }
        }
        // i at beginning of list since it is smallest
        else {
            prepend(G->nArr[u], v);
        }
        G->size += 1;
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling addArc() with arguments out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// private helper function for DFS
void visit(Graph G, int u, List s, int *time){
    /*
   Visit(x)
   d[x] = (++time)          // discover x
   color[x] = gray            
   for all y in adj[x]
      if color[y] == white 
         p[y] = x
         Visit(y)
   color[x] = black 
   f[x] = (++time)          // finish x */
    *time += 1;
    G->discover[u] = *time;
    G->color[u] = 1;
    // move cursor to traverse adj list
    moveFront(G->nArr[u]);
    for (int i = 1; i < length(G->nArr[u]) + 1; i++){
        int y = get(G->nArr[u]);
        if (G->color[y] == 0){
            G->parent[y] = u;
            visit(G, y, s, time);
        }
        moveNext(G->nArr[u]);
    }
    G->color[u] = 2;
    *time += 1;
    G->finish[u] = *time;
    // add finished vertex to list
    // "push" by inserting at the end
    append(s, u);
}

// runs the DFS algorithm on the Graph G with source s
// List s define process order for the main loop and stores
// vertices by decreasing finish times 
// precondition: length(S) == getOrder(G)
void DFS(Graph G, List s){
    /*
DFS(G)
   for all x in V(G)
      color[x] = white 
      p[x] = nil 
   time = 0
   for all x in V(G)  // main loop of DFS
      if color[x] == white 
         Visit(x) */
    // precondition
    if (length(s) == getOrder(G)){
        // set to 0 and NIL
        for (int i = 1; i < getOrder(G) + 1; i++){
            G->color[i] = 0;
            G->parent[i] = NIL;
        }
        // to be passed to visit()
        int time = 0;
        // main DFS loop
        for (int i = 1; i < getOrder(G) + 1; i++){
            // traverse in the order of elements in s
            int x = front(s);
            if (G->color[x] == 0){
                // call helper
                visit(G, x, s, &time);
            }
            // "pop" by deleting the front
            deleteFront(s);
        }
        // reverse the list
        List copy = copyList(s);
        moveBack(copy);
        for (int i = 1; i < length(s) + 1; i++){
            deleteFront(s);
            append(s, get(copy));
            movePrev(copy);
        }
        freeList(&copy);
    }
    else {
        // error message
        fprintf(stderr, "List/Graph Error: calling DFS() with arguments not of same length\n");
        exit(EXIT_FAILURE);
    }
}
// ------------------------------------------------

// Other operations ----------------------------
// returns a reference to a new graph object representing the 
// transpose of G
Graph transpose(Graph G){
    // new graph
    Graph new = newGraph(getOrder(G));
    // copy opposite order from G
    for (int i = 1; i < getOrder(G) + 1; i++){
        // move cursor to back of original
        moveBack(G->nArr[i]);
        // make sure index isn't -1
        while (index(G->nArr[i]) >= 0){
            // create arc and move cursor
            int x = get(G->nArr[i]);
            addArc(new, x, i);
            movePrev(G->nArr[i]);
        }
    }
    return new;
}

// returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G){
    // new graph
    Graph new = newGraph(getOrder(G));
    // copy from G
    for (int i = 1; i < getOrder(new) + 1; i++){
        // move cursor to front of original
        moveFront(G->nArr[i]);
        // make sure index isn't -1
        while (index(G->nArr[i]) >= 0 ){
            // create arc and move cursor
            int x = get(G->nArr[i]);
            addArc(new, i, x);
            moveNext(G->nArr[i]);
        }
    }
    return new;
}

// prints the adjacency list representation of G to the file pointed to by out
// contains all formatting 
void printGraph(FILE* out, Graph G){
    /* format ex.
    1: 4 5
    2: 3 6
    3: 2 7
    4: 1 5 */
    // adjacency list representation
    for(int i = 1; i < getOrder(G) + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->nArr[i]);
        fprintf(out, "\n");
    }
}
// -----------------------------------------------
