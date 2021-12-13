#pragma once

#include <algorithm>
#include <cmath>
#include <doctest.h>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector> 

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief Non-templated class representing a weighted graph G=(V, E).
 * 
 * This class uses an adjacency-matrix representation for the graph. The code is
 * based on the graph algorithms discussed in 
 * 
 * Cormen, T. H., &; Leiserson, C. E. (2009). Introduction to algorithms, 3rd Ed. 
 */
class Graph {

public:
    /**
     * @brief Construct a new Graph object.
     * 
     * @param numVertices Number of vertices in the graph. Defaults to 100.
     */
    Graph(size_t numVertices = 100);

    /**
     * @brief Destroy the Graph object
     * 
     */
    ~Graph();

    /**
     * @brief Add an edge (u, v) to the graph.
     * 
     * @param u "From" vertex of the edge.
     * 
     * @param v "To" vertex of the edge.
     * 
     * @param weight Weight associated with edge (u, v).
     * 
     * @throws std::out_of_range if either u or v is < 1 or > |V|.
     */
    void addEdge(size_t u, size_t v, double weight);

    /**
     * @brief Perform breadth-first search on this graph
     * 
     * This method performs a breadth-first search to look find the shortest
     * path, in terms of edge count, from a vertex s to any other vertex in
     * the graph.
     * 
     * @param s Vertex to search from
     * 
     * @param pDist Array of doubles with size |V| + 1. Upon return, array 
     * elements [1, ..., |V|] will contain the distance from vertex s to all
     * the other vertices, in terms of number of edges.
     * 
     * @param pPred Array of size_t values with size |V| + 1. Upon return, 
     * array elements [1, ..., |V|] will contain predecessor elements. These
     * allow us to work backwards to create the minimum hop count path from s
     * to any other element in the graph.
     * 
     * @throws std::out_of_range if s is < 1 or > |V|.
     */
    void BFS(size_t s, double *pDist, size_t *pPred) const;

    /**
     * @brief Perform Dijkstra's algorithm on this graph
     * 
     * This method performs Dikstra's algorithm to look find the shortest
     * path, in terms of edge weights, from a vertex s to any other vertex in
     * the graph.
     * 
     * @param s Vertex to search from
     * 
     * @param pDist Array of doubles with size |V| + 1. Upon return, array 
     * elements [1, ..., |V|] will contain the distance from vertex s to all
     * the other vertices, in terms of path edge weights.
     * 
     * @param pPred Array of size_t values with size |V| + 1. Upon return, 
     * array elements [1, ..., |V|] will contain predecessor elements. These
     * allow us to work backwards to create the minimum hop count path from s
     * to any other element in the graph.
     * 
     * @throws std::out_of_range if s is < 1 or > |V|.
     */
    void Dijkstra(size_t s, double *pDist, size_t *pPred) const;

    /**
     * @brief Get the weight of the edge (u, v). 
     * 
     * @param u "From" vertex of the edge.
     * 
     * @param v "To" vertex of the edge.
     * 
     * @return double Weight of the edge (u, v), NaN if there is no edge 
     * between u and v.
     * 
     * @throws std::out_of_range if either u or v is < 1 or > |V|.
     */
    double getEdge(size_t u, size_t v) const;

    /**
     * @brief Get number of edges in the graph.
     * 
     * @return size_t value holding the number of edges in the graph. 
     */
    size_t numEdges() const;

    /**
     * @brief Get number of vertices in the graph.
     * 
     * @return size_t value holding the number of vertices in the graph. 
     */
    size_t numVertices() const { return numV; }

    /**
     * @brief Stream insertion override.
     * 
     * @param out std::ostream to write to
     * 
     * @param g Graph to print
     * 
     * @return std::ostream& object written to
     */
    friend std::ostream& operator<<(std::ostream &out, const Graph &g) {
        for(size_t r = 1; r <= g.numV; r++) {
            for(size_t c = 1; c <= g.numV; c++) {
                if(g.pMatrix[r][c] == std::numeric_limits<double>::infinity()) {
                    out << "∞ ";
                } else {
                    out << g.pMatrix[r][c] << " ";
                }
            }
            out << std::endl;
        }
        return out;
    }

private:
    /**
     * @brief Number of vertices in the graph.
     * 
     */
    size_t numV;

    /**
     * @brief Pointer to an 2D array of doubles, holding the edge data 
     * for this graph.
     * 
     */
    double **pMatrix;
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

/*
 * constructor implementation.
 */
Graph::Graph(size_t numVertices) : numV(numVertices) {
    // TODO: allocate 2D array of doubles (pMatrix) for the graph, 
    // and fill with std::numeric_limits<double>::infinity() values
}

/*
 * destructor implementation.
 */
Graph::~Graph() {
    // TODO: free memory for the 2D array of doubles
}

/*
 * addEdge method implementation.
 */
void Graph::addEdge(size_t u, size_t v, double weight) { 
    if(u == 0u ||  v == 0u || u > numV || v > numV) {
        throw std::out_of_range("Illegal vertex in Graph::addEdge()");
    }
    // TODO: add weight to adjacency matrix location (u, v)
}

/*
 * Breadth-first search implementation.
 */
void Graph::BFS(size_t s, double *pDist, size_t *pPred) const {
    // make sure s is a valid index number
    if(s == 0u || s > numV) {
        throw std::out_of_range("Illegal vertex in Graph::BFS()");
    }

    // coloring constants to keep track of which vertices have been
    // explored
    const int WHITE = 0;
    const int GRAY = 1;
    const int BLACK = 2;

    // allocate tracking attribute memory
    int *pColor = new int[numV + 1];

    // initialize tracking attributes for each non-s vertex
    for(size_t u = 1; u <= numV; u++) {
        if(u != s) {
            pColor[u] = WHITE;
            pDist[u] = std::numeric_limits<double>::infinity();
            pPred[u] = 0u;
        }
    }

    // initialize tracking attributes for node s
    pColor[s] = GRAY;
    pDist[s] = 0;
    pPred[s] = 0u;

    // use STL queue to keep track of edges we need to explore
    std::queue<size_t> Q;
    // start at node s
    Q.push(s);

    // keep going until no more vertices are reachable
    while(!Q.empty()) {
        // dequeue first element
        size_t u = Q.front();
        Q.pop();

        // examine all vertices adjacent to u
        for(size_t v = 1; v <= numV; v++) {
            if(pMatrix[u][v] != std::numeric_limits<double>::infinity()) {
                // add unexplored vertices to the queue
                if(pColor[v] == WHITE) {
                    // color as "discovered but incomplete"
                    pColor[v] = GRAY;
                    // track distance from v to u so far
                    pDist[v] = pDist[u] + 1;
                    // v's predecessor is u
                    pPred[v] = u;

                    Q.push(v);
                }
            }
        }
        // this vertex is completely explored
        pColor[u] = BLACK;
    }

    // free color tracking memory
    delete [] pColor;
}

// doctest unit tests for BFS
TEST_CASE("testing Graph::BFS()") {
    Graph g(8);

    g.addEdge(1, 2, 1);
    g.addEdge(1, 5, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 6, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 6, 1);
    g.addEdge(3, 7, 1);
    g.addEdge(4, 7, 1);
    g.addEdge(4, 8, 1);
    g.addEdge(5, 1, 1);
    g.addEdge(1, 5, 1);
    g.addEdge(6, 2, 1);
    g.addEdge(6, 3, 1);
    g.addEdge(6, 7, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(7, 3, 1);
    g.addEdge(7, 4, 1);
    g.addEdge(7, 8, 1);
    g.addEdge(8, 7, 1);
    g.addEdge(8, 4, 1);

    double pDist[9];
    size_t pPred[9];

    g.BFS(2, pDist, pPred);

    double pDistActual[9] = {0, 1, 0, 2, 3, 2, 1, 2, 3};
    size_t pPredActual[9] = {0, 2, 0, 6, 3, 1, 2, 6, 7};

    for(size_t i = 1; i <= 8; i++) {
        CHECK(pDistActual[i] == pDist[i]);
        CHECK(pPredActual[i] == pPred[i]);
    }

    // check exceptions
    bool flag = true;
    try {
        g.BFS(0, pDist, pPred);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);

    flag = true;
    try {
        g.BFS(9, pDist, pPred);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
}

/*
 * Dijkstra method implementation.
 */
void Graph::Dijkstra(size_t s, double *pDist, size_t *pPred) const {
    // sanity check on vertex number s
    if(s < 1 || s > numV) {
        throw std::out_of_range("Illegal vertex number in Graph::Dijkstra()");
    }

    // initialize distances and predecessors
    for(size_t i = 1; i <= numV; i++) {
        pDist[i] = std::numeric_limits<double>::infinity();
        pPred[i] = 0;
    }
    pPred[s] = 0;
    pDist[s] = 0;

    // populate the "priority queue" with all vertices in the graph
    std::list<size_t> Q;
    for(size_t v = 1; v <= numV; v++) {
        Q.push_back(v);
    }

    // continue until we have examined all vertices
    while(!Q.empty()) {
        // examine the node closest to the set of nodes we've looked at so far
        auto uItr = Q.begin();
        double minValue = std::numeric_limits<double>::infinity();
        for(auto i = Q.begin(); i != Q.end(); i++) {
            if(pDist[*i] < minValue) {
                minValue = pDist[*i];
                uItr = i;
            }
        }
        // by now, uItr is an iterator on the smallest value in the queue,
        // so save its value as vertex u
        size_t u = *uItr;
        // then use the std::list erase method to remove the value at the 
        // iterator location
        Q.erase(uItr);

        // TODO: modify this code to work with adjacency matrix instead of
        // adjacency lists
        // update distances and predecessors for the vertex we just removed 
        // from the "priority queue"
        for(AdjEntry v : *(pAdjacents[u])) {
            if(pDist[v.v] > pDist[u] + v.wUV) {
                pDist[v.v] = pDist[u] + v.wUV;
                pPred[v.v] = u;
            } // if
        } // for
    } // while 
}

// doctest unit test for Dijkstra's algorithm method
TEST_CASE("testing Graph::Dijkstra()") {
    Graph g(5);

    g.addEdge(1, 2, 10);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 5, 4);
    g.addEdge(4, 2, 3);
    g.addEdge(4, 3, 9);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 1, 7);
    g.addEdge(5, 3, 6);

    double pDist[6];
    size_t pPred[6];

    g.Dijkstra(1, pDist, pPred);

    double pDistPredicted[6] = {0, 0, 8, 9, 5, 6};
    size_t pPredPredicted[6] = {0, 0, 4, 2, 1, 4};

    for(size_t i = 1; i <= 5; i++) {
        CHECK(pDist[i] == pDistPredicted[i]);
        CHECK(pPred[i] == pPredPredicted[i]);
    }

    // check exception handling
    bool flag = true;
    try {
        g.Dijkstra(0, pDist, pPred);
        flag = false;
    } catch(std::out_of_range oor) {

    }
    CHECK(flag);
    flag = true;
    try {
        g.Dijkstra(6, pDist, pPred);
        flag = false;
    } catch(std::out_of_range oor) {

    }
    CHECK(flag);
}

/*
 * getEdge method implementation.
 */
double Graph::getEdge(size_t u, size_t v) const {
    if(u == 0u || v == 0u || u > numV || v > numV) {
        throw std::out_of_range("Illegal vertex in Graph::getEdge()");
    }

    if(pMatrix[u][v] == std::numeric_limits<double>::infinity()) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return pMatrix[u][v];
    }
}

// doctest unit tests for addEdge and getEdge
TEST_CASE("testing Graph::addEdge() and getEdge()") {
    Graph g(5);

    g.addEdge(1, 2, 1);
    CHECK(g.getEdge(1, 2) == 1.0);
    g.addEdge(1, 5, 2);
    CHECK(g.getEdge(1, 5) == 2.0);
    g.addEdge(2, 1, 3);
    CHECK(g.getEdge(2, 1) == 3.0);
    g.addEdge(2, 5, 4);
    CHECK(g.getEdge(2, 5) == 4.0);
    g.addEdge(2, 4, 5);
    CHECK(g.getEdge(2, 4) == 5.0);
    g.addEdge(2, 3, 6);
    CHECK(g.getEdge(2, 3) == 6.0);
    g.addEdge(3, 2, 7);
    CHECK(g.getEdge(3, 2) == 7.0);
    g.addEdge(3, 4, 8);
    CHECK(g.getEdge(3, 4) == 8.0);
    g.addEdge(4, 2, 9);
    CHECK(g.getEdge(4, 2) == 9.0);
    g.addEdge(4, 3, 10);
    CHECK(g.getEdge(4, 3) == 10.0);
    g.addEdge(4, 5, 11);
    CHECK(g.getEdge(4, 5) == 11.0);
    g.addEdge(5, 1, 12);
    CHECK(g.getEdge(5, 1) == 12.0);
    g.addEdge(5, 2, 13);
    CHECK(g.getEdge(5, 2) == 13.0);
    g.addEdge(5, 4, 14);
    CHECK(g.getEdge(5, 4) == 14.0);

    // test edges that don't exist
    double w = g.getEdge(5, 3);
    CHECK(std::isnan(w));
    w = g.getEdge(1, 4);
    CHECK(std::isnan(w));

    // test exception handling of addEdge
    bool flag = true;
    try {
        g.addEdge(0, 5, 13);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.addEdge(5, 0, 13);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.addEdge(6, 5, 13);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.addEdge(5, 6, 13);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);

    // check exception handling for getEdge
    flag = true;
    try {
        g.getEdge(0, 5);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.getEdge(5, 0);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.getEdge(6, 5);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
    flag = true;
    try {
        g.getEdge(5, 6);
        flag = false;
    } catch(std::out_of_range oor) {
    }
    CHECK(flag);
}

/*
 * numEdges method implementation.
 */
size_t Graph::numEdges() const {
    size_t sum = 0u;
    // TODO: update this code to count the number of edges --
    // the number of entries in pMatrix that are not 
    // std::numeric_limits<double>::infinity()
    for(size_t i = 1u; i <= numV; i++) {
        sum += pAdjacents[i]->size();
    }

    return sum;
}

// doctest unit test for numEdges method
TEST_CASE("testing Graph::numEdges()") {
    Graph g(5);
    CHECK(0 == g.numEdges());

    g.addEdge(1, 2, 1);
    CHECK(1 == g.numEdges());
    g.addEdge(1, 5, 1);
    CHECK(2 == g.numEdges());
    g.addEdge(2, 1, 1);
    CHECK(3 == g.numEdges());
    g.addEdge(2, 5, 1);
    CHECK(4 == g.numEdges());
    g.addEdge(2, 4, 1);
    CHECK(5 == g.numEdges());
    g.addEdge(2, 3, 1);
    CHECK(6 == g.numEdges());
    g.addEdge(3, 2, 1);
    CHECK(7 == g.numEdges());
    g.addEdge(3, 4, 1);
    CHECK(8 == g.numEdges());
    g.addEdge(4, 2, 1);
    CHECK(9 == g.numEdges());
    g.addEdge(4, 3, 1);
    CHECK(10 == g.numEdges());
    g.addEdge(4, 5, 1);
    CHECK(11 == g.numEdges());
    g.addEdge(5, 1, 1);
    CHECK(12 == g.numEdges());
    g.addEdge(5, 2, 1);
    CHECK(13 == g.numEdges());
    g.addEdge(5, 4, 1);
    CHECK(14 == g.numEdges());
}

// doctest unit test for numVertices method
TEST_CASE("testing Graph::numVertices()") {
    Graph g;
    CHECK(100 == g.numVertices());
    Graph h(5);
    CHECK(5 == h.numVertices());
}

// doctest unit test for operator<< 
TEST_CASE("testing operator<<") {
    Graph g(5);

    g.addEdge(1, 2, 1);
    g.addEdge(1, 5, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 2, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 2, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 1, 1);
    g.addEdge(5, 2, 1);
    g.addEdge(5, 4, 1);

    std::ostringstream oss;
    oss << g;
    std::string expected("∞ 1 ∞ ∞ 1 \n");
    expected += "1 ∞ 1 1 1 \n";
    expected += "∞ 1 ∞ 1 ∞ \n"; 
    expected += "∞ 1 1 ∞ 1 \n";
    expected += "1 1 ∞ 1 ∞ \n";
    CHECK(oss.str() == expected);
}