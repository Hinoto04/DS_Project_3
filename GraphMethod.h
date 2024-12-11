#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, int vertex, ostream* os);
bool DFS(Graph* graph, int vertex, ostream* os);
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ostream* os);
bool Kruskal(Graph* graph, ostream* os);
bool Dijkstra(Graph* graph, int vertex, ostream* os);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ostream* os);
bool FLOYD(Graph* graph, ostream* os);

#endif
