## Removing the maximum value in a BST


In this assignment, you will add a new method to our `BST` class, `removeMax`, with this signature:


```
T removeMax();
```


When called, the method finds the largest element in the BST, removes its node, and returns the value. If the method is called on an empty tree, it throws a `std::out_of_range` exception. 


In this assignment, you will write `removeMax` and the doctest unit tests for the new method. Write the unit tests *first*, and then write your `removeMax` code. This is called *test-first development*. Test-first development is a good practice because it forces a developer to really understand the method she is going to write, before coding it. If you cannot write the tests for the method first, do you really understand what the method is supposed to do? 


### Files in the directory


`BST.hpp` : a copy of the `BST` class developed in this module. This is the file you should modify for this assignment.


`BSTTests.cpp` : phantom main program file for making the `BSTTests` unit test application.


`makefile` : makefile for building the `BSTTests` unit test application, and the `LastWord` main application.


`LastWord.cpp` : simple application to exercise the new `removeMax` method. This app loads the dictionary from the spell-checking app demo into a BST, then removes the last word (alphabetically) from the dictionary. 


### Instructions


*[Note: the code for PA06 will compile with the files as delivered. However, the `LastWord` application will not run, and the `BSTTests` unit tests will not pass.]* 


1. Edit `BST.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Complete the doctest unit test for the `removeMax` method. Look at other doctest unit tests in the file -- they all begin with `TEST_CASE` -- for some inspiration. 


    b. Complete the definition of the `removeMax` method.


    c. Build the project and execute the `BSTTests' unit tests. Make sure they all pass.


    d. Execute the `LastWord` application to see what the last word in the dictionary is. 


2. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


3. Once the unit tests pass and the application produces the expected results, zip the entire `3-PA6` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.