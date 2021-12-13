## Module 3: An Improved Singly-Linked List


In this module, we will once again work on a singly-linked list. We will improve the data structure by *overriding* several operators so that the list "plays nice" with other C++ code. In particular, we will:


* override the stream insertion operator (`<<`), so that we can print our lists in the same way we print other objects in C++. Whenever we write a C++ class, if it makes sense to print objects of that type to the screen or write them to a text file, we should override the stream insertion operator. This is analogous to writing the `__str__` dunder method for a Python class we write, or the `toString` method for a Java class. 


* override the assignment operator (`=`) and provide a *copy constructor*, to allow users of our list to make an existing list be just like an existing one, or to make a new list just like an existing one. 


The former operator overload is for convenience, so that we can, say, use `std::cout` output with our list. The latter operator overload is more of a necessity, so that our list will behave as it should when used in our code, and so that lists can be passed to functions as parameters or returned from functions. We will confront an issue that occurs whenever we write data structures: should our code create a *shallow copy* or a *deep copy* of a data structure? 


From this point on, all of the data structures we examine will support stream insertion and assignment, and have copy constructors. 


### Stream insertion override


**[For this section, refer to the `module03\1-SLL\SLL.hpp` file from the course's git repository.]**


In our first singly-linked list, `SimpleSLL`, we had to call a method from a list object in order to print the list to standard output:


```
SimpleSLL<int> list;


// ... list is populated


list.print();
```


This is not how we usually print things in C++. Additionally, the `print` method is configured to *only* print values to the standard output; there is no easy, efficient way to print the contents of a `SimpleSLL` to a text file. We would rather be able to print our list in the usual way, *and* be able to print to a text file if we desire, like this:


```
std::ofstream outFile("out.txt");


// print to standard output
std::cout << list << std::endl;


// print to the file named 'out.txt'
outFile << list << std::endl;
```


We accomplish this by overriding the stream insertion operator (`<<`) so that the operator understands how to print our list. Let's examine how to do that. 


To differentiate between this version of the singly-linked list and the `SimpleSLL` structure of the previous module, this list is called `SLL`. The UML class diagram for the structure should be familiar to you, as it is very similar to the class diagram from the previous module. 


<img src="https://doane.instructure.com/files/904889/download?download_frd=1" alt="SLL UML class diagram" title="SLL UML class diagram"/>


You may notice that there is now an extra constructor in the class diagram (the copy constructor described below), an override for the assignment operator, and a private `copy` method. In addition, the `print` method has been removed, because we are replacing that limited functionality with the more versatile operator override. The stream insertion operator override does not appear in the UML because it is not a member of the class, but rather a friend function of the class. 


We override operators in C++ by writing methods that specify what to do when that operator is invoked on objects of our class. The name of the method is `operatorXX`, where `XX` is the operator we are overriding. So, to override stream insertion for our list, we write an `operator<<` method. Likewise, the assignment operator is overridden with the `operator=` method. 


Before turning to copy constructors and assignment operators, let's examine the stream insertion override. The following appears in the `SLL` class declaration, just before the private data is declared:


```
template <class T1> 
friend std::ostream &operator<<(std::ostream &out, const SLL<T1> &list);
```


We can understand this override better by looking at the declaration piece-by-piece. The first line says that this is going to be a template method, but notice that the type is `T1`, while the type for data in the overall `SLL` class is `T`. What's going on there?


Here is the explanation: Since the object on the left-hand side of the `<<` operator is an output stream (like `std::cout`) and *not* a `SLL` object, this operator override cannot be a part of the `SLL` class. To make the override able to efficiently print the values in the list, we want it to be able to access the private data (the pointers) of the `SLL` object being printed. So, we declare it to be a "friend" of the `SLL` class, with the `friend` keyword on the next line. Since it is not a class member, but is templated, we provide a different type name here. 


On the next line, we first make this override a friend of the `SLL` class. Then, we specify the return type of the overridden method: `std::ostream`. This allows us to chain the stream insertions, so that multiple values can be printed at once, like this:


```
std::cout << "My list is: " << list << std::endl;
```


Next, we have the name of the override method, `operator<<`. The parameter list contains two values, since `<<` is a binary operator. The first parameter, `out`, is a reference to a `std::ostream` object, representing the stream we are printing the list to. In all of the standard output examples we showed above, the actual parameter for this formal parameter is `std::cout`. 


The second parameter is a constant reference to the `SLL` object being printed. The `const` keyword for this formal parameter means that the method cannot change the values in the list. We include this as a safeguard against ourselves (and future maintenance programmers), because we do not want printing to change the values in the data structure. 


The implementation of the `<<` override is the last thing in the `SLL.hpp` file:


```
template <class T> 
std::ostream &operator<<(std::ostream &out, const SLL<T> &list) {
    out << "[";


    // initialize a cursor to the head of the list
    typename SLL<T>::Node *pCurr = list.pHead;


    // iterate until the end
    while (pCurr != 0) {
        out << pCurr->data;


        // output no comma for last element
        if(pCurr->pNext != 0) {
            out << ", ";
        } 


        // update cursor
        pCurr = pCurr->pNext;
    }


    out << "]";


    return out;        
}
```


Here, outside of the class declaration, the name we use for the template data type is not important, so we choose to return to using `T` again, instead of the `T1` we used inside the declaration. This code is virtually the same as the body of the `print` method in the `SimpleSLL` class. The only real difference is that we are using the name of the formal parameter, `out`, as the output stream to print to. 


### Deep versus shallow copies


**[For this section, refer to code in the `module03\2-CopyConstructor` directory in the course's git repository.]**


Suppose we create two instances of the previous module's `SimpleSLL` class:


```
SimpleSLL<int> list1;
for(int i = 0; i < 5; i++) {
  list1.add(i);
}


std::cout << "List 1: ";
list1.print();
std::cout << std::endl;


SimpleSLL<int> list2;
for(int i = 10; i < 20; i++) {
  list2.add(i);
}


std::cout << "List 2: ";
list2.print();
std::cout << std::endl;
```


At this point, we have two lists of integers, each with different lengths and values:


```
List 1: [4, 3, 2, 1, 0]


List 2: [19, 18, 17, 16, 15, 14, 13, 12, 11, 10]
```


Now, what happens when we do this?


```
list1 = list2;


std::cout << "List 1: ";
list1.print();
std::cout << std::endl;
```


The output makes it seem as if the assignment worked as we expected:


```
List 1: [19, 18, 17, 16, 15, 14, 13, 12, 11, 10]
```


But we actually have a problem! When the assignment happens, by default the C++ runtime copies the values of all of the fields in `list2` into the corresponding fields in `list1`. But what are these fields? There are only two fields in the `SimpleSLL` class: `pHead` and `n`. Therefore, the only things that change in `list1` are `pHead` and `n`. Consider this graphic depiction of the situation after the assignment:


<img src="https://doane.instructure.com/files/904906/download?download_frd=1" alt="SimpleSLL assignment memory leak" title="SimpleSLL assignment memory leak" />


So, via this assignment, we've actually done two things:


* we have created a memory leak, because the chain of `SimpleSLL::Node` objects that was originally in `list1` is still allocated, but not referred to by any pointer. The memory required to hold these nodes will remain allocated but unreachable for the duration of our program. If assignment code like this was in a loop, we could quickly exhaust the memory allocated to our application, causing a crash.


* we have created a *shallow copy* of `list2`. In other words, `list1` merely refers to the existing data in `list2`, rather than having new copies of all the values in the list. 


We usually don't want a shallow copy as the result of assignment between data structures. To see why, consider this code, which happens after the assignment above has taken place:


```
 for(int i = 0; i < 10; i++) {
    list2.set(i, 10 - i);
  }


  std::cout << "List 1 after List 2 is changed: " << std::endl;
  list1.print();
  list2.remove(0);
  std::cout << "List 1 after List 2 element removed: " << std::endl;
  list1.print();
  std::cout << "List 1 size: " << list1.size() << std::endl;
  std::cout << "List 2: ";
  list2.print();
```


The problem with a shallow copy becomes apparent when we look at the output:


```
List 1 after List 2 is changed: 
[10, 9, 8, 7, 6, 5, 4, 3, 2, 1]
List 1 after List 2 element removed: 
[0, 1]
List 1 size: 10
List 2: 
[9, 8, 7, 6, 5, 4, 3, 2, 1]
``` 


First, we see that changing `list2` via repeated calls to the `set` method seems to have also changed the values in `list1`. We only expect that behavior when one variable is an alias or reference to another. Things get worse when we remove the first element of `list2`. That changes the value of the `pHead` field in `list2`, but the value of `pHead` still refers to the former `list2` `pHead`, which now points to memory our application no longer owns. We get nonsensical -- and unpredictable -- results when we print `list1`, while the `list1` size is not accurate. `list2` is perfectly fine, but the shallow copy `list1` is a mess. 


What we really want the assignment operator to do is to create a *deep copy* of the list. That is, after the assignment, we want `list1` to have elements identical to `list2`, but without allowing changes to `list2` to impact the state of `list1`. To create this deep copy behavior, we will create a private `copy` method in our new `SLL` class, a copy constructor, and an override of the assignment operator, `=`.


### `copy` method


**[For this section, refer to the `module03\1-SLL\SLL.hpp` file from the course's git repository.]**


Both the copy constructor and the overridden assignment operator will take advantage of the private `copy` method described in this section. The method signature is in the private section at the end of the class declaration:


```
void copy(const SLL<T> &otherList);
```


We can see that the method does not have a return value, and that it takes one parameter: a constant reference to another `SLL` object. The goal of the method is to make the current list be just like the parameter, in a deep-copy manner. 


The code for the method itself looks like this:


```
template <class T> 
void SLL<T>::copy(const SLL<T> &otherList) {
    // remove any existing data
    clear();


    // initialize two cursors: one for this list, one for the other list
    Node *pCurr = pHead, *pOtherCurr = otherList.pHead;


    // iterate through the nodes in the other list
    while(pOtherCurr != 0) {
        // special case: the first node changes the head pointer
        if(pHead == 0) {
            pHead = new Node(pOtherCurr->data, 0);
            pCurr = pHead;
        } else {
            // general case: add new node to end of this list
            pCurr->pNext = new Node(pOtherCurr->data, 0);
            pCurr = pCurr->pNext;
        }


        // move to next node in other list, and increment our size
        pOtherCurr = pOtherCurr->pNext;
        n++;
    }
}
```


The first thing we do is remove any existing data in the current list, so that we do not have a memory leak. We do this via a call to the `clear` method. 


Next, we copy all of the data from the parameter `otherList` to the current list. One might be tempted to do this via a series of `add` method calls, like this:


```
Node *pCurr = otherList.pHead;
while(pCurr != 0) {
  this->add(pCurr->data);
  pCurr = pCurr->pNext;
}
```


While this is attractive because it reuses code that has already been written (`add`), it doesn't work. The problem is that the `add` method adds to the *front* of the list, rather than the back. So, if the values in `otherList` are `[1, 2, 3, 4]`, then the current list would be built like this:


* Add 1. The current list is now `[1]`.


* Add 2. The current list is now `[2, 1]`. 


* Add 3. The current list is now `[3, 2, 1]`.


* Add 4. The current list is now `[4, 3, 2, 1]`.


As you can see, if we were to use the `add` method in our `copy` method, we would end up with a reversed copy of `otherList`. So, we cannot just call `add` to copy the parameter list values into the current list.


So, our approach will be to have two cursor pointers, `pCurr` and `pOtherCurr`, which will point to the current node in the current and parameter list, respectively. Then, we have a `while` loop to iterate through the nodes of `otherList`. If `otherList` happens to be empty, the loop body never happens and the method ends, leaving this empty too.


If `otherList` does have elements, then the body of the loop does happen at least once. The first time, the `if` statement detects the special case situation and changes the value of the current list's `pHead` pointer to point to a new node containing a copy of `otherList`'s first element data. Otherwise, the general case happens, and we add a new node to the end of the current list, containing a copy of the corresponding elements from `otherList`. After the `if`, we update the size variable `n` and move `pOtherCurr` to the next element in `otherList`. The loop terminates when we have iterated through all of the elements in `otherList`. 


At the end of `copy`, the current list has been successfully made into a deep copy of the parameter `otherList`. 


An implementation note is in order here, related to unit testing. The way we are using our doctest unit testing framework, we are restricted to testing only public methods for the `SLL` class, since the testing code is not a part of the `SLL` class. Therefore, we cannot write a doctest unit test for the `copy` method, because `copy` is private. So, we rely instead on the fact that `copy` will be used by the copy constructor and overridden assignment operator. If those unit tests pass, we can be pretty sure that the `copy` method is working correctly. 


### Copy constructor


**[For this section, refer to the `module03\1-SLL\SLL.hpp` file from the course's git repository.]**


A *copy constructor* is used to create an instance of an object that is just like an existing object. Since we have already written the `copy` method, our copy constructor will be very easy to write:


```
SLL(const SLL<T> &otherList) : pHead(0), n(0u) { copy(otherList); }
```


We use the constructor's initialization list to set the initial values of `pHead` and `n`, and then call the private `copy` method to copy the contents of `otherList` over. The doctest unit tests for the copy constructor show how to use the copy constructor. If `list` is a populated `SLL<int>` object, then we can make identical deep copies like this:


```
SLL<int> list2(list1);
SLL<int> *pList = new SLL<int>(list1);
```


### Assignment operator override


**[For this section, refer to the `module03\1-SLL\SLL.hpp` file from the course's git repository.]**


The assignment operator override is almost as simple as the copy constructor. In the class declaration, we see the signature of the override:


```
SLL<T> &operator=(const SLL<T> &otherList);
```


The return type is a reference to the current list, so that we can chain together assignment operators, like this:


```
list2 = list3 = list1;
```


This code would make both `list2` and `list3` deep copies of `list1`. The code for the override is scarcely more complicated than the copy constructor:


```
template <class T>
SLL<T> & SLL<T>::operator=(const SLL<T> &otherList) {
    // copy other list contents to this object
    copy(otherList);


    return *this;
}
```


We perform the actual copying via the private `copy` method, and then return the dereferenced `this` pointer, i.e., the current `SLL` object. 


### Sample application: keyword search


**[For this section, refer to code in the `module03\3-KeywordSearch` directory in the course's git repository.]**


Our sample application in this module is a keyword search function, for a small number of motion pictures, using data from the [IMDb](https://www.imdb.com/) Web site. A text file, `movies.txt`, that contains information about several movies: their title, year of release, and several keywords that somehow relate to the plot of the movie. The first few lines of the file look like this: 


```
Godzilla vs. Kong
2021
kaiju
monsterverse
giant monster
monster versus monster
.
.
.
```


Our application (`KeywordSearch.cpp`) opens the file and creates a `SLL` of `Movie` objects that encapsulate the title, release year, and keywords for each movie in the file. The `Movie` class is simple, as shown in this UML class diagram:


<img src="https://doane.instructure.com/files/910658/download?download_frd=1" alt="Movie class diagram" title="Movie class diagram"/>


The only interesting aspect of this class is the override of the equality operator (`==`). Take a look at the declaration of the override in the `Movie.h` file:


```
bool operator==(std::string keyword);
```


You may notice that the right-hand side of the operator is a `std::string` object versus a `Movie` object. This is somewhat akin to comparing apples and oranges, but for this application it makes sense. We will define this equality operator to return `true` if the movie's keyword list contains the string in the `keyword` parameter. That way, we can iterate through a list of `Movie` objects, collecting all of them that match the keyword. 


The implementation of this override can be found in `Movie.cpp`:


```
bool Movie::operator==(std::string keyword) {
    return keywords.contains(keyword) != -1;
}
```


We use the `contains` method of the list, to see if the supplied keyword is in the list. If it is in the list, the return value will be an integer greater than or equal to zero; if the keyword is not in the list, the return value will be negative one. So, the Boolean expression `keywords.contains(keyword) != -1` is `true` if the keyword is in the list, `false` otherwise. 


The rest of the functionality for this application is in the `KeywordSearch.cpp` file. Two functions, `makeMovieList` and `makeKeywordList`, create the data structures used by the app. The former creates a list of `Movie` objects that we can search by keyword, while the latter creates a list of all the possible keywords, so they can be printed for the user. 


The heart of the application is the `findKeywordMatches` function:


```
SLL<Movie> findKeywordMatches(const SLL<Movie> &movies, std::string keyword) {
    SLL<Movie> matches;


    for(size_t i = 0; i < movies.size(); i++) {
        Movie m = movies.get(i);
        if(m == keyword) {
            matches.add(m);
        }
    }


    return matches;
}
```


The function takes two parameters: a reference to the list of movie objects to search, and a keyword to search for. The function returns a list of all the movies which contain that keyword.


Inside the function, we create an empty `SLL<Movie>` data structure, then populate it by iterating through all of the movies. We add every movie that matches the keyword parameter. This is where the `Movie` override of the equality operator is used, in the `m == keyword` Boolean expression. After the loop, we return the list containing all of the matching movies.


Note that this function would not work without our implementation of the assignment override for the `SLL` class! The `return matches` statement, without the assignment override, would do a shallow copy as the `matches` list is copied into the return value. This is problematic, because `matches` disappears when the function ends. Our main program would have a shallow copy list, with a head pointer pointing to memory that has been returned to the operating system. With the assignment override, the return value is a deep copy of the local list `matches`, and so when `matches` goes out of scope, the main program still has a copy of all the movies that matched the keyword. 


Another thing of note here is that this is not a particularly efficient piece of code, since the `SLL` `get(i)` method has to start at the beginning of the list and iterate through all of the nodes leading up to the element with index `i`. We will learn how to quantify the performance of our code in the next module, *and* we will introduce a new concept (iterators) that will allow us to perform a task like this more efficiently. 


The rest of the code in `KeywordSearch.cpp` is chiefly concerned with printing menus and responding to user input. We will not cover that code here, but feel free to examine it on your own. 


A sample execution of the application might go like this:


```
Select from one of the following options:
        1) Display the movies in our database
        2) Display a list of possible keywords
        3) Perform a keyword search of the database
        9) Exit the application
Enter selection: 1
        Predator (1987)
        Alien 3 (1992)
        Aliens (1986)
        Alien (1979)
        Postcards from the Edge (1990)
        Heartburn (1986)
        Silkwood (1983)
.
.
.
        Godzilla vs. Kong (2021)


Select from one of the following options:
        1) Display the movies in our database
        2) Display a list of possible keywords
        3) Perform a keyword search of the database
        9) Exit the application
Enter selection: 2
             name as title               name in title                         007
                     1940s              abusive mother                   acid burn
                acrophobia              action heroine        actor executive prod
                   actress                    adultery               airport apron


.
.
.
            worst director                 worst movie                      writer
       wrongful conviction       wrongful imprisonment              year 1831
                   z movie                      zombie               zombie attack


Select from one of the following options:
        1) Display the movies in our database
        2) Display a list of possible keywords
        3) Perform a keyword search of the database
        9) Exit the application
Enter selection: 3
Enter keyword: f rated
Movies matching f rated
        Black Widow (2021)
        Prizzi's Honor (1985)
        Silkwood (1983)
        Heartburn (1986)
        Postcards from the Edge (1990)


Select from one of the following options:
        1) Display the movies in our database
        2) Display a list of possible keywords
        3) Perform a keyword search of the database
        9) Exit the application
Enter selection: 9
```


In the next module, we will learn about how to analyze the *time complexity* of our code, and we will add one more element to our singly-linked list: an *iterator*.