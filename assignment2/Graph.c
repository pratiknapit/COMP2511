// Implementation of the Directed Weighted Graph ADT
// Uses an adjacency matrix - This file has been taken from the labs and adapted for the project.

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "list.h"

struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    bool **edges; // adjacency matrix storing bool
                    // 0 if nodes not adjacent
    /*
    double *outlinks; 
    double *inlinks; 
    */
};

static bool doHasCycle(Graph g, Vertex v, Vertex prev, bool *visited);
static int  validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(bool *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(bool));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    /*
    for (int c = 0; c < nV; c++) {
        g->inlinks = calloc(nV, sizeof(double)); 
        g->outlinks = calloc(nV, sizeof(double)); 
    }
    */

    return g;
}

void graph_free(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}


bool GraphInsertEdge(Graph g, Edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    //assert(e.v != e.w);
    //assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == false) {
        g->edges[e.v][e.w] = true;
        //g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != false) {   // edge e in graph
        g->edges[v][w] = false;
        //g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}


bool GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}


void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = 0; w < g->nV; w++) {
            if (g->edges[v][w] != false) {
                printf("Edge %d - %d: %d\n", v, w, g->edges[v][w]);
            }
        }
    }
}

bool GraphHasCycle(Graph g) {
    bool *visited = calloc(g->nV, sizeof(bool));
    assert(visited != NULL); // lazy error checking
    
    for (int v = 0; v < g->nV; v++) {
        if (!visited[v] && doHasCycle(g, v, v, visited)) {
            free(visited);
            return true;
        }
    }

    free(visited);
    return false;
}

static bool doHasCycle(Graph g, Vertex v, Vertex prev, bool *visited) {
    visited[v] = true;
    for (int w = 0; w < g->nV; w++) {
        if (g->edges[v][w] != false) {
            if (!visited[w]) {
                if (doHasCycle(g, w, v, visited)) {
                    return true;
                }
            } else if (w != prev) {
                return true;
            }
        }
    }
    return false;
}

// Calculate Win.
double in_links(Graph g, Vertex v, Vertex w) {

    return links_into_vertex(g, w) / total_reference_in_links(g, v);
}

// Get the total inlinks of our current page.
double links_into_vertex(Graph g, Vertex v) {
    double total = 0;
    int N = GraphNumVertices(g);
    for (int i = 0; i < N; i++) {
        // If there is a link from vertice i to vertice v, increment inlink total.
        // v != i eliminates the possibility of counting loops.
        if (GraphIsAdjacent(g, i, v) == true && v != i) {
            total++;
        }
    }
    return total;
}

// Find the sum of all the pages inlinking to v.
double total_reference_in_links(Graph g, Vertex v) {
    double total = 0;
    int N = GraphNumVertices(g);
    for (int j = 0; j < N; j++) {
        // If there is a link curr page's child to i, calculate the total inlinks for all reference pages.
        // v != i eliminates the possibility of counting loops.
        if (GraphIsAdjacent(g, v, j) == true && v != j) {
            total += links_into_vertex(g, j);
        }
    }
    return total;
}



// Calulate Wout.
double out_links(Graph g, Vertex v, Vertex w) {
    // outlinks = total outlinks of curr page / sum of outlinks of reference pages.
    return links_out_of_url(g, w) / total_reference_out_links(g, v);
}

double links_out_of_url(Graph g, Vertex v) {
    double total = 0;
    int N = GraphNumVertices(g);
    for (int i = 0; i < N; i++) {
        // If there is a link from vertice i to vertice v, increment inlink total.
        // v != i eliminates the possibility of counting loops.
        if (GraphIsAdjacent(g, v, i) == true && v != i) {
            total++;
        }
    }

    // We redefine total if necessary to prevent division by zero errors.
    if (total == 0) {
        total = 0.5;
    }
    return total;
}

int *get_outlinks(int n, Graph g) {

    int *out_links = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        out_links[i] = (int)links_out_of_url(g, i);
    }

    return out_links;

}

// Find the sum of all the pages which v links to.
double total_reference_out_links(Graph g, Vertex v) {
    double total = 0;
    int N = GraphNumVertices(g);
    for (int i = 0; i < N; i++) {
        // If there is a link curr page's child to i, calculate the total Outlinks for all reference pages.
        // v != i eliminates the possibility of counting loops.
        if (GraphIsAdjacent(g, v, i) == true && v != i) {
            total += links_out_of_url(g, i);
        }
    }
    return total;
}



////////////////////////////////////////////////////////////////////////
// Your task

/*
static PQ makePQ(Graph g);

Graph GraphMST(Graph g) {
    // TODO: Complete this function
    Graph mst = GraphNew(g->nV); 
    PQ pq = makePQ(g); 

    while (mst->nE < g->nV - 1 && !PQIsEmpty(pq)) {
        Edge e = PQExtract(pq); 
        GraphInsertEdge(mst, e); 
        if (GraphHasCycle(mst)) {
            GraphRemoveEdge(mst, e.v, e.w); 
        }
    }

    PQFree(pq); 
    if (mst->nE == g->nV - 1) {
        return mst; 
    } else {
        GraphFree(mst); 
        return NULL; 
    }

}

static PQ makePQ(Graph g) {
    PQ pq = PQNew(); 

    for (int i = 0; i < g->nV; i++) {
        for (int j = i; j < g->nV; j++) {
            if (g->edges[i][j] != false) {
                PQInsert(pq, (Edge){i, j, g->edges[i][j]}); 
            }
        }
    }

    return pq; 
}
*/
////////////////////////////////////////////////////////////////////////

static int validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}
