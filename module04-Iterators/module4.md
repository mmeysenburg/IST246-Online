## Module 4: Iterators and Time Complexity


In this module, we will make one final modification to our singly-linked list data structure, to allow us to efficiently iterate through the list, from the outside of the list, without having access to the pointer structure of the list. We will do this by adding support for *iterators* to our list. 


In addition, our studies here will lead us into the concept of *algorithmic complexity*, or *time complexity*, and a mathematical concept called *asymptotic notation* or *order notation*.


### The need for iterators


Let us revisit the heart of the sample application from the previous module. If you recall, we used a `SLL` to hold a series of movie objects, and then searched the list for movies matching a given keywords, with this function:


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


What concerns us here is the amount of time taken by the `SLL::get` method, reproduced here:


```
T SLL<T>::get(unsigned idx) const {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in SLL::get()");
    }


    // initialize cursor
    Node *pCurr = pHead;


    // iterate cursor to position
    for(unsigned i = 0u; i < idx; i++) {
        pCurr = pCurr->pNext;
    }


    // return requested value
    return pCurr->data;
}
```


Unlike an array, we are not able to directly access element *i* of a list. Rather, we start at the head of the list (element 0), and then have to iterate through each element before $i$ in order to get to the proper location. 


This is a problem, especially if we have to repeatedly iterate through all of the elements of the list, as is the case with the movie keyword application. Abstractly, if there are *n* elements in the list, it takes 1 "step" to get to the first element of the list, 2 steps for the second element, 3 for the third element, and so on. This series of equations shows how many steps are required to iterate through the whole `SLL`:


<img src="https://doane.instructure.com/files/918445/download?download_frd=1" alt="Sum of integers 1 to n" title="Sum of integers 1 to n"/>


We see that an algorithm takes roughly *n<sup>2</sup>* steps to iterate through the *n* elements in the list, which is, frankly, unacceptable. To make a single trip through the list, we would like to spend only *n* steps in our algorithm. *If* we had access to the pointers and nodes of the `SLL` from the outside, we could try something like this:


```
SLL<Movie> findKeywordMatches(const SLL<Movie> &movies, std::string keyword) {
    SLL<Movie> matches;
    SLL<Movie>::Node *pCurr = movies.pHead;


    while(pCurr != 0) {
        Movie m = pCurr->data;
        if(m == keyword) {
            matches.add(m);
        }
        pCurr = pCurr->pNext;
    }


    return matches;
}
```


But this is also unacceptable. One of the principles of object-oriented programming is *encapsulation*. In encapsulation, and object hides its internal details from its users, so that the user of the object only has to know how to use the object, not how it works internally. Plus, now that you have worked with C++ for three modules, you can probably appreciate that working with pointers is tricky business. It is easy to accidentally do something really, really bad if you are not careful, and so we would prefer to keep the internal structure of the list (the pointers, especially) hidden from the user of the list. 


All is not lost! We can have linear-time traversal of our list without exposing the internal structure, by adding an iterator to the class. 


### Introducing the iterator


**[For this section, refer to the `module04\1-IteratorSLL\IteratorSLL.hpp` file from the course's git repository.]**


An *iterator* is an object we can use to efficiently iterate through the contents of a data structure, from outside the structure, without having access to the internal structure itself. We can think of an iterator as an encapsulated pointer, that lets us access the data at a particular location in the data structure, and advance to the next location, without actually touching the pointers in the structure. 


We define our `Iterator` class as an inner class of `IteratorSLL`, just as `Node` has been an inner class of our lists since Module 2. One difference is that `Iterator` will be a public inner class, while `Node` is a private inner class. `Iterator` is public because we want users of the `IteratorSLL` class to be able to access it, while `Node` is private because we do not want users to have access to the internal implementation of the list. 


This UML class diagram shows the methods and fields associated with the `Iterator` class:


<img src="https://doane.instructure.com/files/919348/download?download_frd=1" alt="Iterator UML" title="Iterator UML"/>


Working our way from the top to the bottom of the class diagram, we can see that there is one field in the `Iterator`: `pCurr`, a private-access pointer to a `Node` object. This is the pointer that the `Iterator` is designed to safely encapsulate. 


Next, there are four operator overrides in `Iterator`: dereferencing (`*`), equality (`==`), inequality (`!=`), and postfix increment (`++`). We will look at these shortly. 


The last item in the class diagram is the constructor, but note that it has private access. We do this so that users of our `IteratorSLL` cannot instantiate an `Iterator` on their own. Rather, users will get an iterator by calling methods from the `IteratorSLL` class. 


Let's take one more look at how we might implement the Module 3 movie keyword search function, but this time using our `IteratorSLL` that has an iterator.


```
IteratorSLL<Movie> findKeywordMatches(const IteratorSLL<Movie> &movies,
  std::string keyword) {


    IteratorSLL<Movie> matches;
    IteratorSLL<Movie>::Iterator i = movies.front();


    while(i != movies.end()) {
        Movie m = *i;
        if(m == keyword) {
            matches.add(m);
        }
        i++;
    }


    return matches;
}
```


We get an `Iterator` instance situated at the front of the list by calling the list's `front` method. Then, we have a loop that keeps going until the iterator has moved through all the list elements and reached the special end-of-list iterator, accessed via the list's `end` method. Inside the loop, we dereference the iterator via `*` to get the current movie, and then move to the next movie in the list via the postfix increment operator `++` at the end of the loop body. This traversal of the list using iterators takes *n* steps to traverse a list of *n* elements, without exposing the pointer structure of the list. 


### Implementing the iterator


Now that we have an idea of what an iterator is, why we want one, and how to use one, let us turn to the implementation of the iterator.


#### Iterator declaration


As we mentioned above, the `Iterator` class is a public inner class of the latest version of the singly-linked list, `IteratorSLL`. The list class, from a user's point of view, is only slightly different from the `SLL` class in the previous module, as we can see in its UML class diagram:


<img src="https://doane.instructure.com/files/923646/download?download_frd=1" alt="IteratorSLL UML class diagram" title="IteratorSLL UML class diagram"/>


There are two new methods: `end` and `front`, which return iterators to the end of the list and the first element in the list, respectively. We will examine these methods after we have inspected the implementation of the iterator itself. 


Internally, the `Iteraltor` inner class is declared in a public section of `IteratorSLL`, right after the `Node` class declaration. The `Iterator` class is reproduced here, with the comments removed:


```
class Iterator {
public:
    T &operator*();


    bool operator==(const Iterator &other) const {
        return pCurr == other.pCurr;
    }


    bool operator!=(const Iterator &other) const {
        return pCurr != other.pCurr;
    }


    Iterator &operator++(int dummy);


    friend class IteratorSLL;


private:
    Iterator(Node *pC) : pCurr(pC) { }
    Node *pCurr;
};


```


We declare four operators for use with our iterator:


`*`
: dereferencing operator. This operator allows us to get the value stored at a particular location in the list. If `i` is an iterator to a certain node in the list, then `*i` is a reference to the value stored in that node.


`==`, `!=`
: equality and inequality operators. These allow us to tell when we have reached the end of the list, e.g. for iterator `i` and a list named `list`, `while(i != list.end())` iterates until the end of the list is reached. These are defined here, since they are short functions. The functions compare the value of this iterator's node pointer with the node pointer of another iterator.


`++`
: postfix increment operator. This increments the iterator from one node to the next one in the list. The `dummy` parameter in the declaration is not involved in the operator, but serves simply to let the compiler know that we are overriding the postfix version (`i++`) of the operator instead of the prefix version (`++i`).


After the operator override declarations, we make the enclosing `IteratorSLL` class a friend of the `Iterator` class, so that the `front` and `end` methods will be able to access the private constructor. 


Note again that `Iterator` does not have a public constructor. This prevents users of the `IteratorSLL` class from instantiating an iterator themselves. Users of our list should not be allowed to do that, since creating an iterator requires a pointer to a list node, and we are trying to prevent list users from accessing the pointers. So, the `Iterator` constructor is declared in a private section. This way, users of `IteratorSLL` cannot build an iterator, but the `front` and `end` methods of the list, which can be trusted to access pointers, can access the private constructor, since `IteratorSLL` is a friend. The constructor does all of its work with the initialization list, so it has an empty body.


The last item in the `Iterator` class declaration is the pointer to a list node, `pCurr`. 


#### Iterator function definitions


The function implementations for the two remaining `Iterator` operator overrides occur later in the `IteratorSLL.hpp` file, after the class declaration. The dereferencing operator,


```
template <class T>
T &IteratorSLL<T>::Iterator::operator*() {
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Dereferencing beyond list end in "
                                "Iterator::*()");
    }


    return pCurr->data;
}
```


first checks to make sure that the iterator is referring to a valid node in the list. If not, a `std::out_of_range` exception is thrown. If the iterator *does* refer to an existing node of the list, we simply return a reference to the node's data element. 


The increment operator definition looks like this:


```
template <class T>
typename IteratorSLL<T>::Iterator 
    &IteratorSLL<T>::Iterator::operator++(int dummy) {
        
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Increment beyond list end in "
                                "Iterator::++()");
    }


    pCurr = pCurr->pNext;
    return *this;
}
```


The signature of this override is particularly long, so let's unpack it, one piece at a time, from left to right. First, we have the return type of the function, `typename IteratorSLL<T>::Iterator &`. The `typename` keyword here indicates that our intention is that the following piece of code is to be used as a type -- a reference to an iterator -- rather than being interpreted as the beginning of a function definition. 


Next we have the name of the function we are writing: `IteratorSLL<T>::Iterator::operator++`. This says we're overriding the `++` operator from the `Iterator` class, which is a nested class inside `IteratorSLL<T>`. 


Finally, we have the parameter for the function, `int dummy`. This parameter is not part of the operation of the operator, but it tells the compiler that this is the postfix `++`. If we left the parameter out, we would be overriding the prefix `++`, and would have to increment our iterator like this: `++i`. The operation would be the same, but we don't usually use the prefix version, so we take an extra step -- the dummy parameter -- to specify the postfix version. 


The code of the override itself first checks to see that the iterator refers to a node in the list. If not, a `std::out_of_range` exception is thrown. Provided the iterator refers to a list node, we advance the `pCurr` pointer to the next node in the list, and then return a reference to the iterator, via `return *this`. 


#### Iterator factory methods


In object-oriented programming, a *factory method* is a method that takes care of the details of creating an object. The method handles details that may be so complicated that the user is likely to implement them incorrectly, or encapsulates elements that the user should not be able to access. The `end` and `front` methods we have added to the `IteratorSLL` class are factory methods of this type. To create an iterator, we need to pass a pointer to a node into the iterator constructor, but we do not want users of the `IteratorSLL` class to have access to the pointers. So, these factory methods take care of that detail for users of the list. Since `end` and `front` are members of `IteratorSLL`, and since `IteratorSLL` is a friend of the `IteratorSLL::Iterator` class, `end` and `front` have access to the private constructor of the inner class, while users of the list do not have this access. 


Both factory methods are simple, one-line methods that are defined within the class declaration. The `end` method returns an iterator with a null pointer, which indicates an iterator that is one past the last node in the list:


```
Iterator end() const { return Iterator(0); } 
```


Similarly, the `front` method returns an iterator positioned on the first node in the list:


```
Iterator front() const { return Iterator(pHead); }
```


With the inner `IteratorSLL::Iterator` class, its overridden operators, and the `end` and `front` factory methods, we can now iterate through the list in an efficient way, without having access to the pointers in the list. 


### Introduction to time complexity analysis


**[For this section, refer to code in the `module04\2-TimeComplexity` directory from the course's git repository.]**


To begin this section, let's use an analogy. Suppose that you have a nicely-equipped home workshop, with a variety of hammers hanging on the pegboard on the wall. You are working on a project that requires a hammer. Which one should you choose to use for the project?  


The answer, of course, depends on the specific problem. If the problem is re-shingling your garage, the upholstery hammer will not be a good choice. One *could* drive roofing nails home with a tiny hammer meant to secure fabric to chairs, but it would take a really, really long time. Conversely, it's probably not best to re-upholster your favorite chair using a sledge hammer. 


Writing computer code is like that. Very often, you are solving a problem where many different data structures and / or algorithms would work. So, which one do you choose? All other aspects being equal, we should choose the data structure / algorithm that performs the best for the problem at hand. 


Let's make this a little more concrete. The `IteratorDemo` application uses two types of singly-linked lists, the `SLL`, which does not have an iterator, and the `IteratorSLL` list from this module, which does. It fills the lists with random content, and then iterates through the lists, doubling the value of each even element in the lists. In the `SLL` case, this involves repeated calls to the `get` and `set` methods, while in the `IteratorSLL`, iterators are used. The application is instrumented to count the number of iterations executed by loops in the process. All of this is repeated for several trials each over a variety of list sizes. This table shows the average number of iterations for each type of list, for the growing list sizes:


| n | `IteratorSLL` | `SLL` |
| --------- | --------- | --------- |
| 2 | 9.200000 | 4.800000 |
| 4 | 16.200000 | 14.000000 |
| 8 | 30.200000 | 53.600000 |
| 16 | 56.200000 | 182.800000 |
| 32 | 115.600000 | 782.000000 |
| 64 | 226.600000 | 3,118.600000 |
| 128 | 447.800000 | 12,002.000000 |
| 256 | 903.800000 | 50,305.000000 |
| 512 | 1,807.800000 | 200,964.800000 |
| 1,024 | 3,593.400000 | 789,832.000000 |
| 2,048 | 7,185.200000 | 3,175,102.600000 |
| 4,096 | 14,346.000000 | 12,591,860.400000 |
| 8,192 | 28,696.400000 | 50,495,155.000000 |
| 16,384 | 57,335.400000 | 201,158,548.400000 |
| 32,768 | 114,679.200000 | 805,699,603.200000 |
| 65,536 | 229,467.600000 | 3,224,056,432.000000 |
| 131,072 | 458,705.400000 | 12,882,819,611.799999 |
| 262,144 | 917,436.400000 | 51,521,863,499.199997 |
| 524,288 | 1,834,957.400000 | 206,144,820,050.399994 |
| 1,048,576 | 3,670,482.200000 | 824,815,857,548.199951 |


Both the `SLL` and the `IteratorSLL` lists are "hammers" to solve the problem, but given the numbers in this table, which one would you want to use? Clearly, `IteratorSLL` is far superior in terms of performance. 


In this section, we introduce *time complexity analysis* and *order notation*, which are mathematical tools we can use to determine and compare the performance of various algorithms. 


#### What *not* to do


First, it is important to realize that we should *not* simply use a stopwatch, or instrument our code with system timer calls, to measure the performance of an algorithm. Why not? 


Well, every piece of code that runs has to run on some computer, and there are many qualities of the computer itself that greatly influence how long the code takes to run. For example, the clock speed of the CPU, the amount of RAM in the machine, the speed of the non-volatile memory (spinning hard drive vs. SSD, e.g.), cache size, number of other programs running on the system, compiler settings when the code was compiled, and many other things will influence the speed of the algorithm. So, if I'm comparing algorithm A and algorithm B, both of which solve the same problem, I might run algorithm A on my laptop and my colleague might run algorithm B on her desktop. If algorithm B finishes first, does that mean it performs better than algorithm A? It's really hard to say, given all of the variables we've just mentioned. 


Therefore, what is needed is an abstract way to determine the algorithm's performance, that is divorced from all of the "real world" influences that might cause the algorithm to run faster or slower. 


#### Counting fundamental operations


Our abstract measure of an algorithm's performance is called the algorithm's *time complexity.* To measure an algorithm's time complexity, we do not need an actual computer at all; rather, all we need is pseudocode for the algorithm and some mathematical sophistication. The process of determining an algorithm's time complexity is called *time complexity analysis.*


First, we need an abstract measure of the size of the input to the algorithm. For example, if the problem we're trying to solve is the movie keyword search from the previous module, the input size is the number of movies we have to search through. We let the input size be represented by the variable *n*. 


Next, we find a *fundamental operation* in our algorithm. A fundamental operation is one that is executed proportionally to the total amount of "work" done by the algorithm. For example, let's examine a simple pseudocode algorithm for performing a linear search on an array of integers:


```
1  int linearSearch(int *pArr, int n, int key) 
2    for(int i = 0; i < n; i++)
3      if(pArr[i] == key)
4        return i
5    return -1
```


The numbers at the beginning of each line are merely line numbers, they are not part of the algorithm. The algorithm searches an array `pArr`, of size `n`, for the element `key`. If `key` is in the array, the algorithm returns the index of the first occurrence of `key`. If `key` is not in the array, the algorithm returns -1, a flag value indicating the not found situation. 


In selecting a fundamental operation for this algorithm, we want something that happens proportional to the amount of work done by the algorithm. In this case, the search algorithm may have to look at every element in the array before finding the key or determining if it is not in the array. So, we want to select a statement in the algorithm that is executed at least once for every search operation made by the algorithm. Let's consider a few statements from the algorithm and see if they are appropriate fundamental operations.


Nothing in the signature (line 1) of the algorithm is a good fundamental operation, because each piece (the parameters passed in, or the return value going out) only happens one time, regardless of the size of the array. Clearly, this is not proportional to the amount of work done by the algorithm. 


One might say the `for` loop in line 2 is a fundamental operation, but we would need to be more specific, because not every part of the loop header is appropriate. The initialization, `int i = 0`, only happens one time, so it is not an appropriate fundamental operation. However, the loop condition `i < n` and the increment `i++` both happen once for each iteration of the loop, so they would be good choices for fundamental operations. 


The comparison in line 3, `pArr[i] == key`, is an excellent choice for a fundamental operation. It really is the whole purpose of the algorithm, boiled down to a single Boolean expression. 


Either of the return statements, `return i` in line 4 or `return -1` in line 5, are not good candidates for a fundamental operation, since they each happen only at most one time, regardless of the size of the array. 


So, let's say that we select the Boolean expression `pArr[i] == key` as our fundamental operation. Our next step is to write a mathematical function that expresses how many times the expression is evaluated during a search, in terms of the array size, `n`. 


Before we come up with such a function, however, we need to consider one more thing: will the time complexity of this algorithm be the same every time for an input of size `n`, or will it vary depending on other characteristics of the input? 


#### Every-case, or best / worst average?


Before we express our number of fundamental operations as a function of `n`, we need to decide if the algorithm has *every-case* time complexity, or *best-*, *worst-* and *average-case* time complexity. 


If the number of fundamental operations executed depends on the specific contents of the input, as in the linear search algorithm above, then the algorithm has best-, worst-, and average-case complexity. For linear search, the best-case situation happens when the key value is in the first element of the array. In that case, the fundamental operation happens only once. On the other hand, if the key value occurs first as the last element of the array, or if the key value is not in the array at all, then the fundamental operation happens `n` times. Those are the best- and worst-case complexities, respectively. Average-case is more complex to evaluate, but we will come to an intuitive conclusion for that situation in the next section.


Not every algorithm behaves differently when the contents of the input vary. Consider this algorithm, that counts the number of even integers in an array:


```
1 int countEvens(int *pArr, int n) 
2   int sum = 0
3   for(int i = 0; i < n; i++) 
4     if(pArr[i] % 2 == 0)
5       sum++
6   return sum
```


To evaluate the time complexity of this algorithm, we first have to decide on our fundamental operation. There are three possible options for fundamental operation: the `i < n` and `i++` in the loop header (line 3), or the `pArr[i] % 2 == 0` Boolean expression in the if statement (line 4). Let's use the Boolean expression.


So, how many times is the Boolean expression executed for an input of size `n`? Well, since the algorithm *has* to look at each item in the array, so that it doesn't miss any even numbers it should count, the expression is *always* executed `n` times, regardless of the contents of the array. In other words, if the array contains no evens, one even, or `n` evens, the algorithm still has to look at each and every element of the array to do its work. Since it does the same amount of work regardless of input contents, this algorithm has every-case time complexity. 


Once we know if we are dealing with every-case or best / worst / average-case time complexity, we can express our fundamental operation count as a function of input size. 


#### Expression fundamental operations as a function


When input contents cause the algorithm to take different amounts of time, we use functions B(n), W(n), and A(n) for best, worst, and average-case time complexity. For the linear search algorithm, and the `pArr[i] == key` fundamental operation, these functions are easy to determine:


<img src="https://doane.instructure.com/files/961784/download?download_frd=1" alt="Linear search time complexities" title="Linear search time complexities"/>


The average-case time complexity is difficult to determine, without using a significant amount of advanced mathematics, including quite a bit of probability. This type of mathematical work is beyond the scope of this course, so we will not develop the *n/2* answer here. However, intuitively, the *n/2* answer makes sense: on average, we would expect to have to go through about one-half of the array before we find our key value. Due to the difficulty of determining average-case time complexity without digging into some deeper mathematics, we will not worry about average-case complexity from here on out. 


When the algorithm takes the same amount of time regardless of the input contents, we express every-case time complexity as the function T(n). For the algorithm to count the number of even values in an array, the `pArr[i] % 2 == 0` fundamental operation is executed 


<img src="https://doane.instructure.com/files/961798/download?download_frd=1" alt="Count-evens time complexity" title="Count-evens time complexity"/>


#### Time complexity functions are usually uglier than that


The linear search and count-evens algorithms were chosen specifically for introducing the idea of time complexity functions. Generally speaking, calculating time complexity functions is more difficult than these two examples might imply. To get a taste of the complexity in computing time complexity, consider the following Bubble Sort code, which will arrange an array of integer values into increasing order:


```
void bubbleSort(int *pArr, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(pArr[j] > pArr[j + 1]) {
                std::swap(pArr[j], pArr[j+1]);
            }
        }
    }
}


```


Bubble Sort got its name for the way larger elements are "bubbled" to the right side of the array with each succeeding pass. The details of the sort are not what we're really interested in here, though. Rather, we want to look at the time complexity of the algorithm. We will use the Boolean condition in the if statement, `pArr[j] > pArr[j + 1]`, as our fundamental operation. 


First, we should note that this is an every-case situation; there is nothing in the code that exits the loops early. Second, note that we have two *nested* loops, where each loop depends on the value of `n`. We can count how many times the fundamental operation happens for each iteration of the outer loop, like this:


| `i` | `j` values | # f.o.'s |
| --------- | ---------- | --------- |
| 0 | 0, 1, 2, ..., n - 2 | n - 1 |
| 1 | 0, 1, 2, ..., n - 3 | n - 2 |
| 2 | 0, 1, 2, ..., n - 4 | n - 3 |
| ... | ... | ... |
| n - 2 | 0 | 1 |


Now, "all" we need to do is add up all of the fundamental operations in the third column. We can use a mathematical identity from the field of combinatorics (the mathematics of counting), and some simple algebra, to see that 


<img src="https://doane.instructure.com/files/961874/download?download_frd=1" alt="Bubble sort time complexity" title="Bubble sort time complexity"/>


Our every-case time complexity for Bubble Sort is on the order of *n<sup>2</sup>*. 


The more complicated our algorithms become, the more difficult it is to get exact time complexity functions. Luckily, there are some shortcuts we can use to know time complexity without having to do the math. 


Algorithms that have non-nested loops depending on the input size, will have every-case or worst-case time complexity on the order of *n*. Algorithms that have two nested loops, each depending on the input size, will have every-case or worst-case time complexity on the order of *n<sup>2</sup>*.


An extra wrinkle that can complicate our thinking is "hidden" time complexity. Consider again the `SLL` movie code from the previous module:


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


On first glance, this looks like it would run with time complexity on the order of *n*, since there is a single loop that depends on the input size. However, we know that the `get` method involves a for loop, that in the worst case, has to iterate through all of the elements in the list. So, in fact, this algorithm takes on the order of *n<sup>2</sup>* time. 


#### Asymptotic notation


You may have noticed that we have been using the phrase "on the order of" when talking about time complexities. When we work with time complexity, we want to focus on the parts that matter the most, while ignoring small details that might get in the way of our understanding. We do this with *order notation*, in particular *Big-O* notation. 


Given a time complexity function, we apply Big-O notation by finding the fastest growing term in the function, and ignoring all other terms, including constants. For example, here are the Big-O notations for a variety of time complexities from this module:


<img src="https://doane.instructure.com/files/961883/download?download_frd=1" alt="Big-O time complexities" title="Big-O time complexities"/>


The *∈* symbol is a set membership sign, read mathematically as "is a member of," or in our situation, as "is." We use this rather than the equals sign because an entry like *O(n)* is a set of functions rather than one function. For an every-case time complexity *T(n)*, we read an entry like


<img src="https://doane.instructure.com/files/961925/download?download_frd=1" alt="T(n) is Big-O of n squared" title="T(n) is Big-O of n squared" />


as "T of n is Big-O of n squared." 


By focusing on the fastest growing term in a time complexity function, we see what really matters, without getting bogged down in small details. Here are some more examples of applying Big-O notation to a variety of functions:


| Function | Big-O |
| ---------- | ---------- |
| *f(n) = 13245* | *∈ O(1)* |
| *f(n) = 13000n - 109* | *∈ O(n)* |
| *f(n) = n<sup>2</sup> + 13n - 10000* | *∈ O(n<sup>2</sup>)* | 
| *f(n) = 13n<sup>2</sup> - 20n + 10* | *∈ O(n<sup>2</sup>)* |
| *f(n) = n<sup>3</sup> - 20n<sup>2</sup> - 100* | *∈ O(n<sup>3</sup>)* |


Remember our notion of applying Big-O: focus on the fastest growing term in the function, and ignore everything else, including constants. 




### Categorizing algorithms by complexity


Previously we have seen that we can use Big-O notation to simplify time complexity functions. Another benefit of using Big-O is that with it, we can classify algorithms by their complexities. For example, the linear search algorithm in the worst case, and the count-evens algorithm in every case, are *linear* algorithms, that is, *∈ O(n)*. Many simple sorting algorithms, such as the Bubble Sort, Insertion Sort, and Selection Sort, are all *quadratic* algorithms, *∈ O(n<sup>2</sup>)*. More sophisticated sorting algorithms, such as Heap Sort, Merge Sort, and Quick Sort, are *linear-logarithmic* algorithms, *∈ O(n log<sub>2</sub> n)*. We generally consider quadratic algorithms to be the slowest algorithms we're willing to tolerate, especially for large sizes of *n*. 


The following table lists a variety of Big-O time-complexity categories, from fastest to slowest. A facetious, but accurate, third column gives you a way to remember each category. 


| Big-O set | Name | Facetious Name |
| ---------- | ---------- | ---------- |
| O(1) | Constant time | Oh, yeah |
| O(log n) | Logarithmic time | Oh, nice |
| O(n) | Linear time | Oh, OK |
| O( n<sup>2</sup> ) | Quadratic time | Oh, my |
| O( 2<sup>n</sup> ) | Exponential time | Oh, no |
| O(n!) | Factorial time | OMG | 


### Sample application: evaluating PRNG quality


In the sample application for this module, we will perform a simple quality test on three *pseudo-random number generators* (PRNGs). As programmers, we use PRNGs in a variety of applications, from generating test data to gaming and simulations. If we are using code simulations as part of scientific research, or for cryptographic purposes, it is important that the PRNG we use is of high quality, that is, produces a sequence of values that appears to be random. 


There are many, many such tests. For this demo, we will use the *monobit* test from the (NIST Statistical PRNG Test Suite)[https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf]. This test takes a large number of pseudo-randomly generated values, and this is where our `IteratorSLL` class comes in. We will use one of these lists as a container to hold a large number of pseudo-randomly generated integers, provided as input to the monobit test. The fact that the list has iterators allows the monobit test code to efficiently move through the list, in linear time, to perform its work. 


This application tests three PRNGs, of varying quality: 


RANDU
: [RANDU](https://en.wikipedia.org/wiki/RANDU) is a tragically flawed generator that shipped on IBM mainframe computers in the 1960s and early 1970s. 


minstd_rand0
: [minstd_rand0](https://en.cppreference.com/w/cpp/numeric/random) is a "Minimum standard" generator, created by Lewis, Goodman and Miller in 1969. 


mt19337_64
: [mt19937_64](https://en.cppreference.com/w/cpp/numeric/random) is a high-quality, 64-bit "Mersenne Twister" generator, created by Matsumoto and Nishimura in 2000. 


First, let's examine the monobit test code:


```
double monobit(const IteratorSLL<int> &numbers) {
    double S = 0.0;


    // iterate through all values
    IteratorSLL<int>::Iterator i = numbers.front();
    while(i != numbers.end()) {
        // assuming 32-bit integers here
        unsigned mask = 0x00000001;


        // sum up zeroes / ones according to the NIST monobit test
        for(int j = 0; j < 32; j++) {
            int v = *i;
            S += (v & mask) == 0x00000000 ? -1.0 : 1.0;
            mask <<= 1;
        }
        i++;
    }


    // compute P-value according to the NIST monobit test
    double stat = abs(S) / sqrt(numbers.size() * 32.0);
    double PValue = erfc(stat / sqrt(2.0));


    return PValue;
}
```


The parameter to the function is a reference to the linked list containing the pseudo-random numbers to be evaluated. The code iterates through all the values, and performs a kind of running sum on the number of zeroes and ones seen in the binary expressions of the integers in the list. Every zero encountered adds -1 to the sum, while every one adds 1 to the sum. After the sum is calculated, a probability (P-value) is calculated and returned, representing the confidence level that the numbers appear to be random. A return value less than 0.01 means that the numbers in the list appear to be non-random. 


The main program populates a singly-linked list with each of the generators listed above, then executes the monobit test on the list. Here is the section that tests the Mersenne Twister PRNG:


```
// test the Mersenne Twister PRNG
for(int i = 0; i < n; i++) {
    int v = dist(mtPRNG);
    randInts.add(v);
}
double PValue = monobit(randInts);
std::cout << "Mersenne Twister monobit: " << PValue << std::endl;
```


A block very much like this is included for each of the three generators. 


When executed, we find that the minimum standard PRNG and the Mersenne Twister provide acceptable results, while RANDU is disastrously bad:


```
Mersenne Twister monobit: 0.918164
Minimum standard monobit: 0.397357
RANDU monobit: 0
```


Of course, when you run the code, your numbers will vary, due to the very nature of pseudo-random number generation.