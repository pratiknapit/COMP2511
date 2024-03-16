
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

double outDegree(Graph g, int nV, int src);
void findPopularFollowers(Graph g, int src, int followers[]);
double inDegree(Graph g, int nV, int src);
int DFS(Graph g, int v, int dest);
int hasPath(Graph g, Vertex src, Vertex dest);

// Worst case time complexity of this solution: O(n^2)
void findPopularFollowers(Graph g, int src, int followers[]) {
	// TODO

	for (int i = 0; i < g->nV; i++) {
		if (hasPath(g, i, src) || i == src) {
			if (inDegree(g, g->nV, i) > outDegree(g, g->nV, i)) {
				followers[i] = 1;
			}
		}
	}

}

int *visited;

int hasPath(Graph g, Vertex src, Vertex dest) {
  // first check if src and dest are connected by an edge
  if (GraphIsAdjacent(g, src, dest)) {
    return 1;
  }

  // sets all in visited to 0
  visited = calloc(g->nV, sizeof(int));

  // perform depth first search
  int exists = DFS(g, src, dest);

  free(visited);

  return exists;
}

int DFS(Graph g, int v, int dest) {
  // set the vertex to visited
  visited[v] = 1;

  // for each vertex in the graph
  for (int w = 0; w < g->nV; w++) {
    // if the given vertex (v) is adjacent to the current vertex (w)
    // and it hasn't been visited
    if (GraphIsAdjacent(g, v, w) && visited[w] == 0) {
      // set it to visited
      visited[w] = 1;

      // if w is the dest, return true
      if (w == dest) {
        return 1;
      } else if (DFS(g, w, dest)) {
        return 1;
      }
    }
  }
  return 0;
}


double inDegree(Graph g, int nV, int src) {
    int count = 0;
    for (int i = 0; i < nV; i++) {
        if (GraphIsAdjacent(g, i, src)) {
            count++;
        }
    }
    return count;
}

double outDegree(Graph g, int nV, int src) {
    int count = 0;
    for (int i = 0; i < nV; i++) {
        if (GraphIsAdjacent(g, src, i)) {
            count++;
        }
    }
    
    return count;
}

