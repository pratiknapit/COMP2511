
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX_NODES 1000

int visited[MAX_NODES]; //array to store visited nodes

void depthFirstSearch(Graph g, Vertex src) {
	// TODO
	int n = GraphNumVertices(g);

	visited[src] = 1;

	Vertex w;
	for (w = 0; w <= n; w++) 
		if (GraphIsAdjacent(g, src, w) && !visited[w]) {
			printf("%d ", w); 
			depthFirstSearch(g, w); 
		}
	
}



