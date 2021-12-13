## Reversing a list


In this assignment, you will add a new method to our `DLL` class, `reverse`, with this signature:


```
DLL<T> reverse() const;
```


When called, the method creates and returns a new DLL with the same elements as the object the method was called from, but in reverse order. For example, if `list1` is a `DLL<int>` containing the values [9, 8, 2, 7, 3], then after the statement


```
DLL<int> list2 = list1.reverse();
```


the structure `list2` contains the values [3, 7, 2, 8, 9]. 


In addition to coding the `reverse` method, you will also be asked to write a doctest unit test to test the method. 


### Files in the directory


`DLL.hpp` : a copy of the `DLL` class developed in this module. This is the file you should modify for this assignment.


`DLLTests.cpp` : phantom main program file for making the `DLLTests` unit test application.


`makefile` : makefile for building the `DLLTests` unit test application, and the `PA05` main application.


`PA05.cpp` : simple application to exercise the new `reverse` method. 


### Instructions


*[Note: the code for PA05 will compile with the files as delivered, but with a warning. However, the `PA05` application will not run, and the `DLLTests` unit tests will not pass.]* 


1. Edit `DLL.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Complete the definition of the `reverse` method.


    b. Complete the doctest unit test for the `remove` method. The comments in the code offer you some guidance on how to test the method. Look at other doctest unit tests in the file -- they all begin with `TEST_CASE` -- for some inspiration. 


    d. Built the project and execute the `DLLTests' unit tests. Make sure they all pass.


2. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


3. Once the unit tests pass and the application produces the expected results, zip the entire `5-PA5` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.