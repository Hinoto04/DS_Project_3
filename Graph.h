#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include "Edge.h"

using namespace std;

#define MAX 999999

class Graph{
protected:
	bool m_Type;//0:List 1:Matrix
	int m_Size;

public:
	Graph(bool type, int size);
	~Graph();

	bool getType();
	int getSize();
	
	// To Kruskal, Get All Edges to class Edge -> in Edge.h
	virtual void getAllEdges(vector<Edge>* v) = 0;
	// To BFS or DFS, Get Adjacent Un-Directed Edges
	virtual void getEdges(int vertex, map<int, int>* m) = 0;
	virtual void getAdjacentEdges(int vertex, map<int, int>* m) = 0;
	virtual void insertEdge(int from, int to, int weight) = 0;
	virtual bool printLog(ostream* os) = 0;
	virtual	bool printGraph() = 0;
};

#endif
