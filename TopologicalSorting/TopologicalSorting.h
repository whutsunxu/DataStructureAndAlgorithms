#pragma once
/* use adjacency list for directed acylic graph sort
   reference: Chapter 9.2
   https://songlee24.github.io/2015/05/07/topological-sorting/
   */
#include <list>
#include <queue>

class graph
{
private:
	int Vtx; // number of vertex
	std::list<int>* adj; // adjacent list for every vertex
	std::queue<int> que; // the queue for vetex with zero indegree
	int* indegree;  // the indegree for every vertex

public:
	graph(int v);
	~graph();
	void addEdge(int v, int w); // add an edge(v, w)
	bool topoSort();
};