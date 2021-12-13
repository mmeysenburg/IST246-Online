## More Overrides


In this assignment, you will add three more operator overrides for the `SLL` class. In particular:


Override the compound addition / assignment operator (`+=`) to work with `SLL<T>` objects. This operator adds an item of type `T` to the front of the list. For example, if `list` is an `SLL` containing integers, and it has the items `[1, 3, 5, 7]` already in the structure, then the statement 


```
list += 13;
```


would result in the list containing `[13, 1, 3, 5, 7]`. 


Override the compound subtraction / assignment operator (`-=`) to work with `SLL<T>` objects. This operator removes the first occurrence of an item from the list, if the item is in the list. For example, if `list` is an `SLL` containing double-precision floating point numbers, and it has the items `[1.2, 3.4, 5.6, 7.8, 9.0, 3.4]` already in the structure, then the statement


```
list -= 3.4;
```


would result in the list containing `[1.2, 5.6, 7.8, 9.0, 3.4]`.


Override the indexing operator (`[ ]`) to work with `SLL<T>` objects. This operator returns a reference to the indexed element, or throws a `std::out_of_range` exception if the specified index is not legal for the list. For example, if `list` is an `SLL` containing characters, and it has the items `['a', 'b', 'c', 'd', 'e']` already in the structure, then the statement


```
std::cout << list[1] << std::endl;
```


would print `b` on the standard output. Note: since this operator returns a *reference* to the specified element, it can be used to change the list contents. For example, the statement 


```
list[3] = 'Z';
```


changes the list contents to be `['a', 'b', 'c', 'Z', 'e']`. 


If we attempted to do `list[5] = 'Q';`, an `std::out_of_range` exception would be thrown, since 5 is not a legal index of an element in the list. 


### Files in the directory


`makefile` : makefile for building the `PA03Tests` unit test application, and the `PA03` main application.


`PA03.cpp` : simple application showing the workings of the three new operators.


`PA03Tests.cpp` : phantom main program file for making the `PA03Tests` unit test application.


`SLL.hpp` : copy of the singly-linked list class developed in this module. Modify this file to complete the assignment -- search for the `TODO` comments.


### Instructions


*[Note: the code for PA03 will not compile until you declare and implement the three overrides.]* 


1. Edit `SLL.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Write a Doxygen comment header for the `operator-=` override.


    b. Write the function declaration for the `operator-=` override.


    c. Write the Doxygen comment header for the `operator[]` override. 


    d. Implement the `operator+=` override.


    e. Implement the `operator-=` override.


    f. Implement the `operator[]` override.
    h. Built the project and execute the `PA03Tests' unit tests. Make sure they all pass.


2. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


3. Once the unit tests pass and the application produces the expected results, zip the entire `4-PA3` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.