#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 6 simple binary search tree.
 * 
 * BST is a simple binary search tree. It allows insert, contains, and remove
 * methods, and supports similar administrative methods as earlier structures:
 * clear, isEmpty, size, overrides for assignment and stream insertion, etc. 
 */
template <class T> class BST {
private:
    /**
     * @brief Node in the binary search tree.
     * 
     * Node is a private inner class of BST. It represents a single node in the
     * tree. Each node has a payload of type T, and pointers to the left and
     * right subtrees below the node. 
     */
    class Node {
    public:
        /**
         * @brief Construct a new Node object.
         * 
         * Make a new node with the specified data value, and null left and
         * right pointers.
         * 
         * @param val Value this node will hold. 
         */
        Node(const T& val) : data(val), pLeft(0), pRight(0) { }

        /**
         * @brief Node payload.
         * 
         * Type T payload of the node. Assumed to support assignment, equality
         * testing, less and greater than, copy constructor, and stream 
         * insertion.
         */
        T data;

        /**
         * @brief Left tree pointer.
         * 
         * Pointer to the node at the root of the left subtree under this node,
         * zero if there is no subtree. 
         */
        Node *pLeft;

        /**
         * @brief Right tree pointer.
         * 
         * Pointer to the node at the root of the right subtree under this 
         * node, zero if there is no subtree. 
         */
        Node *pRight;
    };

public:
    /**
     * @brief BST default constructor.
     * 
     * Make an initially empty BST.
     */
    BST() : pRoot(0), n(0u) { }

    /**
     * @brief BST copy constructor.
     * 
     * Make a new, deep-copy BST, just like the parameter tree.
     * 
     * @param tree Reference to the BST to copy.
     */
    BST(const BST<T> &tree) { pRoot = copy(tree.pRoot); }

    /**
     * @brief Destructor.
     * 
     * Free the memory used by this list. 
     */
    ~BST() { clear(); }

    /**
     * @brief Clear the BST.
     * 
     * Remove all the elements from this tree. 
     */
    void clear();

    /**
     * @brief Search the BST for a value.
     * 
     * @param val Value to search for.
     * @return true if the value is in the BST, false otherwise. 
     */
    bool contains(const T &val) const { return contains(val, pRoot); }

    /**
     * @brief Add a value to the BST.
     * 
     * Adds a new value to the tree. If the value is already in the BST, no 
     * action is taken and the tree is not changed. 
     * 
     * @param val Value to insert into the tree. 
     * 
     * @return true if the value was inserted, false if it was a duplicate.
     */
    bool insert(const T &val);

    /**
     * @brief Determine if the BST is empty.
     * 
     * Convenience method to test if the BST contains no elements.
     * 
     * @return true if the list is empty, false otherwise.
     */
    bool isEmpty() { return n == 0u; }

    /**
     * @brief BST stream insertion override.
     * 
     * Writes a pre-order traversal printing of the tree to the specified
     * output stream.
     * 
     * @param out std::ostream object to write tree contents to.
     * @param tree BST object to print.
     * @return std::ostream& Reference to the object written to.
     */
    friend std::ostream &operator<<(std::ostream &out, const BST<T> & tree) {
        out << "[";
        tree.preOrderPrint(out, tree.pRoot);
        out << "]";
        return out;
    }

    /**
     * @brief BST assignment operator override.
     * 
     * Makes this tree a new, deep-copy clone of the specified BST.
     * 
     * @param tree BST to copy from.
     * @return BST<T>& Reference to this object, for chaining. 
     */
    BST<T> &operator=(const BST<T> &tree);

    /**
     * @brief Remove an element from the BST.
     * 
     * Remove the specified value from the BST. If the value was not in the
     * tree to begin with, no action is taken and the tree is not modified.
     * 
     * @param val Value to remove from the BST. 
     * 
     * @return true if the value was removed from the tree, false if it was not
     * in the tree initially.
     */
    bool remove(const T &val);

    /**
     * @brief Remove the maximum element from the BST.
     * 
     * Finds and removes the maximum element from the BST. The value that was
     * the maximum is returned.
     * 
     * @returns Type T element that was the maximum element in the tree.
     * 
     * @throws std::out_of_range if the tree is empty.
     */
    T removeMax();

    /**
     * @brief Get the size of this BST.
     * 
     * @return size_t Number of elements in the tree. 
     */
    size_t size() { return n; }

private:
    /**
     * @brief Pointer to the root node of the tree. 
     * 
     */
    Node *pRoot;

    /**
     * @brief Number of elements in the tree.
     * 
     */
    size_t n;

    /**
     * @brief Clear helper method.
     * 
     * Private, recursive clear method.
     * 
     * @param pCurr Pointer to the root of the subtree to remove.
     */
    void clear(Node *pCurr);

    /**
     * @brief Contains helper method.
     * 
     * Private, recursive contains method.
     * 
     * @param val Value to search the tree for.
     * @param pCurr Pointer to the root of the subtree to search. 
     * @return true if the subtree contains the value, false otherwise.
     */
    bool contains(const T &val, Node *pCurr) const;

    /**
     * @brief Copy helper method.
     * 
     * Private, recursive copy method.
     * 
     * @param pOtherCurr Pointer to the root of the subtree *in the other tree*
     * @return Node* Pointer to the node added *to this tree*
     */
    Node *copy(Node *pOtherCurr);

    /**
     * @brief Stream insertion helper method.
     * 
     * Private, recursive helper method for stream insertion.
     * 
     * @param out Output stream to print to.
     * @param pCurr Pointer to the root of the subtree to print.
     */
    void preOrderPrint(std::ostream &out, Node *pCurr) const;

};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

// doctest unit test for copy constructor 
TEST_CASE("testing BST copy constructor") {
    BST<int> tree1;
    int values[10] = {80, 9, 3, 34, 33, 63, 81, 55, 86, 9};
    for(int i = 0; i < 10; i++) {
        tree1.insert(values[i]);
    }

    // create a copy of tree1
    BST<int> tree2(tree1);

    // "print" both to strings, see if they are equal
    std::ostringstream oss1, oss2;

    oss1 << tree1;
    oss2 << tree2;

    CHECK(oss1.str() == oss2.str());
}

/*
 * Public clear function implementation.
 */
template <class T>
void BST<T>::clear() {
    clear(pRoot);
    n = 0u;
    pRoot = 0;
}

// doctest unit test for clear method
TEST_CASE("testing BST<T>::clear()") {
    BST<int> tree1;
    int values[10] = {80, 9, 3, 34, 33, 63, 81, 55, 86, 9};
    for(int i = 0; i < 10; i++) {
        tree1.insert(values[i]);
    }

    tree1.clear();

    // did the clear empty the tree?
    CHECK(0u == tree1.size());

    // are there 0 elements in the print?
    std::ostringstream oss;
    oss << tree1;

    CHECK(oss.str() == "[]");
}

/*
 * Private recursive clear function implementation.
 */
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

/* 
 * Private recursive contains function implementation.
 */
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

// doctest unit test for contains method
TEST_CASE("testing BST<T>::contains()") {
    BST<char> tree;
    std::string values ="I love data structures!";
    for(size_t i = 0u; i < values.size(); i++) {
        tree.insert(values[i]);
    }

    // verify tree contains all the characters we added
    for(size_t i = 0u; i < values.size(); i++) {
        CHECK(tree.contains(values[i]));
    }

    // verify it does not contain some others
    CHECK(!tree.contains('Q'));
    CHECK(!tree.contains('.'));
    CHECK(!tree.contains('1'));

}

/* 
 * Private recursive copy function implementation.
 */
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

// copy is private, so it is tested indirectly in copy constructor and
// assignment operator tests

/*
 * Insert function implementation.
 */
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

// doctest unit test for the insert method
TEST_CASE("testing BST<T>::insert()") {
    BST<int> tree;

    CHECK(0 == tree.size());
    CHECK(true == tree.insert(1));
    CHECK(1 == tree.size());
    CHECK(tree.contains(1));

    CHECK(true == tree.insert(-2));
    CHECK(2 == tree.size());
    CHECK(tree.contains(-2));

    CHECK(false == tree.insert(-2));
    CHECK(2 == tree.size());
    CHECK(tree.contains(-2));

    CHECK(true == tree.insert(2));
    CHECK(3 == tree.size());
    CHECK(tree.contains(2));
}

// doctest unit test for isEmpty
TEST_CASE("testing BST<T>::isEmpty()") {
    BST<int> tree;

    CHECK(tree.isEmpty());
    tree.insert(1);
    CHECK(!tree.isEmpty());
    tree.clear();
    CHECK(tree.isEmpty());
}

/*
 * Assignment operator override.
 */
template <class T>
BST<T> &BST<T>::operator=(const BST<T> &tree) {
    // clear existing data, if any
    clear();

    // copy the other tree's data
    pRoot = copy(tree.pRoot);

    return *this;
}

// doctest unit test for assignment operator
TEST_CASE("testing BST<T>::operator=()") {
    BST<int> tree1;
    int values[10] = {80, 9, 3, 34, 33, 63, 81, 55, 86, 9};
    for(int i = 0; i < 10; i++) {
        tree1.insert(values[i]);
    }

    // create a copy of tree1
    BST<int> tree2;

    // add some extra before assignment; these should be removed before the
    // copy
    tree2.insert(5);
    tree2.insert(7);
    tree2 = tree1;

    // "print" both to strings, see if they are equal
    std::ostringstream oss1, oss2;

    oss1 << tree1;
    oss2 << tree2;

    CHECK(oss1.str() == oss2.str());
}

/*
 * Private print function implementation.
 */
template <class T>
void BST<T>::preOrderPrint(std::ostream &out, Node *pCurr) const {
    // this recursive method prints values using a preorder traversal --
    // print current value, then print the left subtree, then print the
    // right subtree
    if(pCurr != 0) {
        out << pCurr->data << " ";

        preOrderPrint(out, pCurr->pLeft);
        preOrderPrint(out, pCurr->pRight);
    }
}

// doctest unit test for stream insertion and preOrderPrint
TEST_CASE("testing BST<T>::operator<<") {
    BST<char> tree;

    std::string racecar = "racecar";
    for(size_t i = 0; i < racecar.size(); i++) {
        tree.insert(racecar[i]);
    }

    // print to a string and see if it looks right
    std::ostringstream oss;

    oss << tree;

    CHECK(oss.str() == "[r a c e ]");
}

/*
 * Remove function implementation.
 */
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

// doctest unit test for remove method
TEST_CASE("testing BST<T>::remove()") {
    BST<char> tree;
    std::string data = "datastructures";
    for(size_t i = 0; i < data.size(); i++) {
        tree.insert(data[i]);
    }

    // check original values
    std::ostringstream oss;
    oss << tree;
    CHECK(oss.str() == "[d a c t s r e u ]");
    
    // remove value not in the tree
    CHECK(false == tree.remove('q'));
    std::ostringstream oss1;
    oss1 << tree;
    CHECK(oss1.str() == "[d a c t s r e u ]");
    CHECK(8 == tree.size());

    // remove node with no children
    CHECK(true == tree.remove('e'));
    std::ostringstream oss2;
    oss2 << tree;
    CHECK(oss2.str() == "[d a c t s r u ]");
    CHECK(7 == tree.size());

    //remove node w/ one child
    CHECK(true == tree.remove('a'));
    std::ostringstream oss3;
    oss3 << tree;
    CHECK(oss3.str() == "[d c t s r u ]");
    CHECK(6 == tree.size());

    // remove node with 2 children
    CHECK(true == tree.remove('t'));
    std::ostringstream oss4;
    oss4 << tree;
    CHECK(oss4.str() == "[d c u s r ]");
    CHECK(5 == tree.size());

    // remove root
    CHECK(true == tree.remove('d'));
    std::ostringstream oss5;
    oss5 << tree;
    CHECK(oss5.str() == "[r c u s ]");
    CHECK(4 == tree.size());

    BST<int> tree2;
    
    // remove from empty tree
    CHECK(false == tree2.remove(13));
    std::ostringstream oss6;
    oss6 << tree2;
    CHECK(oss6.str() == "[]");
    CHECK(0 == tree2.size());

    // remove root from tree with only one subtree
    for(int i = 0; i < 5; i++) {
        tree2.insert(i);
    }
    CHECK(true == tree2.remove(0));
    std::ostringstream oss7;
    oss7 << tree2;
    CHECK(oss7.str() == "[1 2 3 4 ]");
    CHECK(4 == tree2.size());
}

// doctest unit test for size method
TEST_CASE("testing BST<T>::size()") {
    BST<int> tree;

    CHECK(0 == tree.size());
    tree.insert(1);
    CHECK(1 == tree.size());
    tree.insert(2);
    CHECK(2 == tree.size());
    tree.clear();
    CHECK(0 == tree.size());
}

/*
 * removeMax function implementation.
 */
template <class T>
T BST<T>::removeMax() {
    // TODO: write the removeMax method, AFTER YOU HAVE WRITTEN THE TESTS.
    // Don't forget to throw a std::out_of_range exception if the tree is
    // empty.

    return T(); // stub, remove
}

// doctest unit test for the removeMax method
TEST_CASE("testing BST<T>::removeMax") {
    // TODO: write unit tests to validate the function. FOR THIS ASSIGNMENT,
    // WRITE THE TESTS FIRST, BEFORE YOU WRITE THE METHOD. Do not forget to 
    // test the exception.

    CHECK(false);   // stub, remove

}