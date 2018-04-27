#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include "edge.h"
#include "node.h"

template <class NodeDataType>
class Graph
{
private:
	std::vector< Node<NodeDataType> > nodes;
	
public:
	Graph(); // Creates an empty Graph
	Graph(const std::vector< Node<NodeDataType> >& nodes); // Creates a graph using the specified list of Nodes
	
	Graph& addNode(const Node<NodeDataType>& node); // Adds a Node Object to the Graph and assigns it the next available NodeID
	Graph& addNode(const NodeDataType& data); // Adds a Node with specified data and assigns it the next available NodeID
	
	Graph& addEdge(const int& sourceID, const Edge& edge); // Adds an Edge Object to the Graph at the node specified by sourceID
	Graph& addEdge(const int& sourceID, const int& destID, const int& w); // Adds an Edge from source node to dest node with 'w' weight
	
	Node<NodeDataType> getNode(const int& nodeID) const; // Returns the specified Node from the Node List
	int getNumberOfNodes() const; // Returns the number of nodes in the graph
};

template <class NodeDataType>
Graph<NodeDataType>::Graph() { }

template <class NodeDataType>
Graph<NodeDataType>::Graph(const std::vector< Node<NodeDataType> >& nodes)
{
	this -> nodes = nodes;
}

template <class NodeDataType>
Graph<NodeDataType>& Graph<NodeDataType>::addNode(const Node<NodeDataType>& node)
{
	nodes.push_back(node);
	
	return (*this);
}

template <class NodeDataType>
Graph<NodeDataType>& Graph<NodeDataType>::addNode(const NodeDataType& data)
{
	nodes.push_back(Node<NodeDataType>(nodes.size(), data));
	
	return (*this);
}

template <class NodeDataType>
Graph<NodeDataType>& Graph<NodeDataType>::addEdge(const int& sourceID, const Edge& edge)
{
	if (sourceID >= nodes.size())
	{
		std::cout << "ERROR: Specified sourceID is not in the Graph." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	nodes[sourceID].edges.push_back(edge);
	
	return (*this);
}

template <class NodeDataType>
Graph<NodeDataType>& Graph<NodeDataType>::addEdge(const int& sourceID, const int& destID, const int& w)
{
	if (sourceID >= nodes.size())
	{
		std::cout << "ERROR: Specified sourceID is not in the Graph." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	nodes[sourceID].addOutboundEdge(destID, w);
	
	return (*this);
}

template <class NodeDataType>
Node<NodeDataType> Graph<NodeDataType>::getNode(const int& nodeID) const
{
	if (nodeID >= nodes.size())
	{
		std::cout << "ERROR: Specified nodeID is not in the Graph." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	return nodes[nodeID];
}

template <class NodeDataType>
int Graph<NodeDataType>::getNumberOfNodes() const
{
	return nodes.size();
}

#endif // GRAPH_H