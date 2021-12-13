## Random Poetry, Man


In this assignment, you will modify the `SimpleSLL` class so that it can be used in a random poetry program. When finished, the `RandomPoet` application will use a large dictionary of English words to slap together a series of random words into a "poem" of sorts. When complete, the program's output might look something like this:


```
Welcome to the random poetry generator!
Please wait while the dictionary is loaded.
Let's make some poetry, dude! Enter the number of lines: 4
Radical! Now, enter the number of words per line: 3


Here's your poem, man!


        variation's rigidness satisfying
        frisks rodeoing searches
        inveighs Berg snots
        entry crimper's arch


Would you like to make another poem? Enter 1 for yes, 0 for no: 1
Let's make some poetry, dude! Enter the number of lines: 3
Radical! Now, enter the number of words per line: 2


Here's your poem, man!


        laptop sentence
        Whitlock flysheets
        nasturtium's Reyna's


Would you like to make another poem? Enter 1 for yes, 0 for no: 0
```


You will find the files you need in the `module02-SimpleSLL\3-PA2` directory of the course's git repository. 


### Files in the directory


`dictionary.txt` : a file containing approximately 150,000 correctly-spelled English words, one per line. 


`makefile` : makefile for building the modified `SimpleSLLTests` unit test application, and the `RandomPoet` main application.


`RandomPoet.cpp` : main program for the `RandomPoet` application. Edit this file and search for the `TODO` comments.


`SimpleSLL.hpp` : simple singly-linked list for the application. Edit this file and search for the `TODO` comments.


`SimpleSLLTests.cpp` : phantom main program file for making the `SimpleSLLTests` unit test application.


### Instructions


Note: A pointer to a `mt19937_64` pseudo-random number generator has been added as a private field to the `SimpleSLL` class, and the constructor and destructor have been modified to allocate / free the object. Use this object, accessed via the `pPrng` pointer, to complete this assignment. In addition, unit test code has been written for the `getRandom()` method you will write. 


1. Edit `SimpleSLL.hpp` and search for the `TODO` comments. Complete the following tasks:


    a. Write a Doxygen comment header for the `getRandom()` method.


    b. Complete the code for the `getRandom()` method. Use the `pPrng` pointer and a `std::uniform_int_distribution<size_t>` object to pick a random index between 0 and `n` - 1, and then return that element from the list. 


    c. Built the project and execute the `SimpleSLLTests' unit tests. Make sure they all pass before moving on to the next step.


2. Edit `RandomPoet.cpp` and search for the `TODO` comments. Complete the following tasks:


    a. Complete the Doxygen header comments at the top of the program.


    b. Call the `getRandom()` method from the dictionary list, and print out the returned word, followed by a space, inside the poem-producing loop. 


3. Before submitting your code, execute the `make clean` command to remove the executables and any object files.


4. Once the unit tests pass and the application produces the expected results, zip the entire `3-PA2` directory and submit the resulting .zip file via this assignment.


### Grading


You will receive one point for the assignment if all the Pass criteria in the attached rubric are met; otherwise, you will receive zero points for the assignment.