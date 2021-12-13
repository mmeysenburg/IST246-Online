#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 4 generic singly-linked list, supporting iterators.
 *
 * IteratorSLL is a generic singly-linked list data structure. It 
 * allows inserting at the front of the list, and supports index-based
 * get, set, and remove operations. The list also provides a contains method,
 * and the administrative methods clear, isEmpty, and size. IteratorSLL also 
 * has a copy constructor, and overrides the assignment and stream insertion 
 * operators. IteratorSLL provides front and end methods to access iterators 
 * that move through the list from front to back.  
 */
template <class T> class IteratorSLL {

private:
    /**
     * @brief Node in the singly-linked list.
     *
     * Node is a private inner class of IteratorSLL. The class represents a 
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
     * @brief IteratorSLL iterator.
     * 
     * This class allows IteratorSLL users to iterate through the list, from 
     * front to back, without exposing the pointer structure of the list, and 
     * without incurring the time complexity of successive calls to the 
     * index-based get() and set() methods. 
     */ 
    class Iterator {
    public:
        /**
         * @brief Iterator dereferencing operator.
         * 
         * This override of the dereferencing operator allows IteratorSLL 
         * users to access and / or change the payload of a node in the list.
         * 
         * @throws std::out_of_range if the iterator is past the end of 
         * the list.
         */
        T &operator*();

        /**
         * @brief Iterator equality operator.
         * 
         * This override of the equality operator allows IteratorSLL users to 
         * compare two iterators, to determine if they refer to the same node 
         * in the list. 
         */
        bool operator==(const Iterator &other) const {
            return pCurr == other.pCurr;
        }

        /**
         * @brief Interator inequality operator.
         * 
         * This override of the inequality operator allows IteratorSLL users to
         * compare two iterators, to determine if they refer to different nodes 
         * in the list.
         */
        bool operator!=(const Iterator &other) const {
            return pCurr != other.pCurr;
        }

        /**
         * @brief Iterator increment operator.
         * 
         * This override of the postfix increment operator allows IteratorSLL 
         * users to move an iterator from one node to the next node in the 
         * list. 
         * 
         * @param dummy Dummy integer parameter to indicate we are overriding 
         * the postfix increment operator rather than the prefix operator
         * 
         * @throws std::out_of_range if the iterator is past the end of 
         * the list.
         */
        Iterator &operator++(int dummy);

        // Make IteratorSLL a friend class, so it can access the private 
        // constructor
        friend class IteratorSLL;

    private:
        /**
         * @brief Initializing constructor.
         * 
         * This constructor makes an iterator that refers to the Node at the
         * end of the specified pointer. The constructor is private, so that 
         * the only way to get an iterator is via the IteratorSLL front() 
         * and end() methods. 
         * 
         * @param pC Node this iterator should refer to.
         */
        Iterator(IteratorSLL<T> &o, Node *pC) : outer(o), pCurr(pC) { }

        IteratorSLL<T> &outer;

        /** 
         * Pointer to the Node this iterator refers to.
         */
        Node *pCurr;

    };

    /**
     * @brief Default list constructor. 
     *
     * Made an initially empty list.
     */
    IteratorSLL() : numFOs(0ul), pHead(0), n(0u) { }

    /**
     * @brief Copy construstor.
     * 
     * Make a new, deep-copy list, just like the parameter list.
     * 
     * @param otherList Reference to the IteratorSLL to copy.
     */
    IteratorSLL(const IteratorSLL<T> &otherList) : 
        numFOs(0ul), pHead(0), n(0u) { copy(otherList); }

    /**
     * @brief Destructor. 
     *
     * Free the memory used by this list. 
     */
    ~IteratorSLL() { clear(); }

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
     * Searches for a value and returns an iterator on the first occurrence
     * of the value in the list, or end if the value is not in the list. 
     *
     * @param d Value to search for.
     *
     * @return Iterator on the first occurrence of d in the list, or end if
     * d is not in the list.
     */
    Iterator contains(const T &d) const;

    /**
     * @brief Get an Iterator representing the end of the list.
     * 
     * @return An Iterator positioned after the last node in the list.
     */
    Iterator end() { numFOs++; return Iterator(*this, 0); } 

    /**
     * @brief Get an Iterator on the first node of the list.
     * 
     * @return An Iterator positioned on the first node of the list.
     */
    Iterator front() { numFOs++; return Iterator(*this, pHead); }

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
    T get (unsigned idx) const;

    /**
     * @brief Determine if the list is empty.
     *
     * Convenience method to test if the list contains no elements. 
     *
     * @return true if the list is empty, false otherwise.
     */
    bool isEmpty() const { return size() == 0u; }

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
    T remove(unsigned idx);

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
    void set(unsigned idx, const T &d);

    /**
     * @brief Get list size.
     *
     * Get the number of integers in the list.
     * 
     * @return The number of integers in the list.
     */
    unsigned size() const { return n; }

    /**
     * @brief Assignment operator.
     * 
     * Override of the assignment operator to work with IteratorSLL objects. 
     * Makes this list a deep-copy, identical structure as the parameter 
     * IteratorSLL. 
     * 
     * @param list IteratorSLL to copy from
     * 
     * @return Reference to this object.
     */
    IteratorSLL<T> &operator=(const IteratorSLL<T> &otherList);

    //#########################################################################
    //# modification - public field containing number of fundamental operations
    //# performed during a traversal of the list
    //#########################################################################
    unsigned long numFOs;

private:
    /**
     * @brief Copy helper method.
     * 
     * This private helper method is used to deep-copy all of the elements from
     * the parameter list to this list. Any existing elements in this list are 
     * safely removed before the copy.
     * 
     * @param otherList Reference to the IteratorSLL object to copy from. 
     */
    void copy(const IteratorSLL<T> &otherList);

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
 * Iterator dereferencing operator override.
 */
template <class T>
T &IteratorSLL<T>::Iterator::operator*() {
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Dereferencing beyond list end in "
                                "Iterator::*()");
    }

    outer.numFOs++;

    return pCurr->data;
}

// doctest unit test for iterator dereferencing
TEST_CASE("testing IteratorSLL<T>::Iterator dereferencing") {
    IteratorSLL<int> list;

    list.add(0);
    IteratorSLL<int>::Iterator it = list.front();

    // first element should be 0
    CHECK(*it == 0);

    // check exception handling when dereferencing past end of list
    it = list.end();
    bool flag = true;
    try {
        *it;            // should throw an exception
        flag = false;   // this should never happen
    } catch (std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Iterator increment operator overload.
 */
template <class T>
typename IteratorSLL<T>::Iterator &IteratorSLL<T>::Iterator::operator++(int dummy) {
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Increment beyond list end in "
                                "Iterator::++()");
    }

    outer.numFOs++;

    pCurr = pCurr->pNext;
    return *this;
}

// doctest unit test for iterator increment overload
TEST_CASE("testing IteratorSLL<T>::Iterator postfix increment") {
    IteratorSLL<char> list;

    // populate with a - z
    for(char c = 'a'; c <= 'z'; c++) {
        list.add(c);
    }

    // verify that iterating moves through the list
    IteratorSLL<char>::Iterator it = list.front();
    for(char c = 'z'; c >= 'a'; c--) {
        CHECK(*it == c);
        it++;
    }

    // check exception handling when incrementing beyond list end
    bool flag = true;
    try {
        it++;           // this should throw an exception
        flag = false;   // this should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

// doctest unit test for the copy constructor
TEST_CASE("testing IteratorSLL<T> copy constructor") {
    IteratorSLL<int> list1;

    // populate the original list
    for(int i = 0; i < 5; i++) {
        list1.add(i);
    }

    // make a new list like original
    IteratorSLL<int> list2(list1);

    // does it have the right size?
    CHECK(list2.size() == list1.size());

    // does it have the right elements?
    for(int i = 0; i < 5; i++) {
        CHECK(list2.get(i) == (4 - i));
    }

    // try it again with dynamic allocation
    IteratorSLL<int> *pList = new IteratorSLL<int>(list1);

    // does it have the right size?
    CHECK(pList->size() == list1.size());

    // does it have the right elements?
    for(int i = 0; i < 5; i++) {
        CHECK(pList->get(i) == (4 - i));
    }

    delete pList;
}

/*
 * Add d to the front of the list.
 */
template <class T> 
void IteratorSLL<T>::add(const T &d) {
    // create the new node
    Node *pN = new Node(d, pHead);

    // change head pointer to point to the new node
    pHead = pN;

    // increment size
    n++;
}

// doctest unit test for the add method
TEST_CASE("testing IteratorSLL<T>::add") {
    IteratorSLL<int> list;

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
void IteratorSLL<T>::clear() {
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
TEST_CASE("testing IteratorSLL<T>::clear") {
    IteratorSLL<int> list;

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
typename IteratorSLL<T>::Iterator IteratorSLL<T>::contains(const T &d) const {
    // create cursor
    Node *pCurr = pHead;

    // iterate until we find d or end of list
    while(pCurr != 0) {

        // found it? return its iterator
        if(pCurr->data == d) {
            return Iterator(pCurr);
        }

        pCurr = pCurr->pNext;
    }

    // not found? return flag value
    return Iterator(0);
}

// doctest unit test for the contains method
TEST_CASE("testing IteratorSLL<T>::contains") {
    IteratorSLL<char> list;

    // populate the list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.add(c);
    }

    // search for 1st element in list
    CHECK(*(list.contains('Z')) == 'Z');

    // search for last element in list
    CHECK(*(list.contains('A')) == 'A');

    // search for something in the middle
    CHECK(*(list.contains('M')) == 'M');

    // search for something not in list
    CHECK(list.contains('a') == list.end());
}

/*
 * Make this list a deep copy of another list.
 */
template <class T> 
void IteratorSLL<T>::copy(const IteratorSLL<T> &otherList) {
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

// since copy is private, it's tested indirectly in copy constructor and 
// assignment operator tests

// doctest unit test for the end method
TEST_CASE("testing IteratorSLLT<T>::end") {
    IteratorSLL<double> list;

    // iterating through empty list should not happen
    IteratorSLL<double>::Iterator it = list.front();
    int count = 0;
    for(; it != list.end(); it++) {
        count++;
    }
    CHECK(count == 0);

    // iterating through a list w/ 5 elements
    for(int i = 0; i < 5; i++) {
        list.add(i);
    }
    it = list.front();
    count = 0;
    for(; it != list.end(); it++) {
        count++;
    }
    CHECK(count == 5);
}

// doctest unit test for the front method
TEST_CASE("testing IteratorSLL<T>::front") {
    IteratorSLL<int> list;
    list.add(0);

    // is the front iterator the first element?
    IteratorSLL<int>::Iterator it = list.front();
    CHECK(*it == list.get(0));

    // add another and repeat the check
    list.add(1);
    it = list.front();
    CHECK(*it == list.get(0));
}

/*
 * Get the value at location idx.
 */
template <class T> 
T IteratorSLL<T>::get(unsigned idx) const {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in IteratorSLL::get()");
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

// doctest unit test for the get method
TEST_CASE("testing IteratorSLL<T>::get") {
    IteratorSLL<char> list;

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
T IteratorSLL<T>::remove(unsigned idx) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in IteratorSLL::remove()");
    }

    // initialize cursors
    Node *pCurr = pHead, *pPrev = 0;

    // iterate cursors to position
    for(unsigned i = 0u; i < idx; i++) {
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
TEST_CASE("testing IteratorSLL<T>::remove") {
    IteratorSLL<char> list;

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
 * Change the value at location idx to d.
 */
template <class T> 
void IteratorSLL<T>::set(unsigned idx, const T &d) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in IteratorSLL::set()");
    }

    // initialize cursor
    Node *pCurr = pHead;

    // iterate to location
    for(unsigned i = 0u; i < idx; i++) {
        pCurr = pCurr->pNext;
    }

    // change data in location idx to d
    pCurr->data = d;
}

// doctest unit test for the set method
TEST_CASE("testing IteratorSLL<T>::set") {
    IteratorSLL<char> list;

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
        flag = false;       // this should never be reached, due to exception
    } catch(std::out_of_range oor) {
        CHECK(flag);    // if exception was handled properly, should be true
    }
}

/*
 * Assignment operator.
 */
template <class T>
IteratorSLL<T> & IteratorSLL<T>::operator=(const IteratorSLL<T> &otherList) {
    // remove any existing contents first
    clear();

    // copy other list contents to this object
    copy(otherList);

    return *this;
}

// doctest unit test for the assignment operator
TEST_CASE("testing IteratorSLL<T> assignment") {
    IteratorSLL<int> list1, list2;

    // populate lists
    for(int i = 0; i < 5; i++) {
        list1.add(i);
        if(i % 2 == 0) {
            list2.add(i);
        }
    }

    // do the assignment
    list1 = list2;

    // right size?
    CHECK(list1.size() == list2.size());

    // same contents?
    for(unsigned i = 0; i < list1.size(); i++) {
        CHECK(list1.get(i) == list2.get(i));
    }
}

/*
 * Override of the stream insertion operator. Using iterators removes
 * the need for this to be a friend of the IteratorSLL class. 
 */
template <class T>
std::ostream &operator<<(std::ostream &out, const IteratorSLL<T> &list) {

    out << "[";

    // iterate through the list using an iterator
    typename IteratorSLL<T>::Iterator i = list.front();
    // second iterator used to see if we should output a comma or not
    typename IteratorSLL<T>::Iterator j = list.front();
    
    while(i != list.end()) {

        out << *i;

        // output comma for all but last element
        j++;
        if(j != list.end()) {
            out << ", ";
        }

        i++;
    }

    out << "]";

    return out;        
}

// doctest unit test for the stream insertion operator
TEST_CASE("testing IteratorSLL<T> stream insertion") {
    IteratorSLL<int> list;

    for(int i = 0; i < 5; i++) {
        list.add(i);
    }

    // test stream insertion by "printing" to a string
    std::ostringstream oss;

    oss << list;

    // did the output match?
    CHECK(oss.str() == "[4, 3, 2, 1, 0]");
}