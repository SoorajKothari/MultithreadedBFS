#ifndef NODE_H
#define NODE_H

#include <vector>

#include "edge.h"

template <class DataType>
class Node
{
private:
	int nodeID; // ID of the Node
	DataType data; // Data to store at Node
	std::vector<Edge> edges; // Outbound Edges
	
public:
	Node(); // Creates Node with empty data and empty edges with -1 nodeID
	Node(const int& nodeID, const DataType& data); // Creates Node with specified data and empty edges
	Node(const int& nodeID, const DataType& data, const std::vector<Edge>& edges); // Creates Node with specified data and edges
	Node& addOutboundEdge(const int& destID, const int& weight); // Adds an edge with specified parameters
	int getNodeID(); // Returns the ID of the node
	DataType getData(); // Returns the data associated with the Node
	std::vector<Edge> getOutboundEdges(); // Returns the Edges going out of the Node
};

template <class DataType>
Node<DataType>::Node()
{
	this -> nodeID = -1;
}

template <class DataType>
Node<DataType>::Node(const int& nodeID, const DataType& data)
{
	this -> nodeID = nodeID;
	this -> data = data;
}

template <class DataType>
Node<DataType>::Node(const int& nodeID, const DataType& data, const std::vector<Edge>& edges)
{
	this -> nodeID = nodeID;
	this -> data = data;
	this -> edges = edges;
}

template <class DataType>
int Node<DataType>::getNodeID()
{
	return this -> nodeID;
}

template <class DataType>
DataType Node<DataType>::getData()
{
	return this -> data;
}

template <class DataType>
std::vector<Edge> Node<DataType>::getOutboundEdges()
{
	return this -> edges;
}

template <class DataType>
Node<DataType>& Node<DataType>::addOutboundEdge(const int& destID, const int& weight)
{
	edges.push_back(Edge(destID, weight));
	
	return (*this);
}

#endif // NODE_H