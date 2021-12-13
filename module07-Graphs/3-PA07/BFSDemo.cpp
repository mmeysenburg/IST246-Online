#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "Graph.hpp"

int main() {
    Graph g(8);

    // read edges from a text file
    std::ifstream inFile("undir.txt");
    size_t u, v;
    double weight;
    while(inFile >> u >> v >> weight) {
        g.addEdge(u, v, weight);
    }
    inFile.close();

    // print graph representation
    std::cout << "Graph has " << g.numVertices() << " vertices and " << 
        g.numEdges() << " edges" << std::endl;
    std::cout << "Graph adjacencies:" << std::endl;
    std::cout << g << std::endl;

    // execute BFS algorithm
    double pDist[9];
    size_t pPred[9];
    g.BFS(2, pDist, pPred);

    // display distance results
    for(size_t v = 1; v <= 8; v++) {
        std::cout << "Distance from 2 to " << v << ": " << pDist[v] << std::endl;
    }
    std::cout << std::endl;

    // display path results
    for(size_t v = 1; v <= 8; v++) {
        if(v != 2) {
            std::list<size_t> path;
            path.push_front(v);
            size_t p = v;
            while(pPred[p] != 2) {
                path.push_front(pPred[p]);
                p = pPred[p];
            }
            path.push_front(2);

            std::cout << "Path from 2 to " << v << ": ";
            for(size_t p1 : path) {
                std::cout << p1 << " ";
            }
            std::cout << std::endl;
        }
    }

    return EXIT_SUCCESS;
}