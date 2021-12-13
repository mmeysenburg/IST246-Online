#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include "Graph.hpp"

int main() {
    Graph g(5);

    // read edges from a text file
    std::ifstream inFile("dir.txt");
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

    // execute Dijkstra's algorithm
    double pDist[6];
    size_t pPred[6];
    g.Dijkstra(1, pDist, pPred);

    // display distance results
    for(size_t v = 1; v <= 5; v++) {
        std::cout << "Distance from 1 to " << v << ": " << pDist[v] << std::endl;
    }
    std::cout << std::endl;

    // display path results
    for(size_t v = 2; v <= 5; v++) {
        std::list<size_t> path;
        path.push_front(v);
        size_t p = v;
        while(pPred[p] != 1) {
            path.push_front(pPred[p]);
            p = pPred[p];
        }
        path.push_front(1);

        std::cout << "Path from 1 to " << v << ": ";
        for(size_t p1 : path) {
            std::cout << p1 << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}