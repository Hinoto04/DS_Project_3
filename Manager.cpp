#include "Manager.h"
using namespace std;

vector<string> split(string& str, const string& deli) { //String Split Function to Recognition of Commmand
	vector<string> cuts;
	size_t pos = 0;
	string cut;
	while ((pos = str.find(deli)) != string::npos) {
		cut = str.substr(0, pos);
		cuts.push_back(cut);
		str.erase(0, pos + deli.length());
	}
	cuts.push_back(str);

	if (cuts[cuts.size() - 1].length() == 0) {
		cuts.pop_back();
	}

	return cuts;
}

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load)
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
		
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}

	string buf;

	/*
	All Function returns existance of error
	return 1; or return true; means "expected runtime error"
	*/
	while (getline(fin, buf))
	{
		int result = 0;
		vector<string> cuts;
		cuts = split(buf, "\t");
		if (cuts[0] == "LOAD") {
			if (cuts.size() != 2) result = 100;
			else {
				char temp[128];
				strcpy(temp, cuts[1].c_str());
				result = 100 * LOAD(temp);
			}
		}
		else if (cuts[0] == "PRINT") result = 200 * PRINT();
		else if (cuts[0] == "BFS") {
			if (cuts.size() != 2) result = 300;
			else result = 300 * mBFS(stoi(cuts[1]));
		}
		else if (cuts[0] == "DFS") {
			if (cuts.size() != 2) result = 400;
			else result = 400 * mDFS(stoi(cuts[1]));
		}
		else if (cuts[0] == "DFS_R") {
			if (cuts.size() != 2) result = 500;
			else result = 500 * mDFS_R(stoi(cuts[1]));
		}
		else if (cuts[0] == "KRUSKAL") result = 600 * mKRUSKAL();
		else if (cuts[0] == "DIJKSTRA") {
			if (cuts.size() != 2) result = 700;
			else result = 700 * mDIJKSTRA(stoi(cuts[1]));
		}
		else if (cuts[0] == "BELLMANFORD") {
			if (cuts.size() != 3) result = 800;
			else result = 800 * mBELLMANFORD(stoi(cuts[1]), stoi(cuts[2]));
		}
		else if (cuts[0] == "FLOYD") result = 900 * mFLOYD();
		else if (cuts[0] == "EXIT") {
			fout << "===== EXIT =====" << endl;
			fout << "Success" << endl;
			fout << "================" << endl;
			fout.close();
			exit(0);
		}
		// print errorcode when error exist
		if (result) printErrorCode(result);
	}
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	ifstream loadfs;
	loadfs.open(filename);
	if (!loadfs) return 1;
	if (loadfs.eof()) return 1;
	string buf;
	loadfs >> buf;
	if(loadfs.eof()) return 1;
	if (buf == "L") { // List Mode
		int num;
		loadfs >> num;
		this->graph = new ListGraph(0, num);
		
		int from = 0;
		while (!loadfs.eof()) {
			getline(loadfs, buf, '\n');
			cout << "buf: " << buf << endl;
			vector<string> cuts;
			cuts = split(buf, " ");
			for (int i = 0; i < cuts.size(); i++) {
				cout << "cuts[" << i << "]: " << cuts[i] << endl;
			}
			if (cuts.size() == 2) { // if two integer given -> to weight
				graph->insertEdge(from, stoi(cuts[0]), stoi(cuts[1]));
			}
			else if(cuts.size() == 1) { // if one integer given -> from
				from = stoi(cuts[0]);
			}
		}
	}
	else { // Matrix Mode
		int num;
		loadfs >> num;
		this->graph = new MatrixGraph(1, num);

		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				int w;
				loadfs >> w;
				this->graph->insertEdge(i, j, w);
			}
		}
	}
	fout << "===== LOAD =====" << endl << "Success" << endl << "================" << endl;
	return 0;
}

bool Manager::PRINT()
{
	if (graph == nullptr) return 1;
	graph->printLog(&fout);
	return graph->printGraph();
}

bool Manager::mBFS(int vertex)
{
	if (graph->getSize() < vertex) return 1; // vertex does not exist
	return BFS(graph, vertex, &fout);
}

bool Manager::mDFS(int vertex)
{
	if (graph->getSize() < vertex) return 1; // vertex does not exist
	return DFS(graph, vertex, &fout);
}


bool Manager::mDFS_R(int vertex)
{
	fout << "===== DFS_R =====" << endl;
	fout << "startVertex: " << vertex << endl;
	if (graph->getSize() < vertex) return 1; // vertex does not exist
	vector<bool> visit(graph->getSize(), false); // Visited Vector
	int result = DFS_R(graph, &visit, vertex, &fout);
	fout << endl << "=================" << endl;
	return result;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if (graph->getSize() < vertex) return 1; // vertex does not exist
	vector<Edge> v;
	graph->getAllEdges(&v);
	for (auto iter = v.begin(); iter != v.end(); iter++) {
		if (iter->weight < 0) { // Negative Weight Check
			return 1;
		}
	}

	return Dijkstra(graph, vertex, &fout);
}

bool Manager::mKRUSKAL()
{
	if (graph->getSize() == 0) return 1;
	return Kruskal(graph, &fout);
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if (graph->getSize() < s_vertex || graph->getSize() < e_vertex) return 1; // vertex does not exist
	return Bellmanford(graph, s_vertex, e_vertex, &fout);
}

bool Manager::mFLOYD()
{
	return FLOYD(graph, &fout);
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
