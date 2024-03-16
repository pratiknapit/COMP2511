// COMP2521 Assignment 2

// Written by: Pratik Napit 
// Date: 4/11/2021

// This is a helper function to read the data and put it into a set. 

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "list.h"
#include "Graph.h" 
#include "readData.h"

/*
int main(void) {
    list l = get_collection();

    print_url_list(l);

    Graph g = MakeGraph(l);

    GraphShow(g);
}
*/

list get_collection() {

    //Use list ADT 

    char *file = "collection.txt";

    FILE *in = fopen(file, "r"); 

    list List_of_Urls = new_list(); 

    char url[100]; 

    while (fscanf(in, "%s", url) == 1) {

        insert_url(List_of_Urls, url); 
    }

    //print_url_list(List_of_Urls);

    fclose(in);  

    return List_of_Urls;

}

Graph make_Graph(list l) {
    //Create a new Graph with the list of urls 

    Graph g = GraphNew(l->nelems); 
    
    node curr = l->head;
    while (curr != NULL) {
        insert_edge(curr->url_name, g, l); 
        curr = curr->next;
    }
    
    return g; 

}

void insert_edge(char *url, Graph g, list l) {

    char *filename = strdup(url);

    filename = realloc(filename, strlen(url) + strlen(".txt") + 1);
    strcat(filename, ".txt");    

    FILE *in = fopen(filename, "r"); 

    char link_url[100]; 
    char *end = "#end"; 
    Edge edge;
    
    edge.v = url_to_index(url, l); // check if index is -1 then we have an ERROR !!!

    fscanf(in, "%*[^\n]\n"); // this should skip the first line of the file
    /*
    Assumptions: 

    Web pages may have links to themselves and multiple links to the same web page. 
    You must completely ignore self links and duplicate links, 
    including when calculating the outdegree of each page.

    URLs do not necessarily start with url. - this is a dumb assumption.

    Webpages could have no links to other pages.

    */
    while (fscanf(in, "%s", link_url) == 1) { 
        if (strcmp(link_url, end) == 0) return; 
        edge.w = url_to_index(link_url, l); 
        if (edge.v != edge.w) { //need to ignore self diedges
            GraphInsertEdge(g, edge);
        }
        //printf("%s\n", link_url); 
    }

    //  fscanf(file_pointer, "format string", list of address of variables),

}

int url_to_index(char *url, list l) { //iterate through the linked list and return the index O(n); 
    node curr = l->head; 
    while (curr != NULL) {
        if (strcmp(curr->url_name, url) == 0) {
            return curr->index; 
        }
        curr = curr->next;
    }
    return -1; 
}

char *index_to_url(int index, list l) {
    node curr = l->head; 
    while (curr != NULL) {
        if (curr->index == index) {
            return curr->url_name;
        }
        curr = curr->next;
    }
    return NULL;
}

