#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 2 simple, generic singly-linked list.
 *
 * SimpleSLL is a simple, generic singly-linked list data structure. It only
 * allows inserting at the front of the list, but it does support index-based
 * get, set, and remove operations. The list also provides a contains method,
 * and the administrative methods clear, isEmpty, and size. 
 */
template <class T> class SimpleSLL {

private:
    /**
     * @brief Node in the singly-linked list.
     *
     * Node is a private inner class of SimpleSLL. The class represents a 
     * single node in the list. Each node has a payload of type T and a 
     * pointer to the next node in the list. 
     */
    class Node {
    public:
        /**
         * @brief Default constructor. 
         *
         * Make a new Node with default data and next pointer set to zero.
         */
        Node() : data(), pNext(0) { }

        /**
         * @brief Initializing constructor. 
         *
         * Make a new node with the specified data and next pointer values.
         *
         * @param d Data value for the node.
         * @param pN Pointer to the next node in the list, or 0 if this is the
         * last Node in the list.
         */
        Node(const T &d, Node *pN) : data(d), pNext(pN) { }

        /**
         * @brief Node payload.
         *
         * Type T payload of the node. Assumed to support assignment, equality 
         * testing, copy constructor, and stream insertion.
         */
        T data;

        /**
         * @brief Next node pointer. 
         *
         * Pointer to the next node in the list, or 0 if this is the last node.
         */
        Node *pNext;
    };

public:
    /**
     * @brief Default list constructor. 
     *
     * Made an initially empty list.
     */
    SimpleSLL() : pHead(0), n(0) { }

    /**
     * @brief Destructor. 
     *
     * Free the memory used by this list. 
     */
    ~SimpleSLL() { clear(); }

    /**
     * @brief Add a value to the front of the list. 
     *
     * @param d Value to add to the list.
     */
    void add(const T &d);

    /**
     * @brief Clear the list.
     *
     * Remove all the elements from the list.
     */
    void clear();

    /**
     * @brief Search the list for a specified value.
     *
     * Searches for a value and returns the index of the first occurrence
     * of the value in the list, or -1 if the value is not in the list. 
     *
     * @param d Value to search for.
     *
     * @return Index of the first occurrence of d in the list, or -1 if it is
     * not in the list.
     */
    int contains(const T &d) const;

    /**
     * @brief Get a value.
     *
     * Get the value at a specified index in the list.
     * 
     * @param idx Index of the value to get.
     *
     * @throws std::out_of_range if the index is past the end of the list.
     * 
     * @return Value at location idx in the list.
     */
    T get (size_t idx) const;

    /**
     * @brief Determine if the list is empty.
     *
     * Convenience method to test if the list contains no elements. 
     *
     * @return true if the list is empty, false otherwise.
     */
    bool isEmpty() const { return size() == 0; }

    /**
     * @brief Remove an element.
     *
     * Remove the value at a specified index in the list.
     *
     * @param idx Index of the element to remove.
     *
     * @throws std::out_of_range if the index is past the end of the list.
     *
     * @return Value that was at location idx.
     */
    T remove(size_t idx);

    /**
     * @brief Print the list
     *
     * Print the contents of this list to the standard output.
     */
    void print() const;

    /**
     * @brief Change a list element. 
     *
     * Change the value at a specified index to another value.
     *
     * @param idx Index of the value to change.
     *
     * @throws std::out_of_range if the index is past the end of the list.
     *
     * @param d New value to place in position idx.
     */
    void set(size_t idx, const T &d);

    /**
     * @brief Get list size.
     *
     * Get the number of integers in the list.
     * 
     * @return The number of integers in the list.
     */
    size_t size() const { return n; }

private:
    /**
     * Pointer to the first Node in the list, or 0 if the list is empty.
     */
    Node *pHead;
    
    /**
     * Number of integers in the list.
     */
    size_t n;
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

/*
 * Add d to the front of the list.
 */
template <class T> 
void SimpleSLL<T>::add(const T &d) {
    // create the new node
    Node *pN = new Node(d, pHead);

    // change head pointer to point to the new node
    pHead = pN;

    // increment size
    n++;
}

// doctest unit test for the add method
TEST_CASE("testing SimpleSLL<T>::add") {
    SimpleSLL<int> list;

    // each addition should happen at the front, and the size should go up by
    // one each time
    list.add(1);
    CHECK(list.get(0) == 1);
    CHECK(list.size() == 1u);

    list.add(2);
    CHECK(list.get(0) == 2);
    CHECK(list.size() == 2u);
}

/*
 * Delete all list nodes.
 */
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

// doctest unit test for the clear method
TEST_CASE("testing SimpleSLL<T>::clear") {
    SimpleSLL<int> list;

    // add some list elements
    for(int i = 0; i < 100; i++) {
        list.add(i);
    }

    // clear should make size equal zero
    list.clear();
    CHECK(list.size() == 0u);
}

/*
 * Search the list for value d.
 */
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

// doctest unit test for the contains method
TEST_CASE("testing SimpleSLL<T>::contains") {
    SimpleSLL<char> list;

    // populate the list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.add(c);
    }

    // search for 1st element in list
    CHECK(list.contains('Z') == 0);

    // search for last element in list
    CHECK(list.contains('A') == 25);

    // search for something in the middle
    CHECK(list.contains('M') == 13);

    // search for something not in list
    CHECK(list.contains('a') == -1);
}

/*
 * Get the value at location idx.
 */
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

// doctest unit test for the get method
TEST_CASE("testing SimpleSLL<T>::get") {
    SimpleSLL<char> list;

    // populate list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.add(c);
    }

    // get first element
    CHECK(list.get(0) == 'Z');

    // get last element
    CHECK(list.get(25) == 'A');

    // get something in the middle
    CHECK(list.get(13) == 'M');

    // check exception handling when access is beyond list
    bool flag = true;
    try {
        list.get(26); // list element 26 does not exist
        flag = false; // this line should not be reached, due to an exception
    } catch(std::out_of_range oor) {
        // verify flag wasn't modified
        CHECK(flag);
    }
}

/*
 * Remove node at location idx. 
 */
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

// doctest unit test for the remove method
TEST_CASE("testing SimpleSLL<T>::remove") {
    SimpleSLL<char> list;

    // populate list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.add(c);
    }

    // remove first element
    CHECK(list.remove(0) == 'Z');
    CHECK(list.size() == 25);
    CHECK(list.get(0) == 'Y');

    // remove last element
    CHECK(list.remove(24) == 'A');
    CHECK(list.size() == 24);
    CHECK(list.get(23) == 'B');

    // remove something in the middle
    CHECK(list.remove(12) == 'M');
    CHECK(list.size() == 23);
    CHECK(list.get(12) == 'L');

    // check exception handling when access is beyond end of the list
    bool flag = true;
    try {
        list.remove(26);    // illegal access; element 26 doesn't exist
        flag = false;       // this line should not be reached due to exception
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Print the list to standard output.
 */
template <class T> 
void SimpleSLL<T>::print() const {
    using namespace std;

    cout << "[";

    // initialize cursor
    Node *pCurr = pHead;

    // iterate through list
    while(pCurr != 0) {
        cout << pCurr->data;

        // no comma for last node
        if(pCurr->pNext != 0) {
            cout << ", ";
        }

        pCurr = pCurr->pNext;
    }

    cout << "]" << endl;
}

/* 
 * Change the value at location idx to d.
 */
template <class T> 
void SimpleSLL<T>::set(size_t idx, const T &d) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in SimpleSLL::set()");
    }

    // initialize cursor
    Node *pCurr = pHead;

    // iterate to location
    for(size_t i = 0u; i < idx; i++) {
        pCurr = pCurr->pNext;
    }

    // change data in location idx to d
    pCurr->data = d;
}

// doctest unit test for the set method
TEST_CASE("testing SimpleSLL<T>::set") {
    SimpleSLL<char> list;

    // populate the list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.add(c);
    }

    // set first element
    list.set(0, 'z');
    CHECK(list.get(0) == 'z');

    // set last element
    list.set(25, 'a');
    CHECK(list.get(25) == 'a');

    // set something in the middle
    list.set(13, 'm');
    CHECK(list.get(13) == 'm');

    // check exception handling for index beyond end of list
    bool flag = true;
    try {
        list.set(26, 'X');  // this is illegal; index doesn't exist
        flag = false;       // this should never be reached, due to the exception
    } catch(std::out_of_range oor) {
        CHECK(flag);    // if exception was handled properly, should be true
    }
}
