## Module 2: A Simple Singly-Linked List


In this module, we will introduce our first data structure, a simple *singly-linked list*. This list will be composed of a series of noces, each linked to the next by a single pointer. We will start, however, with a general discussion of a list, and then turn our attention to the algorithms and implementations of the singly-linked structure.


### General list characteristics


Before we delve into the structure and C++ implementation of our first data structure, let's take a moment or two to discuss the general characteristics of a list. 


#### A list is a linear structure


Lists are *linear*, i.e., shaped like a line. Each element in the list, except for the first list, has a unique predecessor, and each element, except for the last, has a unique successor. When we draw a list, we typically draw the elements from left to right, with the first element of the list on the left side and the last element on the right side. For example, we might have a list of five character elements like this:


<img src="https://doane.instructure.com/files/896960/download?download_frd=1" alt="5 element list" title="5 element list"/>


The character 'H' is the first character in the list, and so it has no predecessor, i.e., no character is to the left of 'H'. 'D' is the last character in the list, so it has no successor, i.e., no character is to the right of 'S'. The element in the middle, 'N', has a predecessor, 'S', and a successor, 'A'. Each element has an index associated with it, letting us know how far from the left each is. 


#### List size is dynamic


The *size* of a list is the number of elements in the list. In a list data structure, the size of the structure is *dynamic*, i.e., the size varies over time as elements are added to and / or removed from the list. In the character list above, the size is five. 


There may be some maximum size for the list, called the *capacity* of the list, depending on the underlying implementation of the data structure. In that situation, the size of the list is quite frequently less than the capacity of the list, meaning that one or more slots in the list are unused, and therefore wasted memory. For example, if we have the following, 


<img src="https://doane.instructure.com/files/896961/download?download_frd=1" alt="List with size 5, capacity 10" title="List with size 5, capacity 10"/>


The size of the list is still five, but the capacity of the list is 10, because there is room to store a total of 10 elements. 


We will implement our singly-linked list in such a way that there is no capacity, other than the amount of memory our program is allowed to access by the operating system. In addition, our list will never waste space; there will never be any unused memory in the list. 


#### There is no implied order in a list


Our singly-linked list will be constructed in such a way that there is no particular order of the elements in the list, other than the sequential, one-after-the-other ordering implied by the list's linear structure. In other words, the elements in the list do not have to be in sorted order, or any other particular order. 


### List operations


Now, let's turn to the operations we can perform on our list. Again, we are speaking here of an abstract list, apart from the actual underlying implementation of the structure. Consider this UML class diagram of the SimpleSLL class, and only pay attention to the `SimpleSLL<T>` class. The inner `SimpleSLL::Node<T>` class is an artifact particular to the linked list implementation we will discuss below.


<img src="https://doane.instructure.com/files/896962/download?download_frd=1" alt="SimpleSLL UML" title="SimpleSLL UML"/>


As you will recall from the `Coordinate` class in Module 1, the `<T>` portion of the class names indicates that this is a template class, i.e., a data structure that can hold any kind of data, whether it be `int`, `double`, `string`, or any other primitive or object type.


The UML shows us that there are methods for creating and destroying the list (the constructor and destructor), methods that change the state of the list (`add`, `clear`, `remove`, and `set`), and methods that observe the state of the list (`contains`, `get`, `isEmpty`, `print`, and `size`). Before digging into the implementation details, here are descriptions of what each of these methods do.


#### Constructor and destructor


In C++, the *constructor* is a special method used to initialize an object. The constructor is always named the same as the class, so our constructor is called `SimpleSLL`. This method will create an initially empty list -- a list with size zero.


The *destructor* is a special method called automatically whenever an object is going to be destroyed. In this course, destructors are used to free any dynamically-allocated memory that the data structure has allocated with the `new` keyword. C++ destructors are named the same as their class, but with a `~` prefix, so our destructor for this class is named `~SimpleSLL`.


#### Operations that change the state of the list


The following `SimpleSLL` methods change the state of the list when they are called: `add`, `clear`, `remove`, and `set`. 


The `add` method adds a new element to the list, and it *always* adds that element at the beginning of the list. For now, there is no other way to add new elements to the list. For example, suppose we add {1, 2, 3, 4, 5} to an initially-empty `SimpleSLL`, in that order. The list would look like this at each insertion:


```
1
2 1
3 2 1
4 3 2 1
5 4 3 2 1
```


The `clear` method safely removes all of the elements from the list, freeing up any dynamically-allocated memory formerly used to store the elements. 


The `remove` method removes an element from the list, based on its index. Suppose we have the five-element list of characters we looked at above, and suppose the list is named `myList`:


<img src="https://doane.instructure.com/files/896963/download?download_frd=1" alt="5 element list" title="5 element list"/>


Then, the call `myList.remove(1)` would remove the 'S' from the list, and somehow "shuffle" the elements over, so that the list looks like this:


<img src="https://doane.instructure.com/files/896964/download?download_frd=1" alt="List after removing element 1" title="List after removing element 1"/>


With the `remove` method, and any other method that takes an index as a parameter, the method will throw an exception if the index is not valid for the current state of the list. For example, if `myList` list has the original five elements, `myList.remove(5)` would throw an exception, because there is no element at index 5. 


The `set` method allows us to change the value of an existing element in the list. For example, if we have the original, five-element list `myList`, the method call `myList.set(3, 'Q')` would modify the list to look like this:


<img src="https://doane.instructure.com/files/896965/download?download_frd=1" alt="List after modifying element 4" title="List after modifying element 4"/>


As for the `remove` method, the `set` method will throw an exception if the index is not a legal index for any element in the list. 


#### Operations that observe the state of the list


The following `SimpleSLL` methods do not change the state of the list when they are called, but merely tell us something about the elements in the list: 
`contains`, `get`, `isEmpty`, `print`, and `size`.


The `contains` method allows us to search a `SimpleSLL` object for a value. If the value is in the list, `contains` returns the first index where the value occurs. If the value we search for is not in the list, `contains` returns -1. For example, given the original 5-element `myList` referenced above, the method call `myList.contains('A')` returns 3, while `myList.contains('Z')` returns -1. 


The `get` method returns the value stored at a particular index in the list. For example, for our list of characters, `myList.get(3)` returns 'A', `myList.get(0)` returns 'H', and `myList.get(10)` would throw an exception, because there is no element with index 10 in the list. 


`isEmpty` is a convenience method that returns `true` if the list has no elements, or `false` if the list has one or more elements. 


The `print` method causes the elements of the list to be printed to the standard output, in order from left to right. The method will enclose the output values in square brackets, and separate them with commas. In future versions of the list data structure, we will override the stream insertion operator, `<<`, so that we can print the list directly, without calling the `print` method. 


The `size` method returns the number of elements in the list, i.e., the list's size. 


### List implementation


By this point, we should have a fairly good understanding of what a list can do, from the point of view of someone using the class. Now it is time to turn our attention to the algorithms and code that we use to actually make it work. 


#### Linked list basics


The fundamental building block of our singly-linked list is the `Node` class. A node is a container capable of storing one value, and with the capability to be linked to the next `Node` in the list. We visualize our node like this:


<img src="https://doane.instructure.com/files/896966/download?download_frd=1" alt="SimpleSLL Node class" title="SimpleSLL Node class"/>


As you can see, there are two parts to the node: its "payload," `data`, and a pointer to the next `Node` object in the list, `pNext`. If this node is the last one in the list, its `pNext` field will have the value `0`. 


In a singly-linked list, we chain `Node` objects together, like this:


<img src="https://doane.instructure.com/files/896967/download?download_frd=1" alt="3 chained nodes" title="3 chained nodes"/>


Pulling together the rest of the detail in the `SimpleSLL` UML class diagram above, we see that the list has two fields: `n`, which will always hold the size of the list, and `pHead`, a pointer to the first `Node` in the list. Putting all of this together, a `SimpleSLL` object holding three characters, 'A', 'B', and 'C', might be diagrammed like this:


<img src="https://doane.instructure.com/files/896968/download?download_frd=1" alt="3 node linked list" title="3 node linked list"/>


When we process the list, we will start at the beginning of the list -- the node at the end of the `pHead` pointer -- and then go down the list, one node at a time, following each `pNext` pointer in turn. When a node's `pNext` pointer has a value of zero, we know we have reached the end of the list. For example, suppose we want to print out the value stored in each node of the list. This pseudocode illustrates the "visit every node" pattern we will often use:


```
Node *pCurr = pHead
while (pCurr != 0)
  print(pCurr->data)
  pCurr = pCurr->pNext
```


We often call a pointer used to traverse a data structure, like `pCurr` here, a *cursor*. 


The nodes and pointers of the list are hidden from the user of the data structure -- for good reason! If we exposed the nodes or pointers, what would happen if the `pNext` value of the first node was accidentally set to zero? Well, we would be able to get to the first node, via `pHead`, but after that, the rest of the nodes in the list would be inaccessible. Likewise, accidentally changing `pHead` incorrectly could result in a memory leak and inaccessible list elements.


#### The `SimpleSLL` class


**[For this section of the reading, refer to the sample code in the module02-SimpleSLL/1-SimpleSLL directory of the course's git code repository]**


Now, at long last, we can look at some of the C++ implementation details of the `SimpleSLL` class, which is contained entirely in the `SimpleSLL.hpp` file. 


##### The inner `Node` class


The first part of the class is the private `Node` class, excerpted here sans the Doxygen comments:


```
class Node {
public:
    Node() : data(), pNext(0) { }


    Node(const T &d, Node *pN) : data(d), pNext(pN) { }


    T data;


    Node *pNext;
};


```


The `Node` class is set to private so that users of the `SimpleSLL` structure cannot create them, since they are only for internal usage. Every part of the `Node` is public, to cut down on the overhead that would ordinarily be associated with accessors and mutators. 


The only two methods in the `Node` class are the default and initializing constructors. The default constructor makes a node with the data set to the default value for the `data` payload (e.g., zero for numeric primitives) and `pNext` set to zero. The initializing constructor allows us to set the payload value and next pointer via the parameters. 


##### Inline methods


Now we turn our attention to the methods in the `SimpleSLL` class that are so simple that they are inline, i.e., they are written inside the class declaration. The first is the constructor:


```
SimpleSLL() : pHead(0), n(0) { }


```


This default constructor simply sets the `pHead` pointer and size variable `n` both to zero. 


The destructor is almost as simple:


```
~SimpleSLL() { clear(); }


```


Here we simply call the `clear` method, to remove all of the elements in the list. `clear` is defined below. 


The next inline method is the `isEmpty` convenience method:


```
bool isEmpty() const { return size() == 0; }


```


`isEmpty` is a `const` method, meaning that the method does nothing to change the state of the list. It calls `size` and compares that returned value to zero. 


The final inline method is `size`:


```
size_t size() const { return n; }


```


This is simply an accessor for the size variable, `n`. `size_t` is a primitive data type, an unsigned integer of at least 16 bits, and generally much larger than that. It is used to represent the size of an object. So, it makes sense to use the type for `n`, the number of elements in the list, and thus for the return type of the `size` method. 


##### `SimpleSLL` fields


The final two parts of the `SimpleSLL` class declaration are its two fields: the `Node` pointer, `pHead`, and the number of elements in the list, `n`. 


##### Other methods


After the class declaration, we have the methods that are too long to implement inline, and their associated [doctest](https://github.com/onqtam/doctest) unit test functions. 


The `add` method needs to create a new `Node` object, containing the specified value as its payload, link it into the list as the first element, and then modify the `pHead` pointer:


```
template <class T> 
void SimpleSLL<T>::add(const T &d) {
    // create the new node
    Node *pN = new Node(d, pHead);


    // change head pointer to point to the new node
    pHead = pN;


    // increment size
    n++;
}


```


When we create a new node, the second parameter in the constructor call sets the `pNext` pointer in the new node to the value of `pHead`, as in this case, where 'a' is being added to a list that already contains 'A', 'B', and 'C':


<img src="https://doane.instructure.com/files/896969/download?download_frd=1" alt="Adding a new node" title = "Adding a new node"/>


Then, the value of `pHead` is changed to point to the newly created node, and the size variable `n` is incremented. The result is that the new node has been correctly placed at the beginning of the list:


<img src="https://doane.instructure.com/files/896970/download?download_frd=1" alt="New node placed correctly" title = "New node placed correctly"/>


The `clear` method requires some care. We have to move a cursor pointer, `pCurr`, down the list, visiting each one, but we also need a second cursor, `pPrev`, so that we can safely delete a node without losing the value of its `pNext` pointer. First, the code: 


```
template <class T> 
void SimpleSLL<T>::clear() {
    // create cursors
    Node *pCurr = pHead, *pPrev = 0;


    // iterate thru list, deleting each node
    while(pCurr != 0) {
        // "inchworm" up to next node
        pPrev = pCurr;
        pCurr = pCurr->pNext;


        // delete previous node
        delete pPrev;
    }


    // reset head pointer and size
    pHead = 0;
    n = 0u;
}
```


To help illustrate how this works, imagine that we are somewhere in the middle of the process, with `pCurr` pointing to the next node to be deleted, and `pPrev` still set to the address of the most-recently-deleted node:


<img src="https://doane.instructure.com/files/896971/download?download_frd=1" alt="Clear phase 1" title="Clear phase 1"/>


Since `pCurr` is not yet zero, the `while` loop continues, and the value of `pPrev` is set to the same as `pCurr`:


<img src="https://doane.instructure.com/files/896972/download?download_frd=1" alt="Clear phase 2" title="Clear phase 2"/>


Then, `pCurr` is moved forward to the next node in the list:


<img src="https://doane.instructure.com/files/896973/download?download_frd=1" alt="Clear phase 3" title="Clear phase 3"/>


Finally, the object that `pPrev` points to is deleted:


<img src="https://doane.instructure.com/files/896974/download?download_frd=1" alt="Clear phase 4" title="Clear phase 4"/>


These four steps are repeated over and over again, until `pCurr` becomes zero. At that point, all of the nodes have been deleted, and so we finish the method by setting `pHead` and `n` to zero.


The `contains` method is simpler:


```
template <class T> 
int SimpleSLL<T>::contains(const T &d) const {
    // create cursors
    int idx = -1;
    Node *pCurr = pHead;


    // iterate until we find d or end of list
    while(pCurr != 0) {
        idx++;


        // found it? return its index
        if(pCurr->data == d) {
            return idx;
        }


        pCurr = pCurr->pNext;
    }


    // not found? return flag value
    return -1;
}
```


Here, we simply use our traversal pattern to examine each node in turn, to see if it contains the value `d` passed in as a parameter. We maintain an index value, `idx`, that contains the index of each node in turn. If we find our value `d`, we return the current value of `idx`. If we go all the way through the list without seeing `d`, we fall out of the `while` loop and return the not found flag value, negative one. 


The `get` method uses a similar traversal pattern, but also must check to see if the index provided by the user actually refers to an existing element in the list. Here is the code:


```
template <class T> 
T SimpleSLL<T>::get(size_t idx) const {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in SimpleSLL::get()");
    }


    // initialize cursor
    Node *pCurr = pHead;


    // iterate cursor to position
    for(size_t i = 0u; i < idx; i++) {
        pCurr = pCurr->pNext;
    }


    // return requested value
    return pCurr->data;
}
```


Since the `idx` parameter is of type `size_t`, there is no possibility of a negative index coming into the method. Therefore, the only illegal index is one that is greater than or equal to the size of the list, `n`. If that is the case, we throw a `std::out_of_range` exception object and the method terminates. 


If the `idx` value is legal, then we need to traverse up to that location in the list. We do this with a `for` loop, using the by-now-familiar `pCurr = pCurr->pNext` statement inside the loop. After the loop, `pCurr` points to the node at the specified location, and so we finish the method by returning the `data` value stored at that location. 


The `remove` method is the most complicated method we have looked at so far. Here is the code:


```
template <class T> 
T SimpleSLL<T>::remove(size_t idx) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in SimpleSLL::remove()");
    }


    // initialize cursors
    Node *pCurr = pHead, *pPrev = 0;


    // iterate cursors to position
    for(size_t i = 0u; i < idx; i++) {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }


    // save value so we can return it
    T d = pCurr->data;


    // first element? change head pointer
    if(pCurr == pHead) {
        pHead = pCurr->pNext;
    } else {
        // general case: "wire around" node
        pPrev->pNext = pCurr->pNext;
    }


    // remove node and decrement size
    delete pCurr;
    n--;


    // send back removed value
    return d;
}
```


We start with a sanity check on `idx` as we did in the `get` method. Then, as in the `clear` method, we set up two cursor pointers, `pPrev` and `pCurr`. Then, as in the `get` method, we use a `for` loop to iterate the cursors to their proper locations: `pCurr` points to the node we want to remove, and `pPrev` to the previous node. Before moving to the code that actually deletes the node, we save the type `T` value the method is going to return.


Now, we have a question to confront: is the node to remove the first node, or one of the others? If it is the first node, then we must update the head pointer to refer to the following node. If it is not the first node, then we make no changes to `pHead`, we instead change the value of the previous node's `pNext` pointer to have the same value as the current node's `pNext`, "wiring around" the node to be deleted, like this:


<img src="https://doane.instructure.com/files/897113/download?download_frd=1" alt="Wiring around a node" title="Wiring around a node"/>


Then, the node is deleted, and `n` is decremented. For the general, non-first-element case, we visualize the deletion like this:


<img src="https://doane.instructure.com/files/897117/download?download_frd=1" alt="Safely deleting an internal node" title="safely deleting an internal node"/>


If we did not wire around the deleted node first, we would lose its `pNext` pointer value, and thus lose track of the rest of the list. When working with data structures algorithms that involve pointers, it is great advice to draw a picture of the situation, and then *very carefully* indicate which pointers change, and the order in which they change. 


The `print` method is another traversal, using a cursor pointer and a `while` loop. We will not cover it here, but you can refer to it in the source code if you would like. 


The `set` method is very similar to the `get` method. The only difference is that we change the value of the selected node, rather than return the value. As for `print`, we will not cover the `set` code here. 


And that is all! You can compile the code and run the unit tests, and you'll find that they all pass. Momentarily we will turn to the module's sample application. Before we do, though, we should take a minute to think about what other options we have for implementing a list.


### Implementation options


Do we have to use linked nodes to implement a list? Well, no. For instance, we could use an array of type `T` as the underlying storage structure, rather than linked nodes that each contain a single type `T` value. The next few paragraphs discuss the performance tradeoffs that would be incurred if we chose an array as the underlying structure rather than linked nodes.


#### An array-backed list would have a capacity, with costly resizing


One of the advantages of a linked list is that it is always just the right size; it does not have any unused slots as an array would. Therefore, as we mentioned above, linked lists have sizes but not capacities. 


An array-backed list would be finite, by its nature, and so would have a capacity, and therefore, potentially unused slots in the structure. This can waste memory.


In addition, what happens if the size becomes equal to the capacity? What if we want to add more to the list after that happens? If we mean the structure to grow, then we would have to create a new array, of a larger size, copy the elements over from the old array to the new one, and then delete the old one. The linked-node list never needs to do anything like this. 


We will discuss *time complexity* in a later module, and then we will be able to fully quantify this performance difference. For now, consider this: an array-backed list with size and capacity of 1,000,000 would require on the order of 1,000,000 steps to move to a list with size of 1,000,001 and a larger capacity. 


#### An array-backed list *could* have a costly `add` method


If we use an array as the backing storage for our list, and *if* we keep the front of the list on the left side, as in our diagrams, then the `add` method becomes expensive. Suppose we start with this list of size three, capacity five:


<img src="https://doane.instructure.com/files/897169/download?download_frd=1" alt="Naive insertion into an array-backed list" title="Naive insertion into an array-backed list"/>


The top image is the initial situation. Adding a new value, say, 2, to the list would require opening a slot at the beginning of the list. To do that, we would shuffle each of the values over one position, starting with the rightmost value and moving left, as shown in the middle image. Finally, we place the new value in position. 


Like the list enlargement we discussed above, adding in this way requires one step of the algorithm for each value in the list. If there are 1,000,000 elements in the list, and a capacity that is larger (maybe 2,000,000), we still have 1,000,000 shuffles to do before we can insert the new value. We say that this takes *linear time*.


On the other hand, adding to the front of a linked list takes the same amount of steps, regardless of how many elements are in the list. We say that this takes *constant time*. 


We could make adding to an array-backed list faster in most cases, if we stored the elements in reverse order, as shown in this image.


<img src="https://doane.instructure.com/files/897181/download?download_frd=1" alt="Storing with first element last" title="Storing with first element last"/>


If we maintain an extra variable that tells where the "first" element is, we can add an element to the front of the list in constant time. We would have to tinker with the index-based methods like `get`, so that they use the physical indices of the values, given one of the virtual indices provided by the parameter. There still is a case where we would have a linear-time `add`, though: in the *worst case*, when we exceed the capacity of the list and have to create a new, larger array. In that case, since we have to copy all of the values over to the new array, we are back to a linear-time situation. 


#### An array-backed list has constant-time `get` and `set` methods


In our linked list, `set` and `get` are linear-time algorithms, because we have to iterate from the first node through all of the nodes prior to the one at location `idx`. On the other hand, in an array-backed list, `set` and `get` are constant-time, because we can get to the required value just by using an array access. 


#### Both versions have linear-time `remove` methods


Both versions, array-backed and linked-node, require linear time for the `remove` method. In the array-backed case, the linear time is required to close up the "hole" made by removing a value, sort of the opposite of the shuffling we examined with the naive `add` method. In the linked-node case, the linear time is required to iterate to the correct node to remove. So, as far as removing goes, there is no performance advantage to either storage scheme.


#### So which one is better?


Which one is better? It depends. If we need efficient access to elements in the middle of the list, then an array-backed list is probably better. If we do not know how big the list will be at the outset, then a linked-node list is probably better, because it always has constant `add` time. This is why Java provides two lists -- `LinkedList` and `ArrayList`. As programmers, we can choose the one that best fits how we will use the list. 


Having said that, we are obviously using the linked structure here. 


## Sample application: user authentication


**[For this section of the reading, refer to the sample code in the module02-SimpleSLL/2-UserAuth directory of the course's git code repository]**


This module's sample application is a simple user authentication system. A series of usernames and passwords is stored in the file named `users.txt`. Each line has one username and password, separated by whitespace. There are 100 lines in the file, like this:


```
abraham.delgado MC2)sm.3,~9a`'}8
adrienne.bowen PA=[J+t~;x@5DjRK
alberta.reid MbSQ2]^h65qyF_Rz
alicia.sullivan YeAGVv.LBnj/;@3H
allison.guerrero f'MG^+#h6>4R-2;u
alma.moss v2&MB=Q]b3,;n}Z(
amanda.foster e&7Q]qV-zSPd2)!3
amber.klein kDB]ytV*bWMT3Yfx
andrea.wong PH^t%6Y=qy[<!Ee)
angelina.terry FR@>=J$a7tp%HG(g
.
.
.
merle.watkins password123
.
.
.
yvonne.arnold g>be}nXc=M96'v5
```


User `merle.watkins` has a very poor password, but he is included so that we can test the application more easily.


Our application reads in the information from `users.txt` and loads them into a `SimpleSLL` of `User` objects. The `User` class is designed to encapsulate the username and password into one chunk. Here's a UML class diagram for `User`:


<img src="https://doane.instructure.com/files/897206/download?download_frd=1" alt="User class diagram" title="User class diagram"/>


`User` has `std::string` fields for the name and password, accessors for each, and overrides the `=` and `==` operators. We will look at operator overrides later on. For now, just understand that these allow assignment and equality checking to make sense for `User` objects.


Once we have all of the user data in the list, the application prompts the user to type in a username and password. Then, we search the list with the `contains` method, to see if the username and password match one of the entries in our file of authenticated users. If so, we print a rudimentary welcome message. If not, we let the user know that their access has been denied. 


Here is a sample session showing how the application works:


```
Enter username (q to quit): merle.watkins
Enter password: password123
WELCOME TO OUR SITE!
...logged off.
Enter username (q to quit): melissa.smith
Enter password: th8m;f"kJ*n%s_([
WELCOME TO OUR SITE!
...logged off.
Enter username (q to quit): jessie.blair
Enter password: NotMyPasswordBro
ACCESS DENIED.
Enter username (q to quit): q
```


Authenticating users in this way is a linear-time operation, because `contains` takes linear time to search our list for the specified user. If we have a really large number of users, we would probably want to choose a different data structure in order to speed up the process.


In our next module, we will improve the linked list, by adding an additional constructor and overriding several operators so that they work with the list.