#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Graph.h"

class MatrixGraph : public Graph{
private:
	int** m_Mat;

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();
	
	void getAllEdges(vector<Edge>* v);
	void getEdges(int vertex, map<int, int>* m);
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printLog(ostream* os);
	bool printGraph();
};

#endif