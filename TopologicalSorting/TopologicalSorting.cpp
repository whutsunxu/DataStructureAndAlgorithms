#include "TopologicalSorting.h"
#include <iostream>

graph::graph(int v)
{
	Vtx = v;
	indegree = new int[Vtx];
	for (int i = 0; i < Vtx; i++)
		indegree[i] = 0;
	adj = new std::list<int>[Vtx];
}

graph::~graph()
{
	delete[] indegree;
	delete[] adj;
}

void graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	indegree[w]++;
}
bool graph::topoSort()
{
	// enqueue those vertex with zero indegree
	for (int i = 0; i < Vtx; i++)
		if (indegree[i] == 0)
			que.push(i);
	//remove the vertex with  zero indegree and related indegree
	int count = 0;
	while (!que.empty())
	{
		int v = que.front();
		que.pop();
		count++;

		std::cout << v << "\t";

		std::list<int>::iterator bg = adj[v].begin();
		for (; bg != adj[v].end(); bg++)
		{
			if (!(--indegree[*bg]))
				que.push(*bg);
		}
	}
	if (count < Vtx)
	{
		std::cout << "There is a cyclic in the graph.\n";
		return false;
	}
	else
		return true;
}