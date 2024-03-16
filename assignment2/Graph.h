// Interface to the Undirected Weighted Graph ADT
// - Vertices are identified by integers between 0 and nV - 1,
//   where nV is the number of vertices in the graph
// - Weights are doubles and must be positive
// - Self-loops are not allowed

// This file has been take from the labs and adapted as required.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include "list.h"

typedef struct graph *Graph;

typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
    //double weight;
} Edge;

/**
 * Creates a new instance of a graph
 */
Graph  GraphNew(int nV);

/**
 * Frees all memory associated with the given graph
 */
void   graph_free(Graph g);

/**
 * Returns the number of vertices in the graph
 */
int    GraphNumVertices(Graph g);

/**
 * Inserts  an  edge into a graph. Does nothing if there is already an
 * edge between `e.v` and `e.w`. Returns true if successful, and false
 * if there was already an edge.
  */
bool   GraphInsertEdge(Graph g, Edge e);

/**
 * Removes an edge from a graph. Returns true if successful, and false
 * if the edge did not exist.
 */
bool   GraphRemoveEdge(Graph g, Vertex v, Vertex w);

/**
 * Returns the weight of the edge between `v` and `w` if it exists, or
 * 0.0 otherwise
 */
bool GraphIsAdjacent(Graph g, Vertex v, Vertex w);

/**
 * Returns true if the graph contains a cycle, and false otherwise
 */
bool   GraphHasCycle(Graph g);

/**
 * Gives use the links out of a vertex/url.
 */
double links_out_of_url(Graph g, Vertex v);

/**
 * Gives us the number of in links for a url. 
 */
double in_links(Graph g, Vertex v, Vertex w);

/**
 * Gives us the links to the vertex.
 */
double links_into_vertex(Graph g, Vertex v);

/**
 * Gives us all the reference in links to the vertex.
 */
double total_reference_in_links(Graph g, Vertex v);

/**
 * Returns all the outlinks from a vertex.
 */
double out_links(Graph g, Vertex v, Vertex w);

/**
 * Returns all the linsk out of a vertex/url.
 */
double links_out_of_url(Graph g, Vertex v);

/**
 * Returns all the reference pages total out of a link.
 */
double total_reference_out_links(Graph g, Vertex v);

/**
 * Returns all the outlinks in total and returns an array of outlinks back.
 */
int *get_outlinks(int n, Graph g);

/**
 * Returns a minimum spanning tree of the given graph. The given graph
 * should not be modified. Returns NULL if the graph has no minimum 
 * spanning tree.
 */
Graph  GraphMST(Graph g);

/**
 * Displays information about the graph
 */
void   GraphShow(Graph g);

#endif
