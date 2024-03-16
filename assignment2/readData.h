// COMP2521 Assignment 2

// Written by: Pratik Napit 
// Date: 4/11/2021

// This is the header file for readData.c.


#ifndef rd_H
#define rd_H 

// Any defines: 
#include "list.h"
#include "Graph.h" 

// Data structure used: 

// Function initialisations: 


list get_collection(); 
Graph make_Graph(list l);
void insert_edge(char *url, Graph g, list l);
int url_to_index(char *url, list l); 
char *index_to_url(int index, list l);


#endif