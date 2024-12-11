#include "MatrixGraph.h"
#include "ListGraph.h"

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	m_Mat = new int*[size];
	for(int i=0; i<size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for(int i=0; i<getSize(); i++)
	{
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getAllEdges(vector<Edge>* v) {
	for (int i = 0; i < m_Size; i++) {
		for (int j = 0; j < m_Size; j++) {
			if (m_Mat[i][j]) {
				Edge e(i, j, m_Mat[i][j]);
				v->push_back(e);
			}
		}
	}
}

void MatrixGraph::getEdges(int vertex, map<int, int>* m) {
	for (int i = 0; i < m_Size; i++) {
		if (m_Mat[vertex][i]) {
			m->insert({ i, m_Mat[vertex][i] });
		}
	}
	for (int i = 0; i < m_Size; i++) {
		if (m_Mat[i][vertex]) {
			m->insert({ i, m_Mat[i][vertex] });
		}
	}
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{
	for (int i = 0; i < m_Size; i++) {
		if (m_Mat[vertex][i]) {
			m->insert({i, m_Mat[vertex][i]});
		}
	}
	return;
}

void MatrixGraph::insertEdge(int from, int to, int weight)
{
	m_Mat[from][to] = weight;
	return;
}

bool MatrixGraph::printLog(ostream* os) {
	if (m_Size < 0)
		return 1;

	*os << "===== PRINT =====" << endl;

	*os << '\t';
	for (int i = 0; i < m_Size; i++)
	{
		*os << "[" << i << "]" << '\t';
	}
	*os << endl;

	for (int i = 0; i < m_Size; i++)
	{
		*os << "[" << i << "]";
		for (int j = 0; j < m_Size && *os << '\t'; j++)
		{
			*os << m_Mat[i][j];
		}
		*os << endl;
	}
	*os << "================" << endl;
	return 0;
}

bool MatrixGraph::printGraph()
{
	if( m_Size < 0 )
		return 1;

	cout<<"Graph is MatrixGraph!"<<endl;

	cout<<'\t';
	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]"<<'\t';
	}
	cout<<endl;

	for(int i=0; i<m_Size; i++)
	{
		cout<<"["<<i<<"]";
		for(int j=0; j<m_Size && cout<<'\t'; j++)
		{
			cout<<m_Mat[i][j];
		}
		cout<<endl;
	}
	return 0;
}
