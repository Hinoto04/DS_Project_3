#include "GraphMethod.h"

// Insertion Sort
void insertionSort(vector<Edge>& arr, int low, int high) {
	for (int i = low + 1; i <= high; i++) {
		Edge key = arr[i];
		int j;
		for (j = i - 1; j >= low && arr[j] > key; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

// Swap Less than pivot and Greater than pivot
int partition(vector<Edge>& arr, int low, int high) {
	Edge pivot = arr[high]; // last value is pivot
	int i = low - 1;

	// Swapping
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

// Quick Sort
void quickSort(vector<Edge>& arr, int low, int high) {
	if (low < high) {
		// Insertion Sort Start when segment_size <= 6
		if (high - low + 1 <= 6) {
			insertionSort(arr, low, high);
			return;
		}
		else { // else quicksort
			int pivot_index = partition(arr, low, high); // Partition With Pivot
			quickSort(arr, low, pivot_index - 1);
			quickSort(arr, pivot_index + 1, high);
		}
	}
}

bool BFS(Graph* graph, int vertex, ostream* os)
{
	*os << "===== BFS =====" << endl;
	*os << "startVertex : " << vertex << endl;
	queue<int> q; // Waiting Queue
	q.push(vertex);
	vector<bool> s(graph->getSize()); // Visited Vector

	while (true) {
		int v = q.front();
		*os << v;
		s[v] = true;
		map<int, int> adj;
		graph->getEdges(v, &adj);
		for (auto iter = adj.begin(); iter != adj.end(); iter++) {
			if (!s[iter->first]) {
				q.push(iter->first);
				s[iter->first] = true;
			}
		}
		q.pop();
		if (q.empty()) break;
		*os << " -> ";
	}
	*os << endl << "===============" << endl;
	return 0;
}

bool DFS(Graph* graph, int vertex, ostream* os)
{
	*os << "===== DFS =====" << endl;
	*os << "startVertex : " << vertex << endl;
	stack<int> st; // Waiting Stack
	st.push(vertex);
	vector<bool> s(graph->getSize()); //Visited Vector

	while (true) {
		int v = st.top();
		if (!s[v]) {
			s[v] = true;
			*os << v;
		}
		map<int, int> adj;
		graph->getEdges(v, &adj);
		for (auto iter = adj.begin(); iter != adj.end(); iter++) {
			if (!s[iter->first]) {
				st.push(iter->first);
				*os << " -> ";
				break;
			}
		}
		if(st.top() == v) st.pop();
		if (st.empty()) break;
	}
	*os << endl << "===============" << endl;
	return 0;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ostream* os)
{
	*os << vertex;
	map<int, int> adj;
	visit->at(vertex) = true;
	graph->getEdges(vertex, &adj);
	for (auto iter = adj.begin(); iter != adj.end(); iter++) {
		if (!visit->at(iter->first)) {
			*os << " -> ";
			DFS_R(graph, visit, iter->first, os);
		}
	}
	return 0;
}

int find_parent(vector<int>& parent, int now) {
	if (parent[now] != now) {
		return find_parent(parent, parent[now]);
	}
	return now;
}

void union_parent(vector<int>& parent, int a, int b) {
	int pa = find_parent(parent, a);
	int pb = find_parent(parent, b);
	if (pa < pb) parent[pb] = pa;
	else parent[pa] = pb;
}

bool Kruskal(Graph* graph, ostream* os)
{
	// Sort Edges with Weight
	vector<Edge> edges;
	graph->getAllEdges(&edges);
	quickSort(edges, 0, edges.size() - 1);

	// Disjoint set implement with Tree
	map<int, int>* result = new map<int, int>[graph->getSize()];
	vector<int> parent(graph->getSize());
	for (int i = 0; i < graph->getSize(); i++) parent[i] = i;
	int cost = 0;

	for (auto iter = edges.begin(); iter != edges.end(); iter++) {
		//cout << iter->from << " " << iter->to << endl;
		//cout << find_parent(parent, iter->from) << " " << find_parent(parent, iter->to) << endl;
		if (find_parent(parent, iter->from) != find_parent(parent, iter->to)) {
			union_parent(parent, iter->from, iter->to);
			result[iter->from].insert({ iter->to, iter->weight });
			result[iter->to].insert({ iter->from, iter->weight });
			cost += iter->weight;
			//cout << " Unioned" << endl;
		}
		//else {
		//	cout << " Rejected" << endl;
		//}
	}

	bool check = false;
	for (int i = 0; i < graph->getSize(); i++) {
		if (parent[i] == i) {
			if (check) return 1; // Two Different Parent -> Not Connected!!!
			check = true;
		}
	}

	// Result Print
	*os << "===== KRUSKAL =====" << endl;
	for (int i = 0; i < graph->getSize(); i++) {
		*os << "[" << i << "] ";
		for (auto iter = result[i].begin(); iter != result[i].end(); iter++) {
			*os << iter->first << "(" << iter->second << ")" << ' ';
		}
		*os << endl;
	}
	*os << "cost: " << cost << endl;
	*os << "===================" << endl;
	delete[] result; // Memory Save
	return 0;
}

bool Dijkstra(Graph* graph, int vertex, ostream* os)
{
	vector<int> length(graph->getSize(), MAX);
	vector<int> parent(graph->getSize(), -1);
	vector<int> visited(graph->getSize(), false);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.push({ 0, vertex });
	length[vertex] = 0;

	while (!pq.empty()) {
		// Get Now Node and Pop
		int cost = pq.top().first;
		int now = pq.top().second;
		pq.pop();

		map<int, int> adj;
		graph->getAdjacentEdges(now, &adj);
		for (auto iter = adj.begin(); iter != adj.end(); iter++) {
			if (visited[iter->first]) continue;
			int total = cost + iter->second;
			if (total < length[iter->first]) {
				length[iter->first] = total;
				parent[iter->first] = now;
				pq.push({ total, iter->first });
			}
		}

		visited[now] = true;
	}

	*os << "===== DIJKSTRA =====" << endl;
	*os << "startvertex: " << vertex << endl;
	for (int i = 0; i < graph->getSize(); i++) {
		if (i == vertex) continue;
		*os << "[" << i << "] ";
		if (length[i] == MAX) {
			*os << "x" << endl;
		}
		else {
			// Path Find : end -> parent -> ... -> parent(vertex) and reverse this
			stack<int> path;
			int now = i;
			while (now != vertex) {
				path.push(now);
				now = parent[now];
			}
			int temp;
			while (true) {
				*os << path.top();
				path.pop();
				if (path.empty()) break;
				*os << " -> ";
			}
			*os << " (" << length[i] << ")" << endl;
		}
	}
	*os << "====================" << endl;

	// Memory Save
	return 0;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex, ostream* os)
{
	int n = graph->getSize();
	vector<int> length(n, MAX);
	vector<int> parent(n, -1);

	length[s_vertex] = 0;

	vector<Edge> v;
	graph->getAllEdges(&v);

	for (int k = 1; k < n; k++) { // Check All Edges N-1 times
		for (auto iter = v.begin(); iter != v.end(); iter++) {
			int from = iter->from; // Cur Vertex
			int to = iter->to;
			int cost = iter->weight;
			if (length[from] != MAX && length[to] > length[from] + cost) {
				length[to] = length[from] + cost;
				parent[to] = from;
			}
		}
	}

	// Check 1 more time to Search Negative Cycle
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		int from = iter->from; // Cur Vertex
		int to = iter->to;
		int cost = iter->weight;
		if (length[from] != MAX && length[to] > length[from] + cost) {
			// If Negative Cycle does not exist -> Already Shortest
			// -> This Condition can't meet
			return 1; // NEGATIVE CYCLE!!
		}
	}

	*os << "===== BELLMAN-FORD =====" << endl;
	if (length[e_vertex] == MAX) {
		*os << "x" << endl;
	}
	else {
		// Path Find : end -> parent -> ... -> parent(start) and reverse this
		stack<int> path;
		int now = e_vertex;
		while (true) {
			path.push(now);
			if (now == s_vertex) break;
			now = parent[now];
		}
		int temp;
		while (true) {
			*os << path.top();
			path.pop();
			if (path.empty()) break;
			*os << " -> ";
		}
		*os << endl;
		*os << "cost: " << length[e_vertex] << endl;
	}
	*os << "========================" << endl;

	return 0;
}

bool FLOYD(Graph* graph, ostream* os)
{
	int n = graph->getSize();
	// FLOYD
	vector<vector<int>> length(n, vector<int>(n, MAX));
	for (int j = 0; j < n; j++) {
		length[j][j] = 0;
	}

	vector<Edge> v;
	graph->getAllEdges(&v);

	for (int k = 1; k < n; k++) { // Check All Edges N-1 times
		for (auto iter = v.begin(); iter != v.end(); iter++) {
			int from = iter->from; // Cur Vertex
			int to = iter->to;
			int cost = iter->weight;
			for (int i = 0; i < n; i++) { // Bellman-ford for all vertex
				if (length[i][from] != MAX && length[i][to] > length[i][from] + cost) {
					length[i][to] = length[i][from] + cost;
				}
			}
		}
	}

	// Check 1 more time to Search Negative Cycle
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		int from = iter->from; // Cur Vertex
		int to = iter->to;
		int cost = iter->weight;
		for (int i = 0; i < n; i++) {
			if (length[i][from] != MAX && length[i][to] > length[i][from] + cost) {
				// If Negative Cycle does not exist -> Already Shortest
				// -> This Condition can't meet
				return 1; // NEGATIVE CYCLE!!
			}
		}
	}

	*os << "===== FLOYD =====" << endl;

	*os << '\t';
	for (int i = 0; i < n; i++)
	{
		*os << "[" << i << "]" << '\t';
	}
	*os << endl;

	for (int i = 0; i < n; i++)
	{
		*os << "[" << i << "]";
		for (int j = 0; j < n && *os << '\t'; j++)
		{
			if (length[i][j] == MAX) *os << 'x';
			else *os << length[i][j];
		}
		*os << endl;
	}
	*os << "================" << endl;

	return 0;
}