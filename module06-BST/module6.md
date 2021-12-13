## Module 6: Binary Search Trees


In this module, we will work with our first *non-linear* data structure, the *binary search tree*. Each of our previous structures has been linear, because there was a simple, straightforward, front-to-back arrangement of the elements in the structure. This held true for our singly-linked list, our doubly-linked list, and even for stacks and queues. A binary search tree will be different because the elements in the tree have a *hierarchical* structure, and because a node may have up to *two* nodes "after" it in the structure. 


Binary search trees are helpful for doing fast membership testing in our programs -- given value *x*, is *x* in the structure? Our module example, a simple spell-checking program, illustrates this usage. 


Before we delve deeper into the implementation of our binary search tree, let us first look at some tree terminology and basic algorithms. 


### Binary trees


In computing, a *tree* that, if you squint your eyes, looks something like an upside-down tree from nature. The tree has a single *root node*, which has one or more *branches*, which lead to subtrees, which are themselves trees. The recursive nature of this definition might lead you to think that recursive algorithms will play a large part in a tree data structure, and you would be right in thinking that. 


A node in a generic tree can have an arbitrary number of branches to subtrees, but any node in a *binary* tree has at most two branches to subtrees. 


### Binary tree structure


Data will be stored in our binary tree in nodes, just as was the case for our singly-linked and doubly-linked lists. Each node will have a data payload, and pointers to the left and right subtree of the node:


<img src="https://doane.instructure.com/files/982260/download?download_frd=1" alt="Binary tree node" title="Binary tree node"/>


In a binary tree, we will maintain a special pointer, `pRoot`, to the root node. Each node's pointers will refer to the left and right subtrees, with zero values representing the absence of a subtree on that side. So, a binary tree of integers might look like this:


<img src="https://doane.instructure.com/files/982276/download?download_frd=1" alt="Binary tree of 7 integers" title="Binary tree of 7 integers"/>


The root of this tree contains 6. The root node has two children, 2 and 1, which in turn each have two children. In our discussions here, we will say "node 6" rather than "the node containing 6," just to keep our word count down a little. 


Here are some tree terms that help us understand how the values in a tree are related to each other. Node 6 is the *root* of the tree, and it has two *children*, node 2 and node 1. Each of these is the root of a binary tree. Node 1 has two children, 3 and (another) 2; these are *descendants* of node 6. Node 6 is the *parent* of nodes 2 and 1, and an *ancestor* of node 3. 


Nodes 10, 4, 3, and the bottom 2 are *leaf* nodes, because they have no children. Nodes (upper) 2 and 1 are *internal* nodes, because they each have one or more children. The root is on *level 0* of the tree, while the first 2 and node 1 are on level 1, and nodes 10, 4, 3, and the second 2 are on level 2. 


The *height* of this tree is the maximum number of *edges* (pointer links) between the root node and a leaf, i.e., two. This particular tree is a *full* binary tree, since every node except for the leaf nodes has two children. 


Not every tree has to be full. For example, if the duplicate node 2 was not in the tree, it would look like this:


<img src="https://doane.instructure.com/files/982296/download?download_frd=1" alt="Complete binary tree" title="Complete binary tree"/>


In this case, when every level is full except the last, and the nodes on the last level are "left justified," the tree is termed a *complete* binary tree. 


Not every binary tree must be complete or full. For example, consider this tree:


<img src="https://doane.instructure.com/files/982603/download?download_frd=1" alt="Non-full binary tree" title="Non-full binary tree"/>


In this case, nodes 2 and 1 both have only one child each. This is allowed, because the criteria for a tree to be "binary" is that each node has *at most* two children. This applies regardless of the level of the node, or whether the node is internal or a leaf node.


Likewise, consider this tree:


<img src="https://doane.instructure.com/files/982604/download?download_frd=1" alt="Chain binary tree" title="Chain binary tree"/>


This is still a binary tree. Such a tree, where each node actually has at most one child, is called a *chain*. A chain binary tree is actually just a singly linked list. 


### Binary tree traversal algorithms


Some of the methods we will examine later on -- methods to print all of the tree elements and to free the memory allocated to the tree, for example -- need to "visit" each of the nodes in the tree. But, what order should we visit them in? It's pretty clear that we should start at the root, but from there, where do we go? In a linked list, the order was dictated by the linear structure of the list: we start at the head of the list and go to the end, or, if it is a doubly-linked list, we could start at the tail and go towards the front. But, with a binary tree, things are not so clear cut. There are three basic binary tree traversal algorithms to look at: *pre-order*, *post-order*, and *in-order* traversals. Each of these is a recursive algorithm.


#### Pre-order traversal


In a pre-order traversal of a binary tree, we perform whatever action it is that we are doing to the tree (e.g., printing) on the current node, then recursively call the pre-order traversal method on the left subtree, and then recursively call it again on the right subtree. The base case is when we have an empty subtree. In that case, we do nothing. This pseudocode algorithm describes the process:


```
preOrder(Node *pCurr) 
    if pCurr != 0
        process pCurr                // whatever that means
        preOrder(pCurr->pLeft)
        preOrder(pCurr->pRight)
```


Consider this simplified version of the first binary tree we viewed above:


<img src="https://doane.instructure.com/files/982755/download?download_frd=1" alt="Simplified full binary tree" title="Simplified full binary tree"/>


A pre-order traversal would visit the nodes of this tree according to this sequence: 6 - 2 - 10 - 4 - 1 - 3 - 2. 


#### Post-order traversal


In a post-order traversal of a binary tree, we have our recursive calls on the left and right subtrees *first*, and then we process the current node. We have the same base case as before. A post-order traversal is useful when we are freeing the memory allocated for the tree, because we cannot delete the current node until all its descendants have been deleted. This is the pseudocode for a post-order traversal:


```
postOrder(Node *pCurr) 
    if pCurr != 0
        postOrder(pCurr->pLeft)
        postOrder(pCurr->pRight)
        process pCurr                // whatever that means
```


A post-order of the seven-node tree above would visit the nodes of the tree in this sequence: 10 - 4 - 2 - 3 - 2 - 1 - 6. 


#### In-order traversal


In an in-order traversal of a binary tree, we recursively traverse the left subtree first, then process the current node, and then recursively traverse the right subtree. We will see that an in-order traversal of a binary search tree (which we will define shortly) has a special side effect. This is the pseudocode for an in-order traversal:


```
inOrder(Node *pCurr) 
    if pCurr != 0
        inOrder(pCurr->pLeft)
        process pCurr                // whatever that means
        inOrder(pCurr->pRight)
```


We will use a different tree to illustrate the in-order traversal: 


<img src="https://doane.instructure.com/files/982766/download?download_frd=1" alt="Full binary search tree" title="Full binary search tree"/>


An in-order traversal of this tree would visit the nodes of the tree in this sequence: 1 - 2 - 3 - 4 - 6 - 10 - 12. As you can see, the in-order traversal visits the nodes in increasing order. The traversal works this way because this is actually an instance of a *binary search tree*. 


### Binary *search* trees


A *binary search tree* (BST) is a binary tree in which there are no duplicate values in the tree (i.e., every node holds a different value), and where for any node, the value in that node is greater than all the values in the node's left subtree and less than all the values in the node's right subtree. BSTs do not have to be full or complete, but their performance is maximized when the tree is full or complete. As we noted, the tree in the in-order traversal example was a BST, while none of the other previous trees were. You may wish to go back and look at the previous trees, to see why they were not BSTs.  


Now that we have an understanding of what a BST is, we can turn to a C++ implementation of the structure. 


### BST implementation


**[For this section, refer to the `module06\1-BST\BST.hpp` file from the course's git repository.]**


Here is a UML class diagram for our templated BST implementation:


<img src="https://doane.instructure.com/files/982777/download?download_frd=1" alt="BST UML class diagram" title="BST UML class diagram"/>


You can see that, as was the case for our singly- and doubly-linked lists, we have a private nested `Node` class within the `BST` class. The `Node` class has two node pointers, `pLeft` and `pRight`. Some of our methods are recursive, with public interface methods and private helper methods (`clear` and `contains`, e.g.), while others are iterative and require no helper methods (`insert` and `remove`, e.g.). We will look at several methods in the class, starting with the simpler cases and working our way up to the most complex method. 


#### `contains` method


Remember that the primary usage of a BST is for membership testing -- "is element *x* in the tree?" So, our `contains` method takes a value of type `T` as a parameter, and returns true if the value is in the tree, or false if it is not in the tree. There are two versions of `contain`: the public "interface" method called by users of the class, and the private, recursive helper method that actually does the work. The public method is implemented inline and looks like this:


```
bool contains(const T &val) const { return contains(val, pRoot); }
```


It is apparent that this public method simply calls the private version of the method. So, why do we bother? Well, look at the parameter list for the private version: the second parameter is `pRoot`, the pointer to the root node of the tree. The private method needs to have a pointer to the node it is currently working on, and so we pass in the root pointer to begin the recursive process. We *DO NOT* want the users of our class to have access to the pointers used in the structure. So, we hide that bit of complexity from our users behind the public `contains` method. 


Now, let us examine the private, recursive version of the method:


```
template <class T>
bool BST<T>::contains(const T &val, Node *pCurr) const {
    if(pCurr == 0) {
        // empty tree does not contain val
        return false;
    } else if(pCurr->data == val) {
        // found it? return true
        return true;
    } else if(val < pCurr->data) {
        // less than curr? go left
        return contains(val, pCurr->pLeft);
    } else {
        // only other option is to go right
        return contains(val, pCurr->pRight);
    }
}
```


To solve a problem with the *divide and conquer* strategy using recursion, we need two things:


1. A base case, i.e., an instance of the problem that is so simple it can be solved immediately, and 
2. A partitioning that divides an instance of the problem into one or more smaller instances of the same problem. 


For our `contains` method, we have two base cases, which are easy to think about if you try to imagine the easiest BSTs to search. Well, an empty tree certainly does not contain `val`, so we know the answer right away: `false`. Secondly, a tree with the value we are searching for in the root node certainly contains `val`, so again we know the answer: `true`. These base cases are taken care of by the first two `if` statements in the code. 


Our partitioning takes advantage of the characteristics of a BST to cut the size of the problem in half. If the current node does not contain `val`, then if it is in the tree, it must be in the left subtree or the right subtree. Based on the BST structure, if `val` is less than the value in the current node, it must be in the left subtree. So, we return the value of a recursive call to `contains` on the left subtree. If `val` is greater than the value in the current node, it must be in the right subtree, so we return the result of a recursive call of `contains` on the right subtree. 


Eventually, if `val` is in the tree, the recursive process will find its node, and the method returns `true`. If `val` is not in the tree, eventually the recursive process will work its way down to an empty subtree, and return `false`. 


This diagram shows what happens when we search our sample BST for the value 3:


<img src="https://doane.instructure.com/files/982797/download?download_frd=1" alt="Successful BST search" title="Successful BST search"/>


The `contains` method starts at the root. 3 is less than 4, so a recursive call on the left subtree is made. Then, 3 is greater than 2, so a second recursive call is made, on node 2's right subtree. Now, 3 is equal to 3, so the method returns `true` -- and this return value is returned by both of the previous invocations of `contains` as the recursion unwinds. 


On the other hand, what if we search for 7?


<img src="https://doane.instructure.com/files/982798/download?download_frd=1" alt="Unsuccessful BST search" title="Unsuccessful BST search"/>


In this case, `contains` again starts at the root. 7 is greater than 4, so a recursive call on the right subtree is made. Then, 7 is less than 10, so a recursive call on the left subtree of node 10 is made. Likewise, 7 is greater than 6, so a recursive call on the right subtree of node 6 is made. Node 6 has no right subtree, so it's value of `pRight` is zero. Hence, the recursive chain has run into the "empty tree" base case, and the value `false` is returned by the method. 


#### `clear` method


The `clear` method is also implemented recursively, with a public method called by `BST` users and a private, recursive helper method. The public method calls the private version to free all of the nodes in the tree, then performs some housekeeping by setting the values of `n` and `pRoot` to zero:


```
template <class T>
void BST<T>::clear() {
    clear(pRoot);
    n = 0u;
    pRoot = 0;
}
```


The private version of the `clear` method takes a single parameter, a pointer to the current node in the process, `pCurr`. 


```
template <class T>
void BST<T>::clear(Node *pCurr) {
    if (pCurr != 0) {
        // post-order traversal is needed here - delete left and right 
        // subtrees first, then the current node
        clear(pCurr->pLeft);
        clear(pCurr->pRight);
        delete pCurr;
    }
}
```


As was the case for the `contains` method, we have an empty-tree base case here. If there are no nodes in the tree, there is nothing to do, so we invert the base case condition and only do something if the value of `pCurr` is non-zero. This method uses a post-order traversal of the tree, since we need to remove the subtrees before deleting a node. If we tried to delete the current node first, the values of `pLeft` and `pRight` could be changed by the time we try to use them in recursive calls. Therefore, we recursively delete the left subtree, recursively delete the right subtree, and then delete the current node with the `delete pCurr` statement. 


#### `copy` method


The `copy` method is used by the copy constructor and the assignment operator override. There is no corresponding public method, only the private, recursive method:


```
template <class T>
typename BST<T>::Node *BST<T>::copy(Node* pOtherCurr) {
    if(pOtherCurr != 0) {
        Node *pCurr = new Node(pOtherCurr->data);
        n++;
        pCurr->pLeft = copy(pOtherCurr->pLeft);
        pCurr->pRight = copy(pOtherCurr->pRight);


        return pCurr;
    } else {
        return 0;
    }
}
```


The `copy` method returns a pointer to a `Node`, which in each case will be the root of a subtree and eventually the root of the whole tree. Its parameter is a pointer to a node *in the tree we are copying from*. This method uses a pre-order traversal of the other tree, making identical nodes in this tree as we go along. So, for a node in the other tree referred to by the `pOtherCurr` pointer, we make our new identical node referred to by the `pCurr` pointer. Then, we set `pCurr->pLeft` to the result of a recursive call on `pOtherCurr->pLeft`, and `pCurr->pRight` to the result of a recursive call on `pOtherCurr->pRight`. Then, we return the value of `pCurr`. The base case is when `pOtherCurr` refers to an empty subtree, in which case the method returns the value zero. 


#### `insert` method


The `insert` method adds a new element to the BST, such that the binary search tree properties still apply after the insertion. Since duplicates are not allowed in a BST, not every call to `insert` will actually add a new element to the tree. So, we will design the method to return a `bool` -- `true` if the value was inserted (i.e., it was not a duplicate element) or `false` if the value was not inserted (i.e., it was a duplicate element). 


The `insert` method begins with a search, similar to that in the `contains` method. The goal is to find the leaf position where the value should be added to the tree, or to find the value already in the tree. Instead of recursion, here we will use iteration, and we will maintain a `pParent` pointer along the way, similar to how we moved both `pCurr` and `pPrev` through one of our linked lists. Here is the code for `insert`:


```
template <class T>
bool BST<T>::insert(const T& val) {
    // set up pointers to current node and its parent.
    Node *pCurr = pRoot, *pParent = 0;


    // search for the value's location in the tree. This code illustrates
    // how to search non-recursively, while the contains method uses 
    // recursion. It is easier to keep track of the parent pointer if we use
    // iteration. 
    while(pCurr != 0) {
        pParent = pCurr;
        if(val < pCurr->data) {
            // search in left subtree
            pCurr = pCurr->pLeft;
        } else if(val > pCurr->data) {
            // search in right subtree
            pCurr = pCurr->pRight;
        } else {
            // val == pCurr->data means we are inserting a duplicate
            return false;
        }
    } // while


    // now, pCurr is the (empty) spot where the value should be inserted,
    // and pParent is the parent node. Find out which side we are adding on,
    // and add the new node. Special case is a previously empty tree.
    Node *pN = new Node(val);
    if(pRoot == 0) {
        pRoot = pN;
    } else {
        if(val < pParent->data) {
            pParent->pLeft = pN;
        } else {
            pParent->pRight = pN;
        }
    }


    n++;
    return true;
}
```


Assuming the `while` loop terminates, the `pCurr` pointer is in the empty leaf position where the new element should be inserted. So, the code makes a new node, and then uses the `pParent` pointer to determine whether the new element is a left or right child of the parent element. Once the appropriate pointer has been set, we increment the size variable and return `true`. 


#### `remove` method


Similar to the `insert` method, our `remove` method will return a `bool`: true if the specified element was removed from the tree, or false if the element was not in the tree to begin with. The `remove` method is the most complicated of the methods in the `BST` class, so we will break the code into three chunks to make it easier to understand.


In the first phase of the `remove` method, we use iteration to find the location of the value to be deleted, or return `false` if the value is not in the tree: 


```
template <class T>
bool BST<T>::remove(const T& val) {
    // establish pointers to the current node and its parent
    Node *pCurr = pRoot, *pParent = 0;


    // loop until we find an empty space (val not in tree), or the node
    // containing val. Update so that pCurr points to the space or node,
    // and pParent points to the parent of pCurr. 
    while(pCurr != 0 && pCurr->data != val) {
        pParent = pCurr;
        if(val < pCurr->data) {
            // search left subtree
            pCurr = pCurr->pLeft;
        } else {
            // search right subtree
            pCurr = pCurr->pRight;
        }
    }


    // empty space? we do nothing!
    if(pCurr == 0) {
        return false;
    }


```


Once we have reached the end of the above block of code, `pCurr` points to the node with the value to remove from the tree, and `pParent` points to that node's parent. What happens next depends on the number of children `pCurr`'s node has.


Suppose we are removing a node with no children, i.e., a leaf node, like node 3 in this partial BST:


<img src="https://doane.instructure.com/files/982995/download?download_frd=1" alt="Removing a node with no children" title="Removing a node with no children"/>


This case is pretty simple -- we just delete `pCurr` and set `pParent->pLeft` to zero. 


Removing a node with one child is just as easy. Suppose we are removing node 8 from this partial tree:


<img src="https://doane.instructure.com/files/982997/download?download_frd=1" alt="Removing a node with one child" title="Removing a node with one child"/>


Here we can set `pParent->pRight` to `pCurr->pLeft`, then delete `pCurr`. 


In the situation where the node we wish to remove has two children, things are more difficult. Consider this tree, and suppose we are removing node 10:


<img src="https://doane.instructure.com/files/982999/download?download_frd=1" alt="Removing a node with two children" title="Removing a node with two children"/>


What we will do is find node 10's *inorder successor*, i.e., the smallest value in node 10's right subtree. In this image, node 12 is node 10's inorder successor. Then, we will swap the data in the two nodes, and update `pCurr` and `pParent` to the position of the inorder successor node, like this:


<img src="https://doane.instructure.com/files/983018/download?download_frd=1" alt="Swap with inorder successor" title="Swap with inorder successor"/>


Now, node 12 has been repositioned to maintain the BST properties, while node 10, which violates the BST properties, will be removed. Note that the inorder successor node will always be a node with zero or one children, because it can never have a left child. If it did, the left branch would lead to a smaller value, making it not the inorder successor. 


The second section of code performs this kind of operation if the value we want to remove is in a node with two children: 


```
    // otherwise, what we do depends on number of children the node has.
    // If node containing val has two children, we make some modifications
    // so that the node to delete will have zero or one child.
    if(pCurr->pLeft != 0 && pCurr->pRight != 0) {
        // find inorder successor of this node -- smallest value in the right
        // subtree. Start at the root of right subtree...
        Node* pInorderSuccessor = pCurr->pRight;
        Node* pIoSParent = pCurr;


        // ... then go as far left as possible in the right subtree
        while(pInorderSuccessor->pLeft != 0) {
            pIoSParent = pInorderSuccessor;
            pInorderSuccessor = pInorderSuccessor->pLeft;
        }


        // move data from inorder successor to current node
        pCurr->data = pInorderSuccessor->data;


        // update pCurr and pParent to refer to the inorder successor node and
        // its parent. Since we went as far left as possible in this subtree,
        // pCurr's node will have at most one child, and the remaining code 
        // will remove the node (now containing the value we wanted to remove 
        // in the first place) without doing anything else special. 
        pCurr = pInorderSuccessor;
        pParent = pIoSParent;
    }


```


The final section of code deals with the zero or one-child cases, which are the only options, thanks to the inorder successor swap code above. Here, we will manage *three* pointers: `pCurr`, which points to the node to remove, `pParent`, that node's parent, and `pReplacement`, the node that will take `pCurr`'s place in the tree: 


```
    // now pCurr points to a node with zero or one child. pCurr
    // is the node to delete. First, get a pointer to the node to replace
    // pCurr's node with. If there are zero children, pReplacement will be 0.
    Node *pReplacement;
    if(pCurr->pLeft != 0) {
        pReplacement = pCurr->pLeft;
    } else {
        pReplacement = pCurr->pRight;
    }


    // move the replacement node into pCurr's position in the tree
    if(pCurr == pRoot) {
        // special case for deleting current root node
        pRoot = pReplacement;
    } else {
        // attach replacement node to proper child of the parent
        if(pCurr == pParent->pLeft) {
            pParent->pLeft = pReplacement;
        } else {
            pParent->pRight = pReplacement;
        }
    }


    // finally! delete the current node
    delete pCurr;
    n--;
    return true;
}


```


### BST time complexities


At the outset, we said that BSTs were good for fast membership testing. For the simple BST we have implemented, this holds true as long as the BST does not become a chain. If our BST is full or complete, then then time complexity for our operations will be the depth of the tree, *O(lg n)*, where *n* is the number of values in the tree, and *lg* is the base-2 logarithm. 


On the other hand, if the BST does become a chain, then all of our operations become *O(n)* in the worst case, i.e., no better than the performance of a linked list. 


This table summarizes the best, worst, and average time complexities of our BST. 


| Operation | *B(n)* | *A(n)* | *W(n)* | 
| ---------- | ---------- | ---------- | ---------- |
| `contains` | 1 | *O(lg n)* | *O(n)* | 
| `insert` | 1 | *O(lg n)* | *O(n)* | 
| `remove` | 1 | *O(lg n)* | *O(n)* | 


The other operations in our BST are either constant-time (`size`, `isEmpty`) or linear-time (`copy`, `clear`, printing). 


### More advanced BSTs


"Real world" BSTs are modified so that they always maintain a nearly complete tree, avoiding chains. They do this without an undue time penalty, so that the complexity of the contains, insert, and remove operations all become *O(lg n)* in the worst case. Two examples of trees like this are AVL trees and Red-Black trees. Since we are just introducing BSTs in this course, we will not delve into these structures here. 


### Sample application: spell checking


**[For this section, refer to the `module06\2-SpellCheck\SpellCheck.cpp` file from the course's git repository.]**


For this module's sample app, we will develop a very simple spell-checking system. The strategy is this: load a collection of correctly-spelled words into a BST. Then, examine each word in the file we want to spellcheck. If a word is *not* in the BST, then we will assume it is spelled incorrectly, and print it out to the standard output. 


Since the heavy lifting is done by the `BST` class, the main program for the spell-checking app is pretty simple:


```
int main() {
    // read dictionary words into a BST
    BST<std::string> dictionary;
    std::ifstream dictionaryFile("dictionary.txt");
    std::string word;
    while(dictionaryFile >> word) {
        dictionary.insert(word);
    }
    dictionaryFile.close();


    // read file to check from standard input
    while(std::cin >> word) {
        word = stripNonAlpha(toLower(word));
        // dump all words not in the dictionary to standard output
        if(word != "" && !dictionary.contains(word)) {
            std::cout << word << std::endl;
        }
    }


    return EXIT_SUCCESS;
}
```


First, we read all of the words in `dictionary.txt` into a BST named `dictionary`. There are about 77,000 correctly-spelled words in the file, one per line. We have shuffled the contents of the file, though, so that they are not in any particular order, as you can see from the first few lines of the file:


```
grog
dirtiest
counteraction
exfoliated
cointreau
breeder
jape
pettifogging
attenuating
sewed
...
...
```


If we had the words in the dictionary in alphabetical order, then our BST would be a chain, since each word would be larger than the last. This would make our spellchecker really, really slow! By having the dictionary file in random order, our BST will be shallower, and the performance of the application will be much faster. 


Our program reads the file to spellcheck from standard input, word by word. From a bash command line, we could check the spelling of the novel *War and Peace* by piping the contents of the file into the app, via this command:


```
cat war-and-peace.txt | ./SpellCheck
```


Punctuation and numbers are removed from each word, and the word is converted to lower case to match the words in the dictionary. Then, we make a call to see if the BST contains the word. If so, we assume the word is spelled correctly and take no action. If the word is not in the BST, we assume the word is spelled incorrectly, and output it to the standard output. 


#### An object lesson on time complexity


Often there are several different data structures we could use to solve a particular problem. All things being equal, we should choose the data structure with the lower time complexity to solve the problem. 


This sample application shows a very good example of why we should do this. The file `BadSpellCheck.cpp` is a copy of the spellchecker, modified to use a C++ Standard Template Library `list` object for the dictionary instead of a BST. The `list` class is the industrial-strength, built-in doubly-linked list data structure that is distributed with the C++ language. 


We would expect that our BST dictionary to take approximately *O(lg n)* time to see if a word is in the dictionary, where *n* is the size of the dictionary. *lg 77000* is approximately 17, so the BST should be able to check a word in 17 steps or less. 


On the other hand, the `list` requires *O(n)* time to search. I.e., we expect the `list` to take *77,000* steps to see if a word is misspelled! 


You can execute the `list`-based spell checker on your system, to see what this difference looks like in real time, with the command:


```
cat war-and-peace.txt | ./BadSpellCheck
```


*Warning:* you might want to get some coffee or wash the dishes while the `list`-based system runs.