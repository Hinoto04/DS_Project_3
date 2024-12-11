#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{
private:
	map < int, int >* m_List;

public:	
	ListGraph(bool type, int size);
	~ListGraph();
	
	void getAllEdges(vector<Edge>* v);
	void getEdges(int vertex, map<int, int>* m);
	void getAdjacentEdges(int vertex, map<int, int>* m);
	void insertEdge(int from, int to, int weight);
	bool printLog(ostream* os);
	bool printGraph();
};

#endif