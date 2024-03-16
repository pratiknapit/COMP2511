
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define MAX_NODES 1000

int visited[MAX_NODES]; // array to store the visited nodes

void breadthFirstSearch(Graph g, int src) {
	// TODO

	int nV = GraphNumVertices(g);

	Vertex v;

	for (v = 0; v < nV; v++) {
		visited[v] = -1;
	}

	visited[src] = src;
	Queue Q = QueueNew();
	QueueEnqueue(Q, src); 

	while (!QueueIsEmpty(Q)) {

		v = QueueDequeue(Q); 

		printf("%d ", v); 

		Vertex w;
		for (w = 0; w < nV; w++) {

			if (GraphIsAdjacent(g, v, w) && visited[w] == -1) {
				visited[w] = v;
				QueueEnqueue(Q, w);
			}

		}

	} 

	//need to free the Queue 
	QueueFree(Q);


}

