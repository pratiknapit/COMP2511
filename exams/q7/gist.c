// COMP2521 21T2 Sample Final Exam Q7
// Check graph property

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Constants

#define MAXVERTICES 20
#define MAXLINE 100

// Directed graph as adjacency matrix
// The matrix is *not* symmetric
typedef struct _graph_rep {
	int   nV; 
	bool  edge[MAXVERTICES][MAXVERTICES];
} DiGraph;

// Helper functions
void readGraph(FILE *, DiGraph *);
bool graphIsBinTree(DiGraph);
void showGraph(FILE *, DiGraph);


int main(int argc, char **argv)
{
	DiGraph g;  // graph struct
	FILE *in;   // input file handle

	// handle command-line arguments
	if (argc < 2) {
		fprintf(stderr,"Usage: %s GraphFile\n", argv[0]);
		exit(1);
	}
	if ((in = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't read %s\n", argv[1]);
		exit(1);
	}

	// main program
	readGraph(in, &g);
	showGraph(stdout, g);
	printf("\nGraph is ");
	if (!graphIsBinTree(g)) printf("not ");
	printf("a tree\n");
	
	// clean up
	return 0;
}

// Returns true if the given graph is a binary tree, and false otherwise
bool graphIsBinTree(DiGraph g)
{
	//use double for loop to put incoming edges in a incoming array - check incoming array

	int *incoming = calloc(g.nV, sizeof(int));
	int *outgoing = calloc(g.nV, sizeof(int));
	int i, j, w, a;
	for (i = 0; i < g.nV; i++) {
		for (j = 0; j < g.nV; j++) {
			if (g.edge[i][j]) {
				outgoing[i] = outgoing[i] + 1;
				incoming[j] = incoming[j] + 1;
			}
		}
	}

	// check the incoming node rules for a tree
	j = 0;
	w = 0;
	a = 0;
	for (i = 0; i < g.nV; i++) {
		if (incoming[i] == 0) {
			j++;
		} else if (incoming[i] == 1) {
			w++;
		} else {
			a++;
		}
	}
	
	if (j != 1 && w != g.nV-1 && a != 0) {
		return false;
	}

	// check the outgoing node rules for a tree
	for (i = 0; i < g.nV; i++) {
		if (outgoing[i] > 2) {
			return false;
	}

	free(incoming);
	free(outgoing);

	//check if something is a bin tree if there is no cycle - just need a cycle checker, rather than checking only one path exists.

	//if all tests have passed than we can say that this digraph is a tree.
	
	return true; 
}




// Read Graph from "in" file
// Read into DiGraph struct referenced by "g"
void readGraph(FILE *in, DiGraph *g)
{
	char *c, line[MAXLINE];
	int  n, v, nV;
	bool first;

	for (int v = 0; v < MAXVERTICES; v++) {
		for (int w = 0; w < MAXVERTICES; w++)
			g->edge[v][w] = false;
	}
	nV = 0;
	while (fgets(line, MAXLINE, in) != NULL) {
		c = line; first = true;
		while (*c != '\0') {
			// find next number in line
			while (*c != '\0' && !isdigit(*c)) c++;
			if (*c == '\0') break;
			sscanf(c,"%d", &n);
			if (first)
				{ v = n; first = false; }
			else
				g->edge[v][n] = true;
			// skip number we just scan'd
			while (*c != '\0' && isdigit(*c)) c++;
		}
		nV++;
	}
	g->nV = nV;
}

// Print graph info on output file "out"
void showGraph(FILE *out, DiGraph g)
{
	printf("V    Connected to\n");
	printf("--   ------------\n");
	int v, w;
	for (v = 0; v < g.nV; v++) {
		int nout = 0;
		printf("%-3d ",v);
		for (w = 0; w < g.nV; w++) {
			if (g.edge[v][w]) {
				printf(" %d",w);
				nout++;
			}
		}
		if (nout == 0) printf(" -");
		printf("\n");
	}
}
