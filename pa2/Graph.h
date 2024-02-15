/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Winter CSE101 PA2 
* Graph.h 
* Graph ADt interface 
*************************************************/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// graph struct
typedef struct GraphObj* Graph;

// macros
#define INF -1
#define NIL 0

// Constructors-Destructors ------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation procedures ------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other operations ----------------------------
void printGraph(FILE* out, Graph G);

#endif