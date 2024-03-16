
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static void dfsComponentOf(Graph g, int v, int compID, int *componentOf);

int numReachable(Graph g, int src) {
	
	int *componentOf = calloc(GraphNumVertices(g), sizeof(int)); 


	for (int i = 0; i < GraphNumVertices(g); i++) {
		componentOf[i] = -1;
	}

	int compID = 0;
	for (int v = 0; v < GraphNumVertices(g); v++) {
		if (componentOf[v] == -1) {
			dfsComponentOf(g, v, compID, componentOf);
			compID += 1;
		}
	}

	int comp = componentOf[src];
	int pay = 0;
	for (int i = 0; i < GraphNumVertices(g); i++) {
		if (componentOf[i] == comp) {
			pay++;
		}
	}

	free(componentOf);
	return pay;
}

static void dfsComponentOf(Graph g, int v, int compID, int *componentOf) {
	componentOf[v] = compID;
	for (int w = 0; w < GraphNumVertices(g); w++) {
		if (GraphIsAdjacent(g, v, w) && componentOf[w] == -1) {
			dfsComponentOf(g, w, compID, componentOf); 
		}
	}
	return;
}


