
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define MAX_NODES 1000

int visited[MAX_NODES];


int shortestDistance(Graph g, int src, int dest) {
	// TODO

	int nV = GraphNumVertices(g);

	Vertex v;

	for (v = 0; v < nV; v++) {
		visited[v] = -1;
	}

	//bool found = false; 

	visited[src] = src;
	Queue Q = QueueNew();
	QueueEnqueue(Q, src); 


	while (!QueueIsEmpty(Q)) { 

		v = QueueDequeue(Q); 

		//printf("%d \n", v); 

		if (v == dest) {
			//found = true;
			break;
		}

		Vertex w;
		for (w = 0; w < nV; w++) {

			if (GraphIsAdjacent(g, v, w) && visited[w] == -1) {
				visited[w] = v;
				QueueEnqueue(Q, w);
			}

		}

	}
	/*
	Vertex u;
	if (found == true) {
		v = dest;
		while (v != src) {
			u = visited[v];
			v = u;
			printf("%d ", v);
		}
	} 

	Vertex u;
	for (u = 0; u < nV; u++) {
		printf("\n %d", visited[u]);
	}
	*/

	Vertex u = dest;
	int i = 0;
	// need to check if the src and dest are part of the same graph component to 
	// pass the 4th test.
	while (u != src) {
		v = visited[u];
		i++; 
		u = v;
	}

	QueueFree(Q);
	
	return i;
}

