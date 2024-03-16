// COMP2521 Assignment 2

// Written by: Pratik Napit 
// Date: 4/11/2021 

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Graph.h"
#include "list.h"
#include "readData.h"

double *calculatePageRank(Graph g, double d, double diffPR, int maxIterations);

int main(int argc, char *argv[]) {

    //Convert the command-line arguments as required.
    double d = atof(argv[1]); // damping factor 
    double diffPR = atof(argv[2]); //sum of PageRank differences 
    int maxIterations = atoi(argv[3]); //max iterations 

    // Make a new list for the urls.
    list url_list = get_collection(); 

    // Make a new graph for the urls.
    Graph g = make_Graph(url_list); 

    // N = number of urls in the collection
    int n = GraphNumVertices(g);

    //Use the calculatePageRank given formula to calculate the pageranks for each url.
    //Then return the pageranks as an array for each url. 

    double *pageRank = calculatePageRank(g, d, diffPR, maxIterations);
    
    //use function to get the outlinks.
    int *out_links = get_outlinks(n, g);

    //Write the pageRank and outlinks to pagerankList.txt
    FILE *write = fopen("pagerankList.txt", "w");

    for (int i = 0; i < n; i++) {
        double pr = 0.0; 
        int index = 0; 
        // Loop through all the elements in pageRank, and store the largest value and that value's 
        // index in the array.
        for (int j = 0; j < n; j++) {
            if (pageRank[j] >= pr) {
                pr = pageRank[j];
                index = j; 
            }
        }
        fprintf(write, "%s, %d, %.7f\n", index_to_url(index, url_list), out_links[index], pr); 

        //after we are done, we then give that index a value of -1 so we dont
        //print it again.
        pageRank[index] = -1;
    }

    fclose(write); 

    //Free all the memory allocated variables.

    free(pageRank);

    free(out_links);

    graph_free(g);

    free_list(url_list);

    return 0;

}



//Use this function to calculate the PageRank as suggested in the spec.

double *calculatePageRank(Graph g, double d, double diffPR, int maxIterations)  {
    
    //USE THE GIVEN FORMULA IN THE SPEC TO CALCULATE THE PAGERANKS FOR EACH URL IN THE GRAPH.

    int n = GraphNumVertices(g); 
    //Turn n into a double as we will need to divide by n. 
    double fN = (double)n; 
    double *pageRank = (double*) calloc(n, sizeof(double));
    double prevRank[n];


    //Calculate the first iteration pageranks.
    for (int i = 0; i < n; i++) {
        pageRank[i] = 1/fN; 
        prevRank[i] = 1/fN;
    }

    int iteration = 0; 
    double diff = diffPR; 

    //Use the formula given to caculate the pageranks.
    while (iteration < maxIterations && diff >= diffPR) {
        //Loop through so we can calculate the pageRank for every vertex in the graph 
        for (int i = 0; i < n; i++) {
            double sumPR = 0;
            for (int j = 0; j < n; j++) {
                if (GraphIsAdjacent(g, j, i) == true && i != j) {
                    sumPR = sumPR + (prevRank[j] * in_links(g, j, i) * out_links(g, j, i)); 
                }
            }
            pageRank[i] = ((1-d)/fN) + (d * sumPR); 
        }
        for (int i = 0; i < n; i++) {
            diff += fabs(pageRank[i] - prevRank[i]);
        }
        for (int i = 0; i < n; i++) {
            prevRank[i] = pageRank[i];
        }
        iteration++; 
    }



    return pageRank; 
}

// A function to implement bubble sort



