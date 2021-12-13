#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "../1-Graph/Graph.hpp"

/**
 * @brief Convert a map tile character to a weight.
 * 
 * @param c Character representing a map tile.
 * @return double Weight associated with moving to that tile.
 */
double charToWeight(char c) {
    switch(c) {
        case 'c': return 1;
        case 's': return 1.5;
        case 'w': return 3;
        case 'x': return -1; // flag - do not add an edge here
        case 'b': return 1;
        case 'e': return 1;
    }
    return -1;
}

/**
 * @brief Convert a (row, col) coordinate to a vertex number.
 * 
 * @param numR Number of rows in the map.
 * @param r Row of the coordinate
 * @param c Column of the coordinate
 * @return size_t Vertex number in [1, numR * numC]
 */
size_t rowColToVertex(size_t numR, size_t r, size_t c) {
    return r * numR + c + 1;
}

/**
 * @brief Application entry point.
 * 
 */
int main() {

    // read map file into character array; first, get size
    std::ifstream inFile("map.txt");
    size_t numR, numC;
    inFile >> numR >> numC;

    // allocate 2D array for map storage
    char **pMap = new char*[numR];
    for(size_t r = 0; r < numR; r++) {
        pMap[r] = new char[numC];
    }

    // read remaining lines from the file, place characters into the array
    std::string line;
    for(size_t r = 0; r < numR; r++) {
        inFile >> line;
        for(size_t c = 0; c < numC; c++) {
            pMap[r][c] = line[c];
        }
    }
    inFile.close();

    // build a graph representation of the map
    Graph g(numR * numC);
    for(size_t r = 0; r < numR; r++) {
        for(size_t c = 0; c < numC; c++) {
            // source vertex number
            size_t vertex = rowColToVertex(numR, r, c);
            double weight;

            // examine all valid neighbors and enter edges w/ weights
            if(r > 0) {
                // north neighbor
                weight = charToWeight(pMap[r - 1][c]);
                if(weight > 0) {
                    g.addEdge(vertex, rowColToVertex(numR, r - 1, c), weight);
                }
            }
            if(r < numR - 1) {
                // south neighbor
                weight = charToWeight(pMap[r + 1][c]);
                if(weight > 0) {
                    g.addEdge(vertex, rowColToVertex(numR, r + 1, c), weight);
                }
            }
            if(c < numC - 1) {
                // east neighbor
                weight = charToWeight(pMap[r][c + 1]);
                if(weight > 0) {
                    g.addEdge(vertex, rowColToVertex(numR, r, c + 1), weight);
                }
            }
            if(c > 0) {
                // west neighbor
                weight = charToWeight(pMap[r][c - 1]);
                if(weight > 0) {
                    g.addEdge(vertex, rowColToVertex(numR, r, c - 1), weight);
                }
            }
        } // for c
    } // for r

    // execute Dijkstra's algorithm to find a path to the end point
    double pDist[numR * numC + 1];
    size_t pPred[numR * numC + 1];
    g.Dijkstra(1, pDist, pPred);

    // construct path from start (assumed to be vertex 1) to the end
    std::list<size_t> path;
    path.push_front(numR * numC);
    size_t p = numR * numC;
    while(pPred[p] != 1) {
        path.push_front(pPred[p]);
        p = pPred[p];
    }
    path.push_front(1);

    // output path 
    std::cout << "Path from start to finish: ";
    for(size_t p1 : path) {
        std::cout << p1 << " ";
    }
    std::cout << std::endl;

    // free memory allocated for the map
    for(size_t r = 0; r < numR; r++) {
        delete [] pMap[r];
    }
    delete [] pMap;

    return EXIT_SUCCESS;
}