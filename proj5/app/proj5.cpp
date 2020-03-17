#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include <iostream>

// As a reminder, for this project, edges have positive cost, g[i][j] = 0 means no edge.
std::vector<Edge> compute_mst(std::vector< std::vector<unsigned>> & graph)
{

	std::vector<Edge> mst;

	// node of edge and bunch of operators
	struct Node {
		Edge edge;
		Node(unsigned u = 0, unsigned v = 0, unsigned wt = 0) : edge(u,v,wt) {}

		bool operator<(const Node & n) const{
			return edge.weight < n.edge.weight;
		}

		bool operator==(const Node & n){
			return edge == n.edge;
		}

		bool operator>(const Node & n) const {
			return edge.weight > n.edge.weight;
		}

		bool operator>=(const Node & n) const{
			return edge.weight >= n.edge.weight;
		}

		bool operator<=(const Node & n) const{
			return edge.weight <= n.edge.weight;
		}
	};

	MyPriorityQueue<Node> mpq;
	MyPriorityQueue<Node> tmpq;
	const unsigned totalNodes = graph[0].size();
	unsigned i = 0;

	// initialize
	for (unsigned j = 0; j < totalNodes; ++j) {
		if (i != j) { // i = j means no edge
			Node n(i, j, graph[i][j]);
			mpq.insert(n);
		}
	}

	Node minNode = mpq.min(); // object of index 1
	mst.push_back(minNode.edge); // commit to mst
	mpq.extractMin();		// remove from mpq
	i = minNode.edge.pt2;		// min's index

	// find mst
	while (!mpq.isEmpty()) {
		MyPriorityQueue<Node> tmpq;
		unsigned mpqSize = mpq.size();
		for (unsigned j = 0; j < mpqSize; ++j) {
			minNode = mpq.min(); // min node edge
			Node n(i, minNode.edge.pt2, graph[i][minNode.edge.pt2]); // graph node edge that links with min node edge
			mpq.extractMin();
			// check n with minNode from mpq then add to a new temp mpq
			// everything in mpq are still paths to be checked and commited
			if (minNode <= n) { 
				tmpq.insert(minNode);
			} else {
				tmpq.insert(n);
			}
		}
		mpq = tmpq; // set original equal to temp

		Node minNode = mpq.min(); // object of index 1
		mst.push_back(minNode.edge); // commit to mst
		mpq.extractMin();		// remove from mpq
		i = minNode.edge.pt2;		// min's index
	}
	return mst;
}


// Returns the cost of the edges in the given vector,
// This does not confirm that it is a MST at all.  
unsigned mstCost(const std::vector<Edge> & vE) 
{
	unsigned sum =0;
	for(auto e: vE)
	{
		sum += e.weight;
	}
	return sum;
}
