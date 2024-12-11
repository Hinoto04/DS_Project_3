#pragma once

class Edge {
public:
	int from;
	int to;
	int weight;

	Edge(int from, int to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}
	~Edge() { ; }

	bool operator>(Edge& e) {
		return this->weight > e.weight;
	}
	bool operator==(Edge& e) {
		return this->weight == e.weight;
	}
	bool operator<(Edge& e) {
		return this->weight < e.weight;
	}
};