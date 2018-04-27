#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

#include "graph.h"

using namespace std;

pthread_mutex_t mutexLock;
int totalThreads;
bool found = false;
stringstream finalAns;

template <class T>
struct BFSParameters
{
	Graph<T>* graph;
	int initialNode;
	int queueNumber;
	vector<bool>* visited;
	vector< queue< Node<T> > >* bfsQueues;
	string* query;
	
	BFSParameters(Graph<T>* graph, const int& initialNode, const int& queueNumber, vector<bool>* visited, vector< queue< Node<T> > >* bfsQueues, string* query)
	{
		this -> graph = graph;
		this -> initialNode = initialNode;
		this -> queueNumber = queueNumber;
		this -> visited = visited;
		this -> bfsQueues = bfsQueues;
		this -> query = query;
	}
};

void bfsSerial(const Graph<string>& g, const int& source, const string& query)
{
	vector<bool> visited(g.getNumberOfNodes(), false);
	queue< Node<string> > q;
	
	q.push(g.getNode(source));
	visited[source] = true;
	
	while (!q.empty())
	{
		Node<string> current = q.front();
		q.pop();
		
		if (current.getData() == query)
		{
			cout << "Data found at Node: " << current.getNodeID() << endl;
			break;
		}
		
		vector<Edge> outboundEdges = current.getOutboundEdges();
		
		for (int i = 0; i < outboundEdges.size(); ++i)
		{
			if (!visited[outboundEdges[i].getDestID()])
			{
				q.push(g.getNode(outboundEdges[i].getDestID()));
				visited[outboundEdges[i].getDestID()] = true;
			}
		}
	}
}

void* bfs(void* params)
{
	BFSParameters<string> parameters = *((BFSParameters<string>*)params);
	
	queue< Node<string> >& toVisit = ((*(parameters.bfsQueues))[parameters.queueNumber]);
	
	pthread_mutex_lock(&mutexLock);
	
	if (!(*(parameters.visited))[parameters.initialNode])
	{
		toVisit.push(parameters.graph -> getNode(parameters.initialNode));
		(*(parameters.visited))[parameters.initialNode] = true;
	}
	
	pthread_mutex_unlock(&mutexLock);
	
	bool done = false;
	
	while (!done)
	{
		if (found) pthread_exit((void*)NULL);
		
		pthread_mutex_lock(&mutexLock);
		while (!toVisit.empty())
		{
			if (found) pthread_exit((void*)NULL);
			
			Node<string> current = toVisit.front();
			toVisit.pop();
			
			if (current.getData() == (*(parameters.query)))
			{
				finalAns << "Found the required Data at Node: " << current.getNodeID() << endl;
				
				found = true;
				pthread_mutex_unlock(&mutexLock);
				
				pthread_exit((void*)NULL);
			}
			
			vector<Edge> outboundEdges = current.getOutboundEdges();
			
			for (int i = 0; i < outboundEdges.size(); ++i)
			{
				if (!((*(parameters.visited))[outboundEdges[i].getDestID()]))
				{
					(*(parameters.visited))[outboundEdges[i].getDestID()] = true;
					toVisit.push(parameters.graph -> getNode(outboundEdges[i].getDestID()));
				}
			}
		}
		
		pthread_mutex_lock(&mutexLock);
		
		done = true;
		
		for (int i = 0; i < totalThreads; ++i)
		{
			done |= (!(*(parameters.bfsQueues))[i].empty());
		}
		
		if (!done)
		{
			for (int i = 0; i < totalThreads; ++i)
			{
				if ((*(parameters.bfsQueues))[i].size() > 1)
				{
					toVisit.push((*(parameters.bfsQueues))[i].front());
					(*(parameters.bfsQueues))[i].pop();
					break;
				}
			}
		}
		
		pthread_mutex_unlock(&mutexLock);
	}
}

int main()
{
	Graph<string> graph;
	
	// ifstream graphInput("graphInput.txt");
	ifstream graphInput("generated.txt");
	
	int nodeCount, edgeCount;
	graphInput >> nodeCount >> edgeCount;
	
	for (int i = 0; i < nodeCount; ++i)
	{
		string nodeData;
		graphInput >> nodeData;
		
		graph.addNode(nodeData);
	}
	
	for (int i = 0; i < edgeCount; ++i)
	{
		int src, dest, wght;
		
		graphInput >> src >> dest >> wght;
		
		graph.addEdge(src, dest, wght);
	}
	
	cout << "Enter the number of threads allowed: ";
	graphInput >> totalThreads;
	cout << totalThreads << endl;
	
	if (totalThreads > nodeCount)
	{
		cout << "Number of allowed threads must be less than or equal to nodeCount." << endl;
		exit(EXIT_FAILURE);
	}
	
	if (totalThreads < 1)
	{
		cout << "Number of allowed threads must be non-negative and non-zero." << endl;
		exit(EXIT_FAILURE);
	}
	
	int initialNode;
	cout << "Enter the node ID to start the BFS at: ";
	graphInput >> initialNode;
	cout << initialNode << endl;
	
	string query;
	cout << "Enter the data to search for: ";
	graphInput >> query;
	
	cout << query << endl;
	
	pthread_mutex_init(&mutexLock, NULL);
	
	vector<bool> visited(graph.getNumberOfNodes(), false);
	vector< queue< Node<string> > > bfsQueues(totalThreads);
	vector<pthread_t> threads(totalThreads);
	BFSParameters<string> params(&graph, initialNode, 0, &visited, &bfsQueues, &query);
	
	// start time here.
	
	for (int i = 0; i < totalThreads; ++i)
	{
		params.queueNumber = i;
		pthread_create(&threads[i], NULL, bfs, (void*)&params);
	}
	
	for (int i = 0; i < totalThreads; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	
	// end time here.
	
	// bfsSerial(graph, initialNode, query);
	
	pthread_mutex_destroy(&mutexLock);
	
	if (found)
	{
		cout << finalAns.str() << endl;
	}
	
	else
	{
		cout << "No Node found with data equal to query." << endl;
	}
	
	return 0;
}