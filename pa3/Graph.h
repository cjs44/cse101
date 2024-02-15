/************************************************ 
* Caitlin Smith - csmith44 
* 2023 Spring CSE101 PA3
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
#define UNDEF -1
#define NIL 0

// Constructors-Destructors ------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures ------------------------
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);

// Other operations ----------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
