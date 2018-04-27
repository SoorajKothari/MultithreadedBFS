#ifndef EDGE_H
#define EDGE_H

class Edge
{
private:
	int destID;
	int weight;
	
public:
	Edge(); // Creates Edge with 0 destID and weight
	Edge(const int& destID, const int& weight); // Creates Edge with specified destID and weight
	
	int getDestID(); // Returns the destination ID of the edge
	int getWeight(); // Returns the weight of the edge
};

Edge::Edge()
{
	this -> destID = 0;
	this -> weight = 0;
}

Edge::Edge(const int& destID, const int& weight)
{
	this -> destID = destID;
	this -> weight = weight;
}

int Edge::getDestID()
{
	return this -> destID;
}

int Edge::getWeight()
{
	return this -> weight;
}

#endif // EDGE_H