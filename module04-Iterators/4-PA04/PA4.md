## Merging with iterators


Two lists, 


*L = {L<sub>0</sub>, L<sub>1</sub>, ... , L<sub>m</sub>}*


and 


*M = {M<sub>0</sub>, M<sub>1</sub>, ... , M<sub>n</sub>} 


can be merged pairwise to produce a new list


*{M<sub>n</sub>, M<sub>n−1</sub>, M<sub>n−2</sub>, ... , M<sub>m</sub>, L<sub>m</sub>, M<sub>m−1</sub>, L<sub>m−1</sub>, ... , M<sub>1</sub>, L<sub>1</sub>, M<sub>0</sub>, L<sub>0</sub>}*,


as long as list *M* is at least as long as list *L*, i.e., *n ≥ m*, where *n* is the size of list *M*, and *m* is the size of list *L*.  


For example, consider these lists:


*L: {1, 2, 3, 4}*


*M: {-1, -2, -3, -4, -5}*


*Merged: {-5, -4, 4, -3, 3, -2, 2, -1, 1}*


Modify the `IteratorSLL` class in the `4-PA04` directory to include a new constructor that takes two lists `L` and `M` as parameters and creates the new merged list. The new constructor should throw a `std::out_of_range` exception if the size of list `M` is not at least as large as the size of list `L`. You may use the provided unit tests and main program to test your new constructor. 


*Your new constructor should use iterators to iterate through L and M.*


### Files in the directory


`IteratorSLL.hpp` : File containing the `IteratorSLL` class. Modify only this file -- search for the `TODO` comments.


`IteratorSLLTests.cpp` : phantom main program file for making the `IteratorSLLTests` unit test application.


`makefile` : makefile for building the `IteratorSLLTests` unit test application, and the `PA04` main application.


`PA04.cpp` : simple application to exercise the merging constructor, using the data from the example above.


### Instructions


*[Note: the code for PA04 will not compile until you declare and implement the merging constructor.]* 


1. Edit `IteratorSLL.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Write a Doxygen comment header for the merging constructor.


    b. Write the declaration -- just the first line -- of the merging constructor.


    c. Write the definition of the merging constructor. 


    d. Built the project and execute the `IteratorSLLTests' unit tests. Make sure they all pass.


2. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


3. Once the unit tests pass and the application produces the expected results, zip the entire `4-PA4` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.