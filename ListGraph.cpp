#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAllEdges(vector<Edge>* v) {
	for (int i = 0; i < m_Size; i++) {
		for (auto iter = m_List[i].begin(); iter != m_List[i].end(); iter++) {
			Edge e(i, iter->first, iter->second);
			v->push_back(e);
		}
	}
}

void ListGraph::getEdges(int vertex, map<int, int>* m) {
	getAdjacentEdges(vertex, m);
	for (int i = 0; i < m_Size; i++) {
		auto temp = m_List[i].find(vertex);
		if (temp != m_List[i].end()) {
			m->insert({ i, temp->second });
		}
	}
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	*m = m_List[vertex];
	return;
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to, weight});
	return;
}

// Print to fout
bool ListGraph::printLog(ostream* os) {
	*os << "===== PRINT =====" << endl;

	for (int i = 0; i < m_Size; i++)
	{
		*os << "[" << i << "]";

		for (auto it_ = m_List[i].begin(); it_ != m_List[i].end() && *os << " -> "; it_++)
		{
			*os << "(" << it_->first << "," << it_->second << ")";
		}
		*os << endl;
	}
	*os << "=================" << endl;
	return 0;
}

bool ListGraph::printGraph()
{
	cout<<"Graph is ListGraph!"<<endl;

	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && cout<<" -> "; it_++)
		{
			cout<<"("<<it_->first<<","<<it_->second<<")";
		}
		cout<<endl;
	}
	cout<<endl;
	return 0;
}