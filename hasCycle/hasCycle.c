
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

// This cycle check algorithm simply uses the visited array to check if their is a cycle by checking is an adjacent vertex is not the prev vertex it came from, then
// the graph has a cycle.

static bool doHasCycle(Graph g, int v, int prev, bool *visited);

bool hasCycle(Graph g) {
	// TODO

	bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

	for (int v = 0; v < GraphNumVertices(g); v++) {
		if (!visited[v]) {
			if (doHasCycle(g, v, v, visited)) {
				free(visited);
				return true;
			}
		}
	}

	free(visited);

	return false;
}


static bool doHasCycle(Graph g, int v, int prev, bool *visited) {	

	visited[v] = true;
	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (GraphIsAdjacent(g ,v, w)) {
			if (visited[w]) {
				if (w != prev) {
					return true;
				}
			} else {
				if (doHasCycle(g, w, v, visited)) {
					return true;
				}
			}
		}
	}
	return false;

}

