## Changing to a adjacency matrix representation


We mentioned in the Module 7 reading that there are two main options for representing a graph in our code: an adjacency list representation and an adjacency matrix representation. In the reading and the sample code, we used the adjacency list representation. In this assignment, you will convert our `Graph` class to use an adjacency matrix representation instead.


The original class had a pointer to an array of pointers to linked lists, so that the representation of this graph,


<img src="https://doane.instructure.com/files/987106/download?download_frd=1" alt="BFS sample graph" title="BFS sample graph"/>


would be eight lists, like this:


```
1: [(2, 1), (5, 1), ]
2: [(1, 1), (6, 1), ]
3: [(6, 1), (7, 1), (4, 1), ]
4: [(3, 1), (7, 1), (8, 1), ]
5: [(1, 1), ]
6: [(2, 1), (3, 1), (7, 1), ]
7: [(3, 1), (4, 1), (6, 1), (8, 1), ]
8: [(4, 1), (7, 1), ]
```


Each entry in a list is an `AdjEntry` object, with two numbers: the *v* component in an edge *(u, v)*, and the weight of the edge *(u, v)*. 


In the adjacency matrix representation, we will have a 2D array of doubles storing the weights of each edge. If there is no edge for a given row and column position, we will store an ∞. So, the adjacency matrix representation of the graph pictured above would be:


<img src="https://doane.instructure.com/files/988958/download?download_frd=1" alt="Adjacency matrix representation" title="Adjacency matrix representation"/>


We have an extra row and column because we start numbering vertices at one instead of at zero.


### Files in the directory


`BFSDemo.cpp` : the breadth-first demo application from the Module's reading. The app should find the same path as it did before once you've completed the assignment.


'DijkstraDemo.cpp` : the Dijkstra's algorithm demo application from the Module's reading. The app should find the same path as it did before once you've completed the assignment.


`dir.txt`, `undir.txt` : data files read by the demo apps.


`Graph.hpp` : copy of the graph code from the Module's reading. This is the file you should modify.


`GraphTests.cpp` : phantom main program file for making the `GraphTests` unit test application.


`makefile` : makefile for building the unit test and demo apps. 


### Instructions


*[Note: the code for PA07 will not compile with the files as delivered.]* 


1. Edit `Graph.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Write the constructor, to allocate a `(numV + 1) × (numV + 1)` array of doubles, `pMatrix`, that serves as the adjacency matrix.


    b. Write the destructor, to free the memory used by `pMatrix`. 


    c. Finish the implementation of the `addEdge` method so it uses the adjacency matrix implementation. 


    d. Modify the distance-adjusting code in the `Dijkstra` method so it uses the adjacency matrix implementation. 


    e. Modify the `numEdges` code so it uses the adjacency matrix implementation.


    f. Build the project and execute the `GraphTests` unit tests. Make sure they all pass.


    g. Execute the demo apps to verify that they find the same paths as before. 


2. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


3. Once the unit tests pass and the application produces the expected results, zip the entire `3-PA7` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.