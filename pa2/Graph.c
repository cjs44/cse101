/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA2 
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
    int *dist;
    // num vertices
    int order;
    // num edges
    int size;
    // most recent source v
    int source;
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
    G->dist = calloc(n + 1, sizeof(int));
    // set defaults for every element in the arrays
    // loop from 1 so index is same as vertex value
    for (int i = 1; i < n + 1; i++){
        G->nArr[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    // set other defaults
    G->order = n;
    G->size = 0;
    G->source = NIL;
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
        free((*pG)->dist);
        (*pG)->dist = NULL;
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

// returns the source vertex most recently used in function BFS()
// NIL if BFS() has not yet been called
int getSource(Graph G){
    if (G != NULL){
        return G->source;
    }
    else {
        fprintf(stderr, "Graph Error: calling getSource() on empty Graph\n");
        exit(EXIT_FAILURE);
    }
}

// return the parent of vertex u in the BFS tree created by BFS()
// NIL if BFS() has not yet been called.
// precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
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

// returns the distance from the most recent BFS source to vertex u
// INF if BFS() has not yet been called
// precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺)
int getDist(Graph G, int u){
    // precondition
    if (1 <= u && u <= getOrder(G)){
        return G->dist[u];
    }
    else {
        // error message
        fprintf(stderr, "Graph Error: calling getDist() out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// appends to the List L the vertices of a shortest path in G from 
// source to u, appends to L the value NIL if no such path exists
// precondition: 1 ≤ 𝑢 ≤ getOrder(𝐺) and getSource(G)!=NIL - BFS() must 
// be called before getPath()
void getPath(List L, Graph G, int u){
    // precondition
    if ((1 <= u && u <= getOrder(G)) && (getSource(G) != NIL)){
        // no path, append NIL
        if (getDist(G, u) == INF){
            append(L, NIL);
        }
        // if source is u
        else if (getSource(G) == u){
            append(L, u);
        }
        // all other cases
        else {
            // recursive call
            getPath(L, G, getParent(G, u));
            append(L, u);
        }
    }
    else {
        // error message
        if (getSource(G) == NIL){
            fprintf(stderr, "Graph Error: calling getPath() before BFS()\n");
            exit(EXIT_FAILURE);
        }
        else {
            fprintf(stderr, "Graph Error: calling getPath() out of bounds\n");
            exit(EXIT_FAILURE);
        }
    }
}
// ------------------------------------------------

// Manipulation procedures ------------------------
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
    // set all arrays back to defaults
    for (int i = 1; i < getOrder(G) + 1; i++){
        clear(G->nArr[i]);
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    // set others to defaults
    G->size = 0;
    G->source = NIL;
}

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

// runs the BFS algorithm on the Graph G with source s, setting the color, 
// distance, parent, and source fields of G accordingly
void BFS(Graph G, int s){
    /*
BFS(G,s)
   for x in V(G)-{s}
        color[x] = white
        d[x] = inf
        p[x] = nil 
   color[s] = gray       // discover the source s
   d[s] = 0
   p[s] = nil 
   Q = { }               // construct a new empty queue
   Enqueue(Q,s)
   while Q ≠ { }
        x = Dequeue(Q) 
        for y in adj[x]
             if color[y] == white         // y is undiscovered
                  color[y] = gray         // discover y
                  d[y] = d[x]+1
                  p[y] = x
                  Enqueue(Q,y)
        color[x] = black                  // finish x */
    for (int i = 1; i < getOrder(G) + 1; i++){
        // don't reset source
        if (i != s){
            G->color[i] = 0;
            G->dist[i] = INF;
            G->parent[i] = NIL;
        }
    }
    // discover source
    G->source = s;
    G->color[s] = 1;
    G->dist[s] = 0;
    G->parent[s] = NIL;
    // new List
    List Q = newList();
    append(Q, s);
    while (length(Q) != 0) {
        int x = front(Q); 
        deleteFront(Q);
        // cursor of G adj list for x to the front (for traversal)
        moveFront(G->nArr[x]);
        // loop for entire G->nArr[x]
        for (int i = 0; i < length(G->nArr[x]); i++) {
            // y is the value at the cursor
            int y = get(G->nArr[x]);
            if (G->color[y] == 0) { // y is undiscovered
                // discover y
                G->color[y] = 1;
                G->dist[y] = G->dist[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
            // move cursor over one
            moveNext(G->nArr[x]);
        }
        // x is finished
        G->color[x] = 2;
    }
    // free Q
    freeList(&Q);
}
// ------------------------------------------------

// Other operations ----------------------------
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
