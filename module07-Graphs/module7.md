## Module 7: Graphs


**Note: the algorithms in this module are due to those found in Cormen, T. H., & Leiserson, C. E. (2009). Introduction to algorithms, 3rd Edition.**


In this module, we will introduce a class to represent a mathematical *graph*, and some elementary graph algorithms. This module and the next are more about algorithms than data structures, that is, we are not really designing and implementing a container to store data, but looking at how graphs can be used to solve problems. For example, routing of data on the Internet relies on graph algorithms to pick the best path to take, even if portions of the network are down or are experiencing slowdowns. 


### Introduction to graphs


A *graph G = (V, E)* is a set of vertices *V* connected by a set of edges *E*. We visualize graphs with circles representing vertices and lines between the circles representing edges. For example, consider this graph:


<img src="https://doane.instructure.com/files/986922/download?download_frd=1" alt="Simple 5 vertex graph" title="Simple 5 vertex graph"/>


For this graph, the set *V = {1, 2, 3, 4, 5}* and the set *E = {(1, 2), (1, 5), (2, 3), (2, 4), (2, 5), (3, 4), (4, 5)}*. This graph is *undirected*, because the edges have no associated direction, e.g., we could "move" from vertex 1 to vertex 2, or from vertex 2 to vertex 1, via the edge *(1, 2)*. This graph is also *unweighted*, because there is no weight or cost associated with the edges. 


On the other hand, this graph is *directed* and *weighted*:


<img src="https://doane.instructure.com/files/986939/download?download_frd=1" alt="Simple weighted digraph" title="Simple weighted digraph"/>


The arrows show the direction of each edge, and the lines have their weights indicated with numbers. Directed edges mean we can only move in one direction. In this graph, we can move from vertex 1 to vertex 2 (with a cost of 2), but we cannot move from vertex 2 to vertex 1. 


### Representing graphs


Before we start looking at graph algorithms, we first have to decide how we will represent a graph in our code. There are two common options: *adjacency lists* or an *adjacency matrix*. 


#### Adjacency list representation


In an adjacency list representation, we have an array of *|V| + 1* lists, where each list *v = {1, 2, 3, ..., |V|}* contains the vertices connected to node *v*. The algorithms we examine later will work better if we number vertices starting at 1, so we will have an extra, unused list at array location 0. 


For our sample undirected graph,


<img src="https://doane.instructure.com/files/986922/download?download_frd=1" alt="Simple 5 vertex graph" title="Simple 5 vertex graph"/>


an array of adjacency lists might look like this:


```
list 0: unused
list 1: 2, 5
list 2: 1, 5, 3, 4
list 3: 2, 4
list 4: 2, 3, 5
list 5: 2, 1, 4
```


Note that for an undirected graph we have to store each edge in both directions, e.g., list 1 contains vertex 2 and list 2 contains vertex 1. If our graph is weighted, we would need to have some way of storing the weights as well as the edges. For example, we could store (vertex, weight) pairs in the adjacency lists. 


An adjacency list representation is a good choice when a graph is sparse, when *|E|* is much smaller than*|V|<sup>2</sup>*. A disadvantage is that the process of determining if there is an edge between two vertices is *O(|E|)* in the worst case, because we have to search through a list of vertices to see if the edge exists.


#### Adjacency matrix representation


In an adjacency matrix representation of a graph, we create a two-dimensional array of size *(|V| + 1) x (|V| + 1)*, and place a value in row *u*, column *v* if there is an edge *(u, v)*. The value may simply be a 1 if the graph is unweighted, or the weight value if it is a weighted graph. 


For our sample weighted digraph,


<img src="https://doane.instructure.com/files/986939/download?download_frd=1" alt="Simple weighted digraph" title="Simple weighted digraph"/>


the adjacency matrix representation would look like this:


<img src="https://doane.instructure.com/files/987058/download?download_frd=1" alt="Digraph adjacency matrix" title="Digraph adjacency matrix"/>


Since we want our vertices to start at one rather than at zero, the first row and column of the matrix are unused. For a weighted graph, we simply store the edge *(u, v)*'s weight at position *(u, v)* in the matrix. We put some flag value (represented by the ∞ in the matrix) in spaces where there is no edge between two vertices. If the graph is undirected, the adjacency matrix will be symmetric around the diagonal. 


An advantage of the adjacency matrix representation is that checking to see if there is an edge *(u, v)* takes *O(1)* time. The disadvantage of this storage scheme is that it takes a lot of memory: *|V|<sup>2</sup>*. If the graph is sparse, we will have a lot of wasted memory, and if the graph is large, we may not be able to store the whole matrix in memory. 


In our discussions here, we will use an adjacency list representation. 


### Graph implementation


**[For this section, refer to the `module07/1-Graph/Graph.hpp` file from the course's git repository.]**


Our C++ implementation of a graph will use an adjacency list representation and support weighted edges. To expose you to some of the data structure classes provided in C++ distributions, we will use the "built-in" classes rather than one of our own lists in this implementation. 


Since a graph is not a container for holding data, our `Graph` class will not need to be templated. The class exists primarily to encapsulate the adjacency list structures and to provide some simple graph algorithms. Here are UML class diagrams of the `Graph` class and its private inner class, `AdjEntry`:


<img src="https://doane.instructure.com/files/987064/download?download_frd=1" alt="Graph UML class diagram" title="Graph UML class diagram"/>


In the `Graph` class, the `numV` field holds the number of vertices in the graph. The field `pAdjacents` is a pointer to an array of pointers to C++ Standard Template Library (STL) `std::list` objects, which holds information on the edges of the graph. The `std::list` class is a doubly-linked list that is part of the standard C++ distribution. Each element in an adjacency list is an `AdjEntry` object, which contains the endpoint vertex number `v` and the weight of the edge, `wUV`. 


#### Constructor and destructor


In our previous data structures, the constructor has been very simple, since the structures were created empty. The constructor for the `Graph` class has a bit more work to do, since it has to create and initialize the array of pointers to `std::list` objects. Here is the constructor's code:


```
// in class definition
Graph(size_t numVertices = 100);


...


// implementation
Graph::Graph(size_t numVertices) : numV(numVertices) {
    pAdjacents = new std::list<AdjEntry>*[numV + 1];
    for(size_t i = 1; i <= numV; i++) {
        pAdjacents[i] = new std::list<AdjEntry>();
    }
}
```


In the class definition, we set the default value of the `numVertices` parameter to 100. In this way, this single constructor serves as both the initializing (if the user provides a number of vertices) and default (if they do not) constructor. In the implementation, we first create an array of *|V| + 1* pointers to pointers to `std::list` objects. At this point, we have pointers, but no actual lists, so we continue with a `for` loop that allocates a total of *|V|* lists parameterized to hold `AdjEntry` objects. 


The destructor has to safely free all of that memory:


```
Graph::~Graph() {
    for(size_t i = 1; i <= numV; i++) {
        delete pAdjacents[i];
    }
    delete [] pAdjacents;
}
```


The destructor does its job in the reverse order from how the constructor allocated the lists. First, we use a `for` loop to free each of the `std::list` objects, then we delete the `pAdjacents` array itself. 


#### Adding and getting edges


In our class, we add each edge individually via the `addEdge` method, which allows us to add an edge *(u, v)* with weight *w*:


```
void Graph::addEdge(size_t u, size_t v, double weight) { 
    if(u == 0u ||  v == 0u || u > numV || v > numV) {
        throw std::out_of_range("Illegal vertex in Graph::addEdge()");
    }
    pAdjacents[u]->push_back(AdjEntry(v, weight));
}
```


We begin with a safety check on the vertex numbers. After that, we go to vertex *u*'s adjacency list, and add an `AdjEntry` object to it containing vertex number *v* and the edge weight *w*. Note that the `pAdjacents` array contains *pointers* to `std::list` objects, so we use the `->` operator to dereference the pointer corresponding to *u*'s list, and call the list's `push_back` method, which is equivalent to the `addLast` method in our `DLL` implementation. 


To get the weight of an edge in our graph, the `Graph` class provides the `getEdge` method, which will return the weight for edge *(u, v)* or the not-a-number (NaN) value if there is no edge *(u, v)*:


```
double Graph::getEdge(size_t u, size_t v) const {
    if(u == 0u || v == 0u || u > numV || v > numV) {
        throw std::out_of_range("Illegal vertex in Graph::getEdge()");
    }


    auto idx = std::find(pAdjacents[u]->begin(), pAdjacents[u]->end(), v);
    if(idx == pAdjacents[u]->end()) {
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        return (*idx).wUV;
    }
}
```


As for `addEdge`, we start by verifying that the vertex number parameters are valid. Then, we have to determine if vertex *v* is in vertex *u*'s adjacency list. This requires a couple of interesting pieces of code. 


First, there is no `contains` method in the `std::list` class. To search the list, we use the `std::find` function from the `<algorithm>` header. This function takes three parameters: an iterator to the start of the list, an iterator to the end of the list, and the value we are searching for. The function returns an iterator to the first occurrence of the value in the list, or the `end()` iterator if the value was not in the list. The type of the returned iterator would be pretty long to type out, so we take advantage of the `auto` keyword, which means that the C++ compiler will figure out the type of the `std::find` return value, and declare our result variable `idx` to be of that type. Then, we can check the value of `idx == pAdjacents[u]->end()` to tell if we found vertex *v* or not. 


The second interesting piece of code is more subtle. In the `std::find` function call, the third parameter, `v`, is a vertex number with type `size_t`. However, what is in the list? `AdjEntry` objects! On the surface, it appears that we are comparing apples to oranges. 


We made this work by some code in the `AdjEntry` private inner class:


```
    class AdjEntry {
    public:
        AdjEntry(size_t vertex, double weight) : v(vertex), wUV(weight) { }


        size_t v;


        double wUV;


        bool operator==(size_t vertex) { return v == vertex; }


        friend std::ostream &operator<<(std::ostream &out, const AdjEntry &a) {
            out << "(" << a.v << ", " << a.wUV << ")";
            return out;
        }
    };
```


With the `operator==` override, we provide a way to compare an `AdjEntry` object of the left-hand side of the operator with a `size_t` value on the right-hand side. Thus, the `std::find` function call will find the first `AdjEntry` object in the adjacency list that has the vertex value `v`. If we did not have this override, the code would not compile, because the compiler would not know how to compare the disparate types of values. 


The return value if there is no edge *(u, v)* is NaN. If there is an edge *(u, v)*, we dereference the iterator `idx`, which results in an `AdjEntry` object, then return that object's `wUV` value, the weight of edge *(u, v)*.


#### Breadth-first search


One of the common tasks to perform on a graph is to determine which vertices are reachable from a vertex *s*, "how far" it is from vertex *s* to any of its connected vertices, and what the "minimum cost" path from vertex *s* to any of its connected vertices is. We put "how far" and "minimum cost" in quotes because those concepts may be defined differently, depending on the graph and the application. Consider this undirected, unweighted graph:


<img src="https://doane.instructure.com/files/987106/download?download_frd=1" alt="BFS sample graph" title="BFS sample graph"/>


We will assume *s = 2*, and since the graph is not weighted, cost / distance will be defined as the minimum number of edges between *s* and another vertex. It should be apparent that all of the other vertices are reachable from *s*. The cost from vertex 2 to vertex 1 is 1, since they are directly connected by the edge *(1, 2)*. The cost from vertex 2 to vertex 3 is 2, because the *shortest* path from vertex 2 to vertex 3 contains two edges: *(2, 6)* and *(3, 6)*. 


A *breadth-first search* (BFS) algorithm starts at vertex *s* and finds all of the vertices connected to *s*. Along the way, the algorithm keeps track of the minimum distance from *s* to the other vertices, and information that can be used to construct the shortest path from *s* to any other vertex. The algorithm first finds all of the vertices one edge away from *s*, then all of the vertices two edges away, then all of the vertices three edges away, and so on, until all of the vertices in the graph have been considered. 


Along the way, a *coloring* scheme will be used to keep track of the vertices that have and have not been considered. Vertices that have not been discovered yet are colored white. Vertices that are not white have already been discovered by the algorithm. A vertex that has been discovered, for which all adjacent vertices are not white, will be colored black. A vertex that has been discovered, for which some adjacent vertices are still white, will be colored gray. So, white vertices have not been considered yet, black vertices are "completely discovered," and gray vertices represent the boundary between the known and unknown as the algorithm progresses. 


These colors are abstract, of course -- we do not try to somehow "paint" the bytes in RAM that represent each vertex. Rather, we will have an array of *|V| + 1* integers, containing values that we associate with white, black, and gray. 


The BFS algorithm will take the starting vertex *s* as a parameter, along with two arrays of size *|V| + 1|*, `pDist` and `pPred`, which, after the algorithm is complete, will hold the distance from *s* to each other vertex, and each vertex's *predecessor*, respectively. The predecessor values allow us to construct the minimum-cost path from *s* to each other vertex. We will see how to use the information in the predecessor array in an example after we tour the BFS algorithm code. 


We will consider the BFS code in two parts. In the first part, we set up the values of our ancillary arrays:


```
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
```


We begin with a sanity check of the value of the parameter vertex number, *s*. Then, we establish three constants representing the vertex colors used by the algorithm: `WHITE`, `GRAY`, and `BLACK`, and create an array `pColor` to hold the colors of each vertex. 


Next, we provide initial values for the three arrays. The color of each vertex that is not *s* is set to `WHITE`, the distance from *s* to each vertex is set to infinity, and the predecessor value for each vertex is set to zero, an invalid vertex number representing the absence of a predecessor. 


Then, we set the values in these three arrays that we know before the algorithm proper begins. We know that the distance between *s* and *s* is zero, that there is no predecessor for vertex *s*, and that the color of vertex *s* is `GRAY`, since *s* is the only vertex we have "discovered" so far. 


Now that things have been set up, the next segment of the BFS code performs the actual searching. 


```
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
        for(AdjEntry v : *(pAdjacents[u])) {
            // add unexplored vertices to the queue
            if(pColor[v.v] == WHITE) {
                // color as "discovered but incomplete"
                pColor[v.v] = GRAY;
                // track distance from v to u so far
                pDist[v.v] = pDist[u] + 1;
                // v's predecessor is u
                pPred[v.v] = u;


                Q.push(v.v);
            }
        }
        // this vertex is completely explored
        pColor[u] = BLACK;
    }


    // free color tracking memory
    delete [] pColor;
}
```


We will use a STL `std::queue` object to keep track of gray vertices, so we add the starting vertex *s* to the queue. Note that the STL `std::queue` class unfortunately uses non-standard terminology for its queue operations: `push` is the enqueue operation, `front` gives a reference to the first element in the queue, and `pop` is the dequeue operation (which does not return the value of the item just dequeued). 


Next, we have a `while` loop that continues until there are no more gray vertices in the queue, i.e., until we have explored every vertex reachable from vertex *s*. 


Inside the loop, we dequeue the first element in the queue, and then use a `for` loop to iterate through that vertex's adjacency list. The loop


```
for(AdjEntry v : *(pAdjacents[u]))
```


is a by-item iteration through the selected adjacency list. `pAdjacents[u]` is a pointer to a list, so we dereference it. Then, `v` will take on the value of each `AdjEntry` object in the list, one after the other. 


Inside this loop, we check to see if each vertex is colored white:


```
if(pColor[v.v] == WHITE)
```


In the notation `v.v`, the first `v` is the current `AdjEntry` object, and `.v` selects the vertex number from that object. We use this as an index into the `pColor` array to determine the vertex's color. 


If the current vertex is white, it has just been discovered, so we update its color to gray, record its distance from *s* (which will be one more than the distance to the predecessor *u*), and record the predecessor in `pPred`. Then we add vertex *v* to the queue of gray vertices. 


After the `for` loop is complete, none of the vertices adjacent to *u* will still be white, and so we will change the color of vertex *u* to black. 


Once all of the gray vertices have been removed from the queue, the algorithm is complete. At this point, `pDist` and `pPred` are complete. 


#### Interpreting the distance and predecessor arrays


**[For this section, refer to the `module07/1-Graph/BFSDemo.cpp` file from the course's git repository.]**


In order to illustrate that the BFS algorithm works as advertised, and the see how to interpret the predecessor array, let's return to our sample undirected graph:


<img src="https://doane.instructure.com/files/987106/download?download_frd=1" alt="BFS sample graph" title="BFS sample grant"/>


Code in the `BFSDemo.cpp` file reads edge information from the file `undir.txt` to construct a `Graph` object containing the vertices and edges in the diagram. When the graph `g` is printed, we get a count of the vertices and edges (note - this is twice the number of lines, since we have to store one entry for each direction), and printouts of each vertex's adjacency list:


```
Graph has 8 vertices and 20 edges
Graph adjacencies:
1: [(2, 1), (5, 1), ]
2: [(1, 1), (6, 1), ]
3: [(6, 1), (7, 1), (4, 1), ]
4: [(3, 1), (7, 1), (8, 1), ]
5: [(1, 1), ]
6: [(2, 1), (3, 1), (7, 1), ]
7: [(3, 1), (4, 1), (6, 1), (8, 1), ]
8: [(4, 1), (7, 1), ]
```


Then, the code executes the BFS algorithm. The distances from vertex 2 to each of the other vertices are placed in `pDist`, and can be printed in a straightforward way:


```
Distance from 2 to 1: 1
Distance from 2 to 2: 0
Distance from 2 to 3: 2
Distance from 2 to 4: 3
Distance from 2 to 5: 2
Distance from 2 to 6: 1
Distance from 2 to 7: 2
Distance from 2 to 8: 3
```


We should look at the predecessors array `pPred` more carefully. If we started at vertex *u*, then `pPred[v]` is the first vertex in the *reversed* path from *u* to vertex *v*. `pPred[pPred[v]]` would be the second vertex in this reversed path. So, we can follow `pPred` entries until we reach vertex *u* to get the full path. The path-printing code in `BFSDemo.cpp` does this with a while loop, adding each successive vertex in the path to the *front* of a `std::list` object. Then, at the end, we can simply iterate through the list from front to back to produce the path in the correct direction: 


```
Path from 2 to 1: 2 1
Path from 2 to 3: 2 6 3
Path from 2 to 4: 2 6 3 4
Path from 2 to 5: 2 1 5
Path from 2 to 6: 2 6
Path from 2 to 7: 2 6 7
Path from 2 to 8: 2 6 7 8
```


The time complexity for our BFS algorithm is *O(|V| + |E|)*, that is, linear in terms of the number of vertices plus the number of edges in the graph. 


#### Dijkstra's algorithm


*Dijkstra's (DYKE-strəz) algorithm* performs the same function as the BFS algorithm, that is, it finds the shortest path from a single starting vertex to all the other reachable vertices in a graph, and the distances of those paths. But, Dijkstra's algorithm does this for a weighted graph. The higher the weight of an edge *(u, v)*, the more costly it is to get from vertex *u* to *v*.


Instead of a coloring scheme like the BFS algorithm used, Dijkstra's algorithm uses a conceptual *priority queue* to always add the vertex with the smallest distance to any of the vertices already discovered to the discovered set. A priority queue is like a normal queue, except that the smallest value is the element that is removed from the queue with each dequeue operation, rather than the element at the front of the queue. We cannot use the C++ `std::priority_queue` class, however, because the data that tells us which vertex should be removed from the queue first, the values in the `pDist` array, will be changing as the algorithm progresses. So, we will use a simple `std::list` as our "priority queue," and do a linear search each time we dequeue something, to remove the smallest element from the queue. 


The relevant code from the `Dijkstra` method is shown here, in two sections:


```
    // populate the "priority queue" with all vertices in the graph
    std::list<size_t> Q;
    for(size_t v = 1; v <= numV; v++) {
        Q.push_back(v);
    }
```


The first section creates and populates the `std::list` we will use as a priority queue. We simply place all of the vertices in the graph into the list `Q`.


The next section of the code uses a while loop to continue until the priority queue is empty: 


```
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


        // update distances and predecessors for the vertex we just removed 
        // from the "priority queue"
        for(AdjEntry v : *(pAdjacents[u])) {
            if(pDist[v.v] > pDist[u] + v.wUV) {
                pDist[v.v] = pDist[u] + v.wUV;
                pPred[v.v] = u;
            } // if
        } // for
    } // while 
```


We start by iterating through the list `Q` to find the smallest element in the list, keeping the iterator `uItr` updated so that it is always referencing the smallest list element we have seen so far. Note that the elements in the list are vertex numbers, but we make our "smallest value" decision based on the distances in the `pDist` array; those values will be in flux as the algorithm proceeds. Once we have an iterator to the smallest value in the list, we dereference `uItr` to get the vertex number `u`, and then remove the smallest value from the list. STL `std::list` objects have the `erase` method, which takes an iterator as a parameter and deletes the referenced value from the list.  


Then, we loop through all of the vertices adjacent to `u`, and if one of these provides a smaller distance, we update the distance and predecessor values. Once the priority queue is empty, we have completely explored the graph and can use the distance and predecessor arrays as we wish. 


The `DijkstraDemo.cpp` code constructs this weighted digraph:


<img src="https://doane.instructure.com/files/988072/download?download_frd=1" alt="Weighted digraph" title="Weighted digraph"/>


Note that since this is a directed graph, we do not include edges in both directions in the adjacency lists, as shown by the printout of the graph:


```
Graph has 5 vertices and 10 edges
Graph adjacencies:
1: [(2, 10), (4, 5), ]
2: [(3, 1), (4, 2), ]
3: [(5, 4), ]
4: [(2, 3), (3, 9), (5, 2), ]
5: [(3, 6), (1, 7), ]
```


The `Dijkstra` method fills the `pDist` array with the shortest distance from vertex zero to every other vertex, in terms of the weights of the edges in the path:


```
Distance from 1 to 1: 0
Distance from 1 to 2: 8
Distance from 1 to 3: 9
Distance from 1 to 4: 5
Distance from 1 to 5: 7
```


And, just as was the case for the `BFS` method, the `Dijkstra` method populates the `pPred` array with predecessors, so that we can build a vertex list of the shortest paths:


```
Path from 1 to 2: 1 4 2
Path from 1 to 3: 1 4 2 3
Path from 1 to 4: 1 4
Path from 1 to 5: 1 4 5
```


Given the way we implemented our min-priority queue, Dijkstra's algorithm has a time complexity of *O(|V|<sup>2</sup>)*. 


### Sample application: path finding


**[For this section, refer to the files in the `module07/2-PathFinding/` director from the course's git repository.]**


In this module's sample application, we will apply graph algorithms to a game application, where we want the game to determine the path that a non-player character (NPC) should use to get from one location to another, given a map with a variety of different terrain types. 


The map will be represented by a rectangular array of characters, where each character indicates a square tile made from a different substance:


c
: concrete. The NPC can easily cross a concrete tile in 1 unit of time.


s
: sand. The NPC can move across sand, but it takes 1.5 units of time to cross a sand tile.


w
: water. The NPC can move through water, but it takes 3 units of time to cross a water tile.


x
: impassible. The NPC cannot move through an impassible tile -- think of it like an unscalable wall. 


b 
: starting point. One tile on the map is marked with an s. This is where the NPC begins.


e
: ending point. One tile on the map is marked with an e. This is where the NPC should move to.


The NPC can move up, down, left, and right, but not diagonally. Our aim is to find the shortest path -- if one exists! -- from the starting point to the ending point. This is the path the NPC will follow during the game. 


A text file containing a sample map, `map.txt`, is in the sample application directory. It looks like this:


```
20 20
bcccsssssssxxxssssss
ccccsssssssxxxssssss
ccccsssssssxxxssssss
sssssssssssxxxssssss
sssswcsssssxxxssssss
ssswwwcsssssssssssss
sswwwwwcsssssswsssss
swwwwwwwcssssswsssss
ssswwwwwcssssswwssss
sssswwwcssssssswssss
ssssswcsssssswwwssss
sssssscssssswwwsssss
sssssscsssswwwwwssss
sssssscssswwwwwwwsss
sssssscxssswwwwwssss
sssssscxsssswwwsssss
sssssswxssssswssssss
ssssswwwxsssssssssss
sssswwwwwxssssssssss
ssswwwwwwwxcccccccce
```


The first line of the map file contains the number of rows and columns in the map. Then, the remaining lines of text specify the map tiles, given the types provided above. 


Of course, in a game, we would use the map file to create some graphical representation. Here's what this map might look like. Our NPC is visualized as a tiger, and the NPC's destination is visualized as a bell.


<img src="https://doane.instructure.com/files/988892/download?download_frd=1" alt="Path-finding map, visualized" title="Path-finding map, visualized"/>


In our application source file, `PathFinding.cpp`, we begin by converting the text of the map file into a graph representation. Given the rectangular arrangement of the tiles in our map, each vertex in the graph will have a maximum of four edges coming out of it. The vertices in the corners will have only two, and other vertices along the edges of the map will have three. The weights on the edges represent the amount of time taken to cross the tile. 


Once the graph has been built, we execute Dijkstra's algorithm to find the shortest path from vertex 1 (the upper left corner) to all of the other vertices in the graph. We really only care about the path to vertex 400 (the lower right corner), so we print that single path out:


```
Path from start to finish: 1 2 3 4 24 44 45 
46 66 86 87 107 108 128 129 149 169 170 190 
210 230 250 270 290 291 311 312 332 352 372 
392 393 394 395 396 397 398 399 400
```


This map shows a visualization of the path found by the algorithm. Note how the algorithm's path maximizes the amount of concrete tiles crossed by the tiger, while avoiding water and the impassible squares:


<img src="https://doane.instructure.com/files/988887/download?download_frd=1" alt="Path-finding map, solve" title="Path-finding map, solved"/>