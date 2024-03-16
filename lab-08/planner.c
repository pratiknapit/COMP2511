// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */


int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {
    // TODO: Complete this function

    // Create a complete graph between all cities and the powerplant.
    
    // get the maximum number, (n(n-1)/2) and then use a minimum spanning tree
    Graph grid = GraphNew(numCities + 1);

    // insert all possible combinations of edges into a graph grid.
    for (int i = 0; i < numCities + 1; i++) {
        Edge cityToCity;
        Place city1;
        cityToCity.v = i;

        if (i != numCities) {
            city1 = cities[i];
        } else {
            city1 = powerPlant; //let the powerplant be the last index 
        }

        for (int j = 0; j < numCities; j++) {
            if (i != j) {
                Place city2 = cities[j];
                cityToCity.w = j;
                cityToCity.weight = sqrt( (city2.x - city1.x) * (city2.x - city1.x)
                + (city2.y - city1.y) * (city2.y - city1.y) );
                GraphInsertEdge(grid, cityToCity); // insert the edge with citytocity weight.
            }
        }
    }

    // use MST to find graph of minimal weight covering all vertices
    Graph span = GraphMST(grid);
    
    // Check MST and insert vertice-edge pairs into array, removing edge after to avoid duplicates.
    int index = 0;
    for (Vertex i = 0; i < numCities; i++) {
        for (Vertex j = 0; j < numCities; j++) {
            if (GraphIsAdjacent(span, i, j) != 0.0 ) { //check for adjacent cities in the MST graph
                powerLines[index].p1 = cities[i];
                powerLines[index].p2 = cities[j];
                GraphRemoveEdge(span, i, j);
                index++;
            }
        }
    }
    for (Vertex i = 0; i < numCities; i++) {
        if (GraphIsAdjacent(span, numCities, i) != 0.0) { // check for adjacent cities to the powerplant in the MST graph
            powerLines[index].p1 = powerPlant;
            powerLines[index].p2 = cities[i];
            index++;
        }
    }

    // free all graphs
    GraphFree(grid);
    GraphFree(span);

    return index;
    
   return 0;
}




////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
