## Module 5: Doubly-Linked Lists, Stacks, Queues


In this module, we will turn our singly-linked list into a *doubly-linked list*, with nodes that have pointers to both the next node in the list and to the previous node in the list. This will allow us to move through the list in either direction -- from first to last or from last to first. 


Additionally, we will maintain a pointer to the beginning of the list and to the end of the list, which will allow us to add items at the front or the back of the list.


Then, we will use an object-oriented programming principle, *composition*, to create two new data structures, *stacks* and *queues*, using our doubly-linked list. 


### Design of the doubly-linked list


**[For this section, refer to the `module05\1-DLL\DLL.hpp` file from the course's git repository.]**


To make our linked list data structure more versatile, and to be able to use the linked list as a backing store for stacks and queues, we need to be able to increase the number of options for efficiently inserting items into the list, and allow traversals of the list in both directions. A way to do this is to change the singly-linked list into a doubly-linked list (DLL). 


To refresh our memory, here is a schematic diagram of a singly-linked list:


<img src="https://doane.instructure.com/files/896968/download?download_frd=1" alt="Singly-linked list schematic" title="Singly-linked list schematic"/>


Each value in the list is held in a node, and each node has a pointer to the next node in the list. We maintain a pointer to the beginning of the list, and another field to hold the size of the list. 


There are two main changes to make a DLL. First, we will redesign our node class so that it has the data payload, and pointers to the next node in the list as well as the previous node in the list:


<img src="https://doane.instructure.com/files/965663/download?download_frd=1" alt="DLL node" src="DLL node"/>


In this new class, the meaning of the `pNext` pointer is the same as it was in the singly-linked list. The `pPrev` pointer points in the other direction, to the previous node in the list. The first node in the list will have a zero value for `pPrev`, while the last node in the list will have a zero value for `pNext`. 


The second major change to create our DLL is to maintain a second pointer in the list class, in addition to the `pHead` pointer. The second pointer, `pTail` will always point to the last node in the list. This DLL schematic illustrates the situation for a list of three nodes:


<img src="https://doane.instructure.com/files/965668/download?download_frd=1" alt="DLL schematic" title="DLL schematic"/>


Adding the second pointer to our list nodes, and adding the `pTail` pointer to the list class, will require adaptations to our code. Overall, things will be a little more complicated than for the singly-linked list. For example, when we remove a node from a DLL, we have twice as many pointers to deal with. On the other hand, some algorithms, like list copying, will be easier to implement in the DLL.


### Implementing the DLL


Before we start looking at the C++ code to implement the DLL, let's first look at the UML class diagram for the new list and its node class:


<img src="https://doane.instructure.com/files/965672/download?download_frd=1" alt="DLL UML class diagram" title="DLL UML class diagram"/>


The node class diagram is a straightforward translation from the schematic diagrams we showed in the last section. We cannot see it in the class diagram, but the constructors for the `DLL<T>::Node` class will now take three parameters: the data value, the value for the node's `pPrev` pointer, and the value for the node's `pNext` pointer. 


The `DLL` class itself, though, is more complicated. We have several more methods than we saw with the singly-linked list: 


- We have methods to add, get, remove, and set from the front and end of the list (`addFirst`, `addLast`, `getFirst`, `getLast`, `removeFirst`, `removeLast`, `setFirst`, and `setLast`), while the singly-linked list had only add and remove. 


- We have two ways to get iterators: `front`, which returns an iterator to the first element in the list, and `back`, which returns an iterator to the last element in the list. The `end` method will be used to determine when the end of the list has been reached, regardless of which direction the traversal is going.


The other methods in the class diagram (`clear`, `contains`, etc.) have the same meaning as they had in the singly-linked list. 


You probably can guess that our iterator will be a bit more complex too. You are correct, but there are not *too* many changes here. Here's the iterator class diagram:


<img src="https://doane.instructure.com/files/965673/download?download_frd=1" alt="DLL Iterator UML class diagram" title="DLL Iterator UML class diagram" />


The only new addition to the `DLL<T>::Iterator` class is the postfix decrement operator, `--`, which allows us to traverse the list from back to front, in addition to the front to back direction provided by the `++` operator. 


Now we can dig in to some selected methods from the DLL class and see how they are implemented.


#### The `addFirst` method


The `addFirst` adds a new element to the list, in position zero (i.e., at the front of the list). The code looks like this:


```
template <class T> 
void DLL<T>::addFirst(const T &d) {
    Node *pN = new Node(d, 0, pHead);


    if(pHead == 0) {
        // empty list case
        pHead = pTail = pN;
    } else {
        // non-empty list case
        pHead = pN;
        pHead->pNext->pPrev = pHead;
    }
    
    n++;
}
```


There are two cases to consider here: when the list is empty, and when it is not. The non-empty case is more complicated, so we will dive right in and cover that case first. 


Assume we have an existing doubly-linked list that contains the integer values [3, 1, 5]. Let's see what happens when we add the value 4 to the beginning of the list. 


First, we create a new node with the specified data value from the parameter  `d`, which in this example would be 4. The other two parameters in the `Node` constructor call are the value for the new node's `pPrev` pointer (0) and the value for its `pNext` pointer (`pHead`). Here is the situation at this point in the process:


<img src="https://doane.instructure.com/files/965743/download?download_frd=1" alt="addFirst process, step 1" title="addFirst process, step 1"/>


As you can see in the diagram, the new node, referred to via the pointer `pN`, is already connected to the rest of the list by virtue of the constructor call. What remains in this case (adding to the front of a list with existing data) is to update the value of the head pointer, maintain the integrity of the pointers holding the nodes together, and update the size variable. 


Changing the value of `pHead` is handled in the first statement of the `else` statement. The next line, 


```
pHead->pNext->pPrev = pHead;
```


can be hard to interpret, so let's look at it a little more closely. Once we have changed the value of `pHead`, our list looks like this:


<img src="https://doane.instructure.com/files/966333/download?download_frd=1" alt="addFirst process, step 2" title="addFirst process, step 2"/>


The integrity of the pointers between nodes is compromised at this point, because the `pPrev` pointer of the node containing 3, which used to be the first node, is still set to zero. We need to change it to point to the *new* first node, the one containing 4. 


It may help to think of the statement `pHead->pNext->pPrev = pHead` in three parts. In part 1, `pHead` part "grabs a hold of" the node containing 4:


<img src="https://doane.instructure.com/files/966978/download?download_frd=1" alt="addFirst process, step 3.1" title="addFirst process, step 3.1" />


Then, `pNext->pPrev` grabs a hold of the node containing the 3:


<img src="https://doane.instructure.com/files/966979/download?download_frd=1" alt="addFirst process, step 3.2" title="addFirst process, step 3.2"/>


Finally, `pPrev = pHead` sets the `pPrev` pointer in the node containing 3 to refer to the new first node (the one containing 4):


<img src="https://doane.instructure.com/files/966980/download?download_frd=1" alt="addFirst process, step 3.3" title="addFirst process, step 3.3"/>


Now the integrity of the list-connecting pointers has been maintained, and the method ends by incrementing the size field `n`. 


If the list happens to be empty when `addFirst` is called, we create a new node in the same way as described above. Then, this statement in the if is executed:


```
pHead = pTail = pN;
```


After this the one and only element in the list is both the first element and the last element, so both `pHead` and `pTail` refer to it. 


As you might expect, the `addLast` method is very similar to `addFirst`. We will not cover `addLast` here.


#### The `copy` method


As was the case with the singly-linked list, we have a private `copy` method in the `DLL` class that is used by the copy constructor and by the assignment operator override. Thanks to the existence of the `addLast` method, the code for `copy` is simpler here than it was for the singly-linked list:


```
template <class T> 
void DLL<T>::copy(const DLL<T> &list) {
    // remove any existing data
    clear();


    // using iterator and addLast simplifies this method compared with the 
    // equivalent in previous SLLs
    for(DLL<T>::Iterator i = list.front(); i != list.end(); i++) {
        addLast(*i);
    }
}
```


We start by clearing the contest of the list. This step is needed because `copy` is used in the assignment operator; we want assignment to remove any existing data in the list before copying new data over. 


Then, we use an iterator to move through the parameter DLL, `list`. The loop body adds each element of `list` to the *end* of the object's data, via calls to the `addLast` method with the dereferenced iterator as a parameter. We were unable to take this approach with the singly-linked list, because that list's `add` method added only to the front. In that case, repeated calls to `add` would result in the new list being a *reversed* copy of the original.


#### The `removeFirst` method


The `removeFirst` method has to save the data from the first node, update the head pointer, and maintain the integrity of the list's pointers. Here is the code: 


```
template <class T> 
T DLL<T>::removeFirst() {
    if(pHead == 0) {
        throw std::out_of_range("Empty list in DLL::removeFirst()");
    }


    // save data in front node, and pointer to the node
    T d = pHead->data;
    Node *pTemp = pHead;


    // update head pointer
    pHead = pHead->pNext;
    if(pHead != 0) {
        // if there are more elements, mark new front node prev pointer
        // as left end of the list
        pHead->pPrev = 0;
    } else {
        // if there are no more elements, update tail pointer
        pTail = 0;
    }


    // update size, free former front node memory
    n--;
    delete pTemp;


    // send back value from former front node
    return d;
}
```


We start with a sanity check that throws an exception if the list is empty when `removeFirst` is called. Then, we save the first node's data in the variable `d`, and maintain a pointer to the node, `pTemp`, so we can delete the node later on. Then, we change `pHead` to point to the second node in the list, if it exists.


Now, we have one of two situations. If there was only one node in the list, the pointers look like this:


<img src="https://doane.instructure.com/files/967053/download?download_frd=1" alt="removeFirst process step 1, list size 1" title = "removeFirst process step 1, list size 1"/>


Since we will be removing the only node left in the list, the `pTail` pointer must be updated to zero. Otherwise, after this method is over, `pTail` would point to memory our program doesn't "own" any more. So, the else statement executes, changing `pTail`, and we have this:


<img src="https://doane.instructure.com/files/967056/download?download_frd=1" alt="removeFirst process step 2, list size 1" title="removeFirst process step 2, list size 1"/>


On the other hand, if there was more than one element in the list when `removeFirst` is called, the pointers look like this when we reach the if statement:


<img src="https://doane.instructure.com/files/967054/download?download_frd=1" alt="removeFirst process step 1, list size n" title = "removeFirst process step 1, list size n"/>


Here, we need to maintain the list's pointer integrity, by making the new first element's `pPrev` pointer zero, as shown here:


<img src="https://doane.instructure.com/files/967086/download?download_frd=1" alt="removeFirst process step 2, list size n" title = "removeFirst process step 2, list size n"/>


After we've made sure that the pointers are all pointing to the right things, we can decrement our size variable, delete the removed node, and, finally, return the value that was in the deleted node. 


The `removeLast` method, not covered here, is similar to `removeFirst`. 


#### The `remove` method


The `remove` method is the last `DLL` method we will cover explicitly here, and it is also the most complicated, due to the need to manage twice the number of pointers as we had to do with the singly-linked list. We use the same overall algorithm (find the node to remove, "wire around" it, and then delete it), but the details are more involved. 


First, here is the code itself:


```
template <class T> 
T DLL<T>::remove(unsigned idx) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in DLL::remove()");
    }


    // handle special cases with other methods
    if(idx == 0u) {
        return removeFirst();
    } else if(idx == n - 1u) {
        return removeLast();
    }


    // handle the general case
    Node *pCurr = pHead;


    // iterate cursor to position
    for(unsigned i = 0u; i < idx; i++) {
        pCurr = pCurr->pNext;
    }


    // save value so we can return it
    T d = pCurr->data;


    // wire around the node to be removed
    pCurr->pPrev->pNext = pCurr->pNext;
    pCurr->pNext->pPrev = pCurr->pPrev;


    // remove node and decrement size
    delete pCurr;
    n--;


    // send back removed value
    return d;
}
```


As was the case with the singly-linked list `remove` method, the `idx` parameter contains the index of the element to remove from the list, and so our new version of `remove` begins with a sanity check that throws a `std::out_of_range` exception if `idx` is an index that is past the end of the list. 


Then, we take advantage of the `removeFirst` and `removeLast` methods to remove the first or last element, if `idx` is zero or the last index in the list. This means that `removeFirst` also handles the special case of removing the only element from the list. 


What's left is the general case -- we are removing a node from somewhere in the middle of the list, not the beginning or the end, and the list has more than one element in it. So, we iterate a cursor pointer, `pCurr`, to the node that will be removed with a for loop. Now, our pointers look like this:


<img src="https://doane.instructure.com/files/967099/download?download_frd=1" alt="remove process, step 1" title="remove process, step 1"/>


After we save the data value that we will return, we "wire around" the node to remove with two statements that are similar to the one we encountered in `addFirst`:


```
pCurr->pPrev->pNext = pCurr->pNext;
pCurr->pNext->pPrev = pCurr->pPrev;
```


Now our pointer situation looks like this:


<img src="https://doane.instructure.com/files/967109/download?download_frd=1" alt="remove process, step 2" title="remove process, step 2"/>


At this point, only `pCurr` points to the node we want to remove, and the other pointers in the list are set correctly. Therefore, we can delete the node, decrement the size variable, and return the data value from the removed node. 


### Time complexities of `DLL` methods


Since we introduced the concept of algorithmic time complexity in the previous module, we will evaluate the time complexity of each of our data structure's methods before we move on to stacks and queues.


As we have implemented it, the `DLL` class has several methods that take constant time, and several others that take linear time. Some are every-case, and some are best / worst-case time complexities. Before moving on to the next section, can you determine the time complexities of the methods?


| Method | Time Complexity |
| ---------- | ---------- |
| Copy constructor | ??? | 
| Destructor | ??? |
| Assignment operator | ??? |
| `addFirst` | ??? |
| `addLast` | ??? |
| `back` | ??? |
| `clear` | ??? |
| `contains` | ??? |
| `copy` | ??? |
| `end` | ??? |
| `front` | ??? |
| `get` | ??? |
| `getFirst` | ??? |
| `getLast` | ??? |
| `isEmpty` | ??? |
| `remove` | ??? |
| `removeFirst` | ??? |
| `removeLast` | ??? |
| `set` | ??? |
| `setFirst` | ??? |
| `setLast` | ??? |
| `size` | ??? |


#### Methods with every-case time complexity


So, how did you do? Which `DLL` methods have every-case time complexity? 


Methods that do not have to traverse the list elements to do their work have every-case, constant-time complexity -- *O(1)*. Methods like `addFirst`, `end`, and `size` fall into this category. 


Methods that have to traverse *all* of the list elements to do their work have every-case, linear time complexity -- *O(n)*. The copy constructor, and `clear` methods are examples of this category.


This table summarizes the time complexities of the methods with every-case complexity:


| Method | Time Complexity |
| ---------- | ---------- |
| Copy constructor | *O(n)* | 
| Destructor | *O(n)* |
| Assignment operator | *O(n)* |
| `addFirst` | *O(1)* |
| `addLast` | *O(1)* |
| `back` | *O(1)* |
| `clear` | *O(n)* |
| `copy` | *O(n)* |
| `end` | *O(1)* |
| `front` | *O(1)* |
| `getFirst` | *O(1)* |
| `getLast` | *O(1)* |
| `isEmpty` | *O(1)* |
| `removeFirst` | *O(1)* |
| `removeLast` | *O(1)* |
| `setFirst` | *O(1)* |
| `setLast` | *O(1)* |
| `size` | *O(1)* |


#### Methods with best / worst-case time complexity


The methods that may take a differing amount of time to do their work, based on the list contents and / or the method parameters, will not have every-case time complexity. Instead, we will need to think about their best- and worst-case time complexities. For the `DLL` class, the methods in this category are `contains`, `get`, `remove`, and `set`. 


The `contains` method searches for an element in the list. In the best case, the element we're looking for is first in the list, so we only need to do one comparison to find it. Therefore, for `contains`, *B(n) ∈ O(1)*. On the other hand, if the value we're looking for is last in the array, or not in the array at all, we have to do n comparisons. Therefore, for `contains`, *W(n) ∈ O(n)*. 


The `get`, `set`, and `remove` have identical time complexities, but for slightly different reasons. All three of these methods take an index parameter, which dictates how many loop iterations are required by the method. If the index is zero, then the time complexity is constant, *B(n) ∈ O(1)*. If the index specified the last element in the list, then the time complexity is linear, so *W(n) ∈ O(n)*. 


| Method | B(n) | W(n)
| ---------- | ---------- | ---------- |
| `contains` | *O(1)* | *O(n)* |
| `get` | *O(1)* | *O(n)* |
| `remove` | *O(1)* | *O(n)* |
| `set` | *O(1)* | *O(n)* |


### Stacks


**[For this section, refer to the `module05\2-Stack\Stack.hpp` file from the course's git repository.]**


A stack is a linear structure, like our lists. But, we imagine it / visualize it as being a vertical structure, rather than horizontal, and we do not associate indices with the elements in the stack. We think of the stack as if it has a bottom and a top. Here is an illustration of a simple stack of five integers:


<img src="https://doane.instructure.com/files/977432/download?download_frd=1" alt="Stack of 5 integers" title="Stack of 5 integers"/>


A stack is like a stack of trays in the cafeteria. When you go to get a tray, which one do you pick up? The one on the top, of course. And, when a tray has been washed, where is placed to get it back into the stack? Also on the top.


So, a stack is a linear data structure, with no element indices, where our operations for adding to and removing from the structure are limited -- they only happen at the top. There are three unique operations supported by the stack:


- `push`, which is used to add an element to the top of the stack
- `pop`, which removes the top element from the stack
- `peek`, which gets a reference to the top element of the stack, without popping it from the stack


The normal administrative methods we have come to expect from our data structures will also be supported by our stack: `clear`, `size`, assignment operator overload, etc. 


A stack is called a *FIFO* (first in, first out) structure, because the latest element pushed onto the stack will always be the first thing popped from the stack. 


#### Composition vs. inheritance


You might guess that, since we are discussing the stack data structure in the module that introduced the doubly-linked list, the `DLL` class will somehow be involved in our stack data structure. 


You are correct! The `DLL` has `addFirst` and `removeFirst` operations, which make it perfect for our stack. We might think about using the concept of *inheritance* here, making `Stack` a subclass of `DLL`, as illustrated in this UML diagram:


<img src="https://doane.instructure.com/files/977441/download?download_frd=1" alt="Stack is-a DLL" title="Stack is-a DLL"/>


Remember that in inheritance, we read the arrow as "is-a." If we used inheritance like this, we could implement new methods in `Stack` (`push`, `pop`, `peek`) that merely call the appropriate inherited methods from `DLL` (`addFirst`, `removeFirst`, `getFirst`). 


So, what do we think of this approach? Is it wise to use inheritance to create our stack, so that `Stack` is-a `DLL`? What are your thoughts? 


Well, in this case, inheritance is not a good solution, because the `Stack` class would inherit *all* of the public methods of the `DLL` class, and therefore, the inheritance-based stack would have too much capability. For example, the stack would allow users to access elements by index (which stacks do not have) and to change elements in the middle of the structure (which stacks are not supposed to support). So, inheritance is not the way to go here. 


Instead, we will use the concept of *composition,* where the `Stack` class *has-a* `DLL` instance as a private data member. The UML diagram for this situation uses a different type of arrow, shown here:


<img src="https://doane.instructure.com/files/977450/download?download_frd=1" alt="Stack has-a DLL" title="Stack has-a DLL"/>


Since the `DLL` will be a private field, our `Stack` class will still be able to access the relevant methods, but the unwanted `DLL` methods will not be exposed to users of the stack. 


The UML class diagram of our stack data structure is simpler than the diagram for `DLL`, since we only support a limited number of modification methods. The private `list` field is our instance of `DLL`. 


<img src="https://doane.instructure.com/files/967724/download?download_frd=1" alt="Stack UML class diagram" title="Stack UML class diagram"/>


#### Implementing the stack


Since all of the heavy lifting is being done by the `DLL` class, implementing our `Stack` class is pretty easy. We will look at `push` and `pop` here, and you are encouraged to read through the rest of the implementation.


The `push` operation is a simple one-line method, so it is defined inline in the class declaration:


```
void push(const T &v) { list.addFirst(v); }
```


All `push` has to do is call the `addFirst` method of the private `list` object. 


If it were not for exception handling, we could also implement `pop` as an inline definition. But, we will add a sanity check to make sure the list is not empty before trying to pop an element. So, the `pop` method definition looks like this:


```
template <class T>
T Stack<T>::pop() {
    if(list.isEmpty()) {
        throw std::out_of_range("Empty stack in Stack::ppo()");
    }


    return list.removeFirst();
}


```


Technically, the `list` object would throw its own exception if we tried to execute the `removeFirst` method on an empty list, but we add a sanity check here so that the exception indicates that the error was caused when the stack `pop` method was called. 


#### Stack operation time complexity


Since the `push`, `pop`, and `peek` operations call `DLL` methods with *O(1)* time complexity, their complexity is also *O(1)*. So, stack operations are very fast. 


### Queues


**[For this section, refer to the `module05\3-Queue\Queue.hpp` file from the course's git repository.]**


A *queue* is another linear data structure with limited insert and remove operations. Like a stack, there are no indices associated with elements in a queue. Unlike a stack, we visualize the queue as being horizontal rather than vertical. New elements are added to the back of the queue, and elements are removed from the front of the queue. 


<img src="https://doane.instructure.com/files/977499/download?download_frd=1" alt="Queue of 5 integers" title="Queue of 5 integers"/>


Whereas the analogy for the stack data structure was a stack of trays in the cafeteria, our analogy for a queue is a line of people waiting for a bank teller. When a new customer arrives, they join the back of the line, and when they reach the front of the line, they are the next person to be served. 


A queue, therefore, is a linear data structure, with no element indices, where our operations for adding to and removing from the queue are limited: additions happen at the back of the queue, and removals happen at the front. There are two unique operations supported by a queue:


- `enqueue` (pronounced en-Q): add a new element to the back of the queue
- `dequeue`(pronounced de-Q): remove and return the first element from the front of the queue


As for the `Stack` class, our `Queue` class will also support the usual administrative operations, and will involve composition with the `DLL` class for the backing store. Here is the UML class diagram for our `Queue` class:


<img src="https://doane.instructure.com/files/977504/download?download_frd=1" alt="Queue UML class diagram" title="Queue UML class diagram"/>


#### Implementing the queue


Our `Queue` class is even simpler than the `Stack` class, since it supports one fewer operation. We will only look at `dequeue` here; you are encouraged to take a tour through the rest of the `Queue` class on your own. 


As was the case with the `Stack` `pop` method, we add a sanity check to the start of our `dequeue` method:


```
template <class T>
T Queue<T>::dequeue() {
    if(list.isEmpty()) {
        throw std::out_of_range("dequeue of empty queue");
    }


    return list.removeFirst();
}
```


If the user tries to call `dequeue` on a stack that is empty, a `std::out_of_range` exception is thrown. Again, technically, we could rely on the `DLL` `removeFirst` method to throw an exception in this situation. We think this approach is better, though, because a user of our `Queue` class does not need to know or care about our use of `DLL`, and so we prefer that the exception description is particular to the `Queue` class. 


#### Queue operation time complexity


For the same reasons as for the `Stack` class, we can see that the time complexities of the queue `enqueue` and `dequeue` operations is *O(1)*. Note that if we used a `SLL` instead of a `DLL` to implement the stack, the `enqueue` operation would have time complexity *O(n)*, where *n* is the size of the queue. Thus, `SLL` would have been an inappropriate choice as the backing store for a queue, while `DLL` fits the bill exactly. 


### Sample application: RPN calculator


*Reverse Polish notation (RPN)*, or *postfix notation*, is a way of writing mathematical expressions where the operator is placed *after* its two operands, rather than in between them. For example, our normal notation for expressing a sum is like this:


5 + 4


This is called *infix* notation because the operator (+) is in between the operands (5 and 4). In RPN, the equivalent expression is:


5 4 +


This can be extended to expressions that involve more than one operator. E.g., the infix expression 3 - 4 + 5 is written like this in RPN: 3 4 − 5 +.


One benefit of RPN is that it makes parentheses unnecessary, as the order of operations is never in question in a RPN expression. Secondly, research has shown that when users learn to operate a handheld calculator that takes input in RPN, they make fewer mistakes with the calculator than they would if they were to use a calculator using infix notation.


Our module example implements a simple, four-function RPN calculator that uses a stack. The program reads lines containing RPN expressions, tokenizes each line, and evaluates the expression by following these rules:


- If the token is an operator ("+", "-", "*", or "/"), we pop the first value on the stack and store it in a variable named b. Then, we pop the second value from the stack and store it in a variable named a. Next, we compute the value a op b (where op is the appropriate operation, e.g., addition) and, finally, push the result back onto the stack.
- If the token is "E", the expression is complete. In this case, we pop the top value from the stack and print it out. Then, we clear the stack to make sure we are ready for the next expression.
- Otherwise, we assume the token represents a number. We convert it from a string object to a double value, and push this value onto the stack. 


Our program will assume that each RPN expression is correctly formed, i.e., no illegal strings like "3 + 4 E" are entered. Here is a sample session, showing the calculator evaluating a variety of expressions. 


```
Welcome to the Doane RPN Calculator!
Please enter an expression in postfix, EOF to quit.
3 4 + E
>> 7
3 4 + 5 * E
>> 35
4 5 7 2 + - *  E
>> -16
3 4 + 2  * 7 / E
>> 2
5 7 + 6 2 -  * E
>> 48
4 2 3 5 1 - + * + E
>> 18
4 2 + 3 5 1 -  * +  E
>> 18
5 1 2 + 4 * + 3 - E
>> 14
17 8 - E
>> 9
6 2 / 5 + E
>> 8
5 4 + 7 2 - * E
>> 45
3 4 + 10 1.5 + * E
>> 80.5
3 44 * 5 1.2 + / E
>> 21.2903
Good bye!
```


Before we look at how we implement the RPN calculator with a stack, let's unpack one of the RPN expressions above and see how it is evaluated. In particular, we'll look at the expression


4 2 3 5 1 - + * + E


This expression is equivalent to this infix expression:


(5 - 1 + 3) * 2 + 4


The tokens in the RPN expression are read from left to right, and each is handled according to the rules we enumerated above. So, we begin evaluating the expression by pushing the numbers 4, 2, 3, 5, and 1 all onto the stack, in the order they appear. So, our stack would look like this:


| top |
|----------|
| 1 |
| 5 |
| 3 |
| 2 |
| 4 |


Then, the next token is '-'. So, the value 1 is popped into variable b, the value 5, is popped into variable a, the expression a - b is evaluated: 5 - 1, producing 4, which is pushed back on the stack:


| top |
|----------|
| 4 |
| 3 |
| 2 |
| 4 |


A similar procedure is followed for the token '+': 4 into b, 3 into a, evaluate 3 + 4, and push 7 back on the stack:


| top |
|----------|
| 7 |
| 2 |
| 4 |


Likewise for '*': 7 into b, 2 into a, evaluate 2 * 7, push 14:


| top |
|----------|
| 14 |
| 4 |


One more operator, '+': 14 into b, 4 into a, evaluate 4 + 14, push 18:


| top |
|----------|
| 18 |


Finally, the 'E' is encountered, and the top value of the stack is popped and printed, resulting in the output of 18. 


#### Implementing the calculator


**[For this section, refer to the `module05\4-RPN\RPN.cpp` file from the course's git repository.]**


The heart of this application is an instance of the `Stack` class, parameterized to hold doubles. Then, we use a `while` loop to read all of the tokens as C++ `string` objects, with a chained `if` statement inside to implement the rules we stated above:


```
while(std::cin >> token) {
    if(token == "E") {
        // print result of expression
        std::cout << ">> " << stack.pop() << std::endl;
        stack.clear();
    } else if(token == "+") {
        // addition
        b = stack.pop();
        a = stack.pop();
        stack.push(a + b);
    } else if(token == "-") {
        // subtraction
        b = stack.pop();
        a = stack.pop();
        stack.push(a - b);
    } else if(token == "*") {
        // multiplication
        b = stack.pop();
        a = stack.pop();
        stack.push(a * b);
    } else if(token == "/") {
        // division
        b = stack.pop();
        a = stack.pop();
        stack.push(a / b);
    } else {
        // numeric entry 
        stack.push(atof(token.c_str()));
    }
}
```


The only piece of code that is not straightforward here is that for pushing a number from the expression onto the stack. We use the `atof` function, which converts a *C character string* representing a number into a floating-point value. The issue is that `atof` does not work on *C++ string objects*. So, we call the `c_str` method of the `token` string, which returns a C-style string, which is then passed into the `atof` function. Finally, the value returned by `atof` is pushed onto the stack. 


It should be clear that the time complexity of evaluating an expression is *O(n)*, where *n* is the length of the expression. This is true because we assume that operations like addition and multiplication are executed in unit (constant) time, and the `push` and `pop` operations have time complexity of *O(1)*. *n* repetitions of constant-time operations yields overall time complexity of *O(n)*.