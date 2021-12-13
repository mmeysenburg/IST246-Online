#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 5 generic doubly-linked list, supporting iterators.
 *
 * DLL is a generic doubly-linked list data structure. It allows inserting at 
 * the front or back of the list, and supports index-based get, set, and remove 
 * operations. The list also provides a contains method, and the administrative 
 * methods clear, isEmpty, and size. DLL also has a copy constructor, and 
 * overrides the assignment and stream insertion operators. DLL provides front,
 * back, and end methods to access iterators that move through the list from 
 * front to back or back to front.
 */
template <class T> class DLL {

private:
    /**
     * @brief Node in the doubly-linked list.
     *
     * Node is a private inner class of DLL. The class represents a 
     * single node in the list. Each node has a payload of type T, a 
     * pointer to the next node in the list, and a pointer to the previous node
     * in the list.
     */
    class Node {
    public:
        /**
         * @brief Default constructor. 
         *
         * Make a new Node with default data and next and previous pointers set 
         * to zero.
         */
        Node() : data(), pPrev(0), pNext(0) { }

        /**
         * @brief Initializing constructor. 
         *
         * Make a new node with the specified data and previous and next 
         * pointer values.
         *
         * @param d Data value for the node.
         * @param pP Pointer to the previous node in the list, or 0 if this is
         * the first node in the list. 
         * @param pN Pointer to the next node in the list, or 0 if this is the
         * last Node in the list.
         */
        Node(const T &d, Node *pP, Node *pN) : data(d), pPrev(pP), pNext(pN) { }

        /**
         * @brief Node payload.
         *
         * Type T payload of the node. Assumed to support assignment, equality 
         * testing, copy constructor, and stream insertion.
         */
        T data;

        /**
         * @brief Previous node pointer. 
         *
         * Pointer to the previous node in the list, or 0 if this is the first 
         * node.
         */
        Node *pPrev;

        /**
         * @brief Next node pointer. 
         *
         * Pointer to the next node in the list, or 0 if this is the last node.
         */
        Node *pNext;
    };

public:
    /**
     * @brief DLL iterator.
     * 
     * This class allows DLL users to iterate through the list, from front to 
     * back or back to front, without exposing the pointer structure of the 
     * list, and without incurring the time complexity of successive calls to 
     * the index-based get() and set() methods. 
     */ 
    class Iterator {
    public:
        /**
         * @brief Iterator dereferencing operator.
         * 
         * This override of the dereferencing operator allows DLL 
         * users to access and / or change the payload of a node in the list.
         * 
         * @throws std::out_of_range if the iterator is past either end of 
         * the list.
         */
        T &operator*();

        /**
         * @brief Iterator equality operator.
         * 
         * This override of the equality operator allows DLL users to 
         * compare two iterators, to determine if they refer to the same node 
         * in the list. 
         */
        bool operator==(const Iterator &other) const {
            return pCurr == other.pCurr;
        }

        /**
         * @brief Interator inequality operator.
         * 
         * This override of the inequality operator allows DLL users to
         * compare two iterators, to determine if they refer to different nodes 
         * in the list.
         */
        bool operator!=(const Iterator &other) const {
            return pCurr != other.pCurr;
        }

        /**
         * @brief Iterator decrement operator.
         * 
         * This override of the postfix decrement operator allows DLL 
         * users to move an iterator from one node to the previous node in the 
         * list. 
         * 
         * @param dummy Dummy parameter that indicates we are overriding
         * the postfix decrement operator.
         * 
         * @throws std::out_of_range if the iterator is past either end of 
         * the list.
         */
        Iterator &operator--(int dummy);

        /**
         * @brief Iterator increment operator.
         * 
         * This override of the postfix increment operator allows DLL 
         * users to move an iterator from one node to the next node in the 
         * list. 
         * 
         * @param dummy Dummy parameter that indicates we are overriding
         * the postfix increment operator.
         * 
         * @throws std::out_of_range if the iterator is past either end of 
         * the list.
         */
        Iterator &operator++(int dummy);

        // Make DLL a friend class, so it can access the private constructor
        friend class DLL;

    private:
        /**
         * @brief Initializing constructor.
         * 
         * This constructor makes an iterator that refers to the Node at the
         * end of the specified pointer. The constructor is private, so that 
         * the only way to get an iterator is via the DLL front(), back(),  
         * and end() methods. 
         * 
         * @param pC Node this iterator should refer to.
         */
        Iterator(Node *pC) : pCurr(pC) { }

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
    DLL() : pHead(0), pTail(0), n(0u) { }

    /**
     * @brief Copy construstor.
     * 
     * Make a new, deep-copy list, just like the parameter list.
     * 
     * @param otherList Reference to the DLL to copy.
     */
    DLL(const DLL<T> &otherList) : pHead(0), pTail(0), n(0u) { copy(otherList); }

    /**
     * @brief Destructor. 
     *
     * Free the memory used by this list. 
     */
    ~DLL() { clear(); }

    /**
     * @brief Add a value to the front of the list. 
     *
     * @param d Value to add to the list.
     */
    void addFirst(const T &d);

    /**
     * @brief Add a value to the back of the list. 
     *
     * @param d Value to add to the list.
     */
    void addLast(const T &d);

    /**
     * @brief Get an Iterator on the last node of the list.
     * 
     * @return An Iterator positioned on the last node of the list.
     */
    Iterator back() const { return Iterator(pTail); }

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
     * @brief Get an Iterator representing the end of the list.
     * 
     * @return An Iterator representing one past the back, or one before the
     * front, of the list.
     */
    Iterator end() const { return Iterator(0); } 

    /**
     * @brief Get an Iterator on the first node of the list.
     * 
     * @return An Iterator positioned on the first node of the list.
     */
    Iterator front() const { return Iterator(pHead); }

    /**
     * @brief Get a value.
     *
     * Get the value at a specified index in the list.
     * 
     * @param idx Index of the value to get.
     *
     * @throws std::out_of_range if the index is past either end of the list.
     * 
     * @return Value at location idx in the list.
     */
    T get (unsigned idx) const;

    /**
     * @brief Get first value.
     *
     * Get the value at the front of the list.
     *
     * @throws std::out_of_range if the list is empty.
     *
     * @return Value at the front of the list.
     */
    T getFirst() const;

    /**
     * @brief Get last value.
     *
     * Get the value at the back of the list.
     *
     * @throws std::out_of_range if the list is empty.
     *
     * @return Value at the back of the list.
     */
    T getLast() const;

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
     * @throws std::out_of_range if the index is past either end of the list.
     *
     * @return Value that was at location idx.
     */
    T remove(unsigned idx);

    /**
     * @brief Remove first element.
     *
     * Remove the element from the front of the list.
     *
     * @throws std::out_of_range if the list is empty.
     *
     * @return Value that was at the front of the list.
     */
    T removeFirst();

    /**
     * @brief Remove last element.
     *
     * Remove the element from the back of the list.
     *
     * @throws std::out_of_range if the list is empty.
     *
     * @return Value that was at the back of the list.
     */
    T removeLast();

    /**
     * @brief Return a new, reversed copy of this list.
     * 
     * Creates and returns a new DLL, with the same elements as this list,
     * but in the opposite order. This list is not changed.
     * 
     * @return A new DLL that is a reversed copy of this list. 
     */
    DLL<T> reverse() const;

    /**
     * @brief Change a list element. 
     *
     * Change the value at a specified index to another value.
     *
     * @param idx Index of the value to change.
     *
     * @throws std::out_of_range if the index is past either end of the list.
     *
     * @param d New value to place in position idx.
     */
    void set(unsigned idx, const T &d);

    /**
     * @brief Change the first list element.
     * 
     * @param d New value to replace front value in the list.
     * 
     * @throws std::out_of_range if the list is empty.
     */
    void setFirst(const T &d);

    /**
     * @brief Change the last list element.
     * 
     * @param d New value to replace back value in the list.
     * 
     * @throws std::out_of_range if the list is empty.
     */
    void setLast(const T &d);

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
     * Override of the assignment operator to work with DLL objects. 
     * Makes this list a deep-copy, identical structure as the parameter 
     * DLL. 
     * 
     * @param list DLL to copy from
     * 
     * @return Reference to this object.
     */
    DLL<T> &operator=(const DLL<T> &otherList);

private:
    /**
     * @brief Copy helper method.
     * 
     * This private helper method is used to deep-copy all of the elements from
     * the parameter list to this list. Any existing elements in this list are 
     * safely removed before the copy.
     * 
     * @param otherList Reference to the DLL object to copy from. 
     */
    void copy(const DLL<T> &otherList);

    /**
     * Pointer to the first Node in the list, or 0 if the list is empty.
     */
    Node *pHead;

    /**
     * Pointer to the last Node in the list, or 0 if the list is empty.
     */
    Node *pTail;
    
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
T &DLL<T>::Iterator::operator*() {
    // if the iterator is past either end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Dereferencing beyond list end in "
                                "Iterator::*()");
    }

    return pCurr->data;
}

// doctest unit test for iterator dereferencing
TEST_CASE("testing DLL<T>::Iterator dereferencing") {
    DLL<int> list;

    list.addFirst(1);
    list.addFirst(0);
    DLL<int>::Iterator it = list.front();

    // first element should be 0
    CHECK(*it == 0);

    // last element should be 1
    it++;
    CHECK(*it == 1);

    // check exception handling when dereferencing past end of list
    it++;
    bool flag = true;
    try {
        *it;            // should throw an exception
        flag = false;   // this should never happen
    } catch (std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Iterator decrement operator overload.
 */
template <class T> 
typename DLL<T>::Iterator &DLL<T>::Iterator::operator--(int dummy) {
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Increment beyond list end in "
                                "Iterator::--()");
    }

    pCurr = pCurr->pPrev;
    return *this;
}

// doctest unit test for iterator decrement overload
TEST_CASE("testing DLL<T>::Iterator postfix decrement") {
    DLL<char> list;

    // populate with a - z
    for(char c = 'a'; c <= 'z'; c++) {
        list.addFirst(c);
    }

    // verify that iterating moves through the list backwards
    DLL<char>::Iterator it = list.back();
    for(char c = 'a'; c <= 'z'; c++) {
        CHECK(*it == c);
        it--;
    }

    // check exception handling when incrementing beyond list end
    bool flag = true;
    try {
        it--;           // this should throw an exception
        flag = false;   // this should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Iterator increment operator overload.
 */
template <class T>
typename DLL<T>::Iterator &DLL<T>::Iterator::operator++(int dummy) {
    // if the iterator is past the end of the list, throw an exception
    if(pCurr == 0) {
        throw std::out_of_range("Increment beyond list end in "
                                "Iterator::++()");
    }

    pCurr = pCurr->pNext;
    return *this;
}

// doctest unit test for iterator increment overload
TEST_CASE("testing DLL<T>::Iterator postfix increment") {
    DLL<char> list;

    // populate with a - z
    for(char c = 'a'; c <= 'z'; c++) {
        list.addFirst(c);
    }

    // verify that iterating moves through the list
    DLL<char>::Iterator it = list.front();
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
TEST_CASE("testing DLL<T> copy constructor") {
    DLL<int> list1;

    // populate the original list
    for(int i = 0; i < 5; i++) {
        list1.addFirst(i);
    }

    // make a new list like original
    DLL<int> list2(list1);

    // does it have the right size?
    CHECK(list2.size() == list1.size());

    // does it have the right elements?
    for(int i = 0; i < 5; i++) {
        CHECK(list2.get(i) == (4 - i));
    }

    // try it again with dynamic allocation
    DLL<int> *pList = new DLL<int>(list1);

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

// doctest unit test for addFirst
TEST_CASE("testing DLL<T>::addFirst") {
    DLL<int> list;

    list.addFirst(0);

    // is it there?
    DLL<int>::Iterator it = list.front();
    CHECK(*it == 0);

    // try with another element
    list.addFirst(1);
    it = list.front();
    CHECK(*it == 1);
    it = list.back();
    CHECK(*it == 0);
}

/*
 * Add do the back of the list.
 */
template <class T>
void DLL<T>::addLast(const T &d) {
    Node *pN = new Node(d, pTail, 0);

    if(pHead == 0) {
        // empty list case
        pHead = pTail = pN;
    } else {
        // non-empty list case
        pTail = pN;
        pTail->pPrev->pNext = pTail;
    }

    n++;
}

// doctest unit test for addLast
TEST_CASE("testing DLL<T>::addLast") {
    DLL<int> list;

    list.addLast(0);

    // is it there?
    DLL<int>::Iterator it = list.back();
    CHECK(*it == 0);

    // try with another element
    list.addLast(1);
    it = list.back();
    CHECK(*it == 1);
    it = list.front();
    CHECK(*it == 0);
}

// doctest unit test for the back method
TEST_CASE("testing DLL<T>::back") {
    DLL<int> list;
    list.addLast(0);

    // is the back iterator the first element?
    DLL<int>::Iterator it = list.back();
    CHECK(*it == list.get(0));

    // add another and repeat the check
    list.addLast(1);
    it = list.back();
    CHECK(*it == list.get(1));
}

/*
 * Delete all list nodes.
 */
template <class T> 
void DLL<T>::clear() {
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

    // reset head, tail pointer and size
    pHead = 0;
    pTail = 0;
    n = 0u;
}

// doctest unit test for the clear method
TEST_CASE("testing DLL<T>::clear") {
    DLL<int> list;

    // add some list elements
    for(int i = 0; i < 100; i++) {
        list.addFirst(i);
    }

    // clear should make size equal zero
    list.clear();
    CHECK(list.size() == 0u);
}

/*
 * Search the list for value d.
 */
template <class T> 
int DLL<T>::contains(const T &d) const {
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
TEST_CASE("testing DLL<T>::contains") {
    DLL<char> list;

    // populate the list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.addFirst(c);
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
 * Make this list a deep copy of another list.
 */
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

// since copy is private, it's tested indirectly in copy constructor and 
// assignment operator tests

// doctest unit test for the end method
TEST_CASE("testing DLLT<T>::end") {
    DLL<double> list;

    // iterating through empty list should not happen
    DLL<double>::Iterator it = list.front();
    int count = 0;
    for(; it != list.end(); it++) {
        count++;
    }
    CHECK(count == 0);

    // iterating through a list w/ 5 elements
    for(int i = 0; i < 5; i++) {
        list.addFirst(i);
    }
    it = list.front();
    count = 0;
    for(; it != list.end(); it++) {
        count++;
    }
    CHECK(count == 5);
}

// doctest unit test for the front method
TEST_CASE("testing DLL<T>::front") {
    DLL<int> list;
    list.addFirst(0);

    // is the front iterator the first element?
    DLL<int>::Iterator it = list.front();
    CHECK(*it == list.get(0));

    // add another and repeat the check
    list.addFirst(1);
    it = list.front();
    CHECK(*it == list.get(0));
}

/*
 * Get the value at location idx.
 */
template <class T> 
T DLL<T>::get(unsigned idx) const {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out of range in DLL::get()");
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
TEST_CASE("testing DLL<T>::get") {
    DLL<char> list;

    // populate list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.addFirst(c);
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
 * Get the front value.
 */
template <class T> 
T DLL<T>::getFirst() const {
    // if list is empty, throw an exception
    if(pHead == 0) {
        throw std::out_of_range("Empty list in DLL::getFirst()");
    }

    return pHead->data;
}

// doctest unit test for the getFirst method
TEST_CASE("testing DLL<T>::getFirst") {
    DLL<int> list;
    for(int i = 0; i < 5; i++) {
        list.addFirst(i);
        CHECK(list.getFirst() == i);
    }

    // test exception generation
    list.clear();
    bool flag = true;
    try {
        list.getFirst();    // this should cause an exception
        flag = false;       // this should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Get the back value.
 */
template <class T> 
T DLL<T>::getLast() const {
    // if list is empty, throw an exception
    if(pTail == 0) {
        throw std::out_of_range("Empty list in DLL::getLast()");
    }

    return pTail->data;
}

// doctest unit test for the getLast method
TEST_CASE("testing DLL<T>::getLast") {
    DLL<int> list;
    for(int i = 0; i < 5; i++) {
        list.addLast(i);
        CHECK(list.getLast() == i);
    }

    // test exception generation
    list.clear();
    bool flag = true;
    try {
        list.getLast();     // this should cause an exception
        flag = false;       // this should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Remove node at location idx. 
 */
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

/*
 * Make a new, reversed copy of this list.
 */
template <class T>
DLL<T> DLL<T>::reverse() const {
    // TODO: implement this method
}

// dotest unit test for reverse method
TEST_CASE("testing DLL<T>::reverse") {
    // TODO: write testing code to validate reverse method
    // Create and populate a DLL
    // Call its reverse method, save in a new DLL variable
    // Verify the second is reversed version of the first
    // Verify the second has same number of elements as first as well
    CHECK(false); // <- replace with your code
}

// doctest unit test for the remove method
TEST_CASE("testing DLL<T>::remove") {
    DLL<char> list;

    // populate list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.addFirst(c);
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
 * Remove front element
 */
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

// doctest unit test for the removeFirst method
TEST_CASE("testing DLL<T>::removeFirst") {
    DLL<int> list;

    // populate list
    for(int i = 0; i < 10; i++) {
        list.addLast(i);
    }

    // check removing from front
    for(int i = 0; i < 10; i++) {
        CHECK(list.removeFirst() == i);
        CHECK(list.size() == 9 - i);
    }

    // check removing from empty list
    bool flag = true;
    try {
        list.removeFirst();     // list is empty, so this is an error
        flag = false;           // should never happen due to exception
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Remove back element.
 */
template <class T>
T DLL<T>::removeLast() {
    if(pHead == 0) {
        throw std::out_of_range("Empty list in DLL::removeLast()");
    }

    // save data in front node, and pointer to the node
    T d = pTail->data;
    Node *pTemp = pTail;

    // update head pointer
    pTail = pTail->pPrev;
    if(pTail != 0) {
        // if there are more elements, mark new last node next pointer
        // as right end of the list
        pTail->pNext = 0;
    } else {
        // if there are no more elements, update head pointer
        pHead = 0;
    }

    // update size, free former last node memory
    n--;
    delete pTemp;

    // send back value from former last node
    return d;
}

// doctest unit test for the removeLast method
TEST_CASE("testing DLL<T>::removeLast") {
    DLL<int> list;

    // populate list
    for(int i = 0; i < 10; i++) {
        list.addFirst(i);
    }

    // test removeLast
    for(int i = 0; i < 10; i++) {
        CHECK(list.removeLast() == i);
        CHECK(list.size() == 9 - i);
    }

    // test exception handling
    bool flag = true;
    try {
        list.removeLast();      // should not be legal; list is empty
        flag = false;           // should never happen due to exception
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/* 
 * Change the value at location idx to d.
 */
template <class T> 
void DLL<T>::set(unsigned idx, const T &d) {
    // if the idx is past list end, throw an exception
    if(idx >= n) {
        throw std::out_of_range("Index out  of range in DLL::set()");
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
TEST_CASE("testing DLL<T>::set") {
    DLL<char> list;

    // populate the list
    for(char c = 'A'; c <= 'Z'; c++) {
        list.addFirst(c);
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
 * Change the value at the front to d.
 */
template <class T>
void DLL<T>::setFirst(const T &d) {
    // throw an exception if the list is empty
    if(isEmpty()) {
        throw std::out_of_range("Empty list in DLL<T>::setFirst()");
    }

    pHead->data = d;
}

// doctest unit test for setFirst
TEST_CASE("testing DLL<T>::setFirst") {
    DLL<char> list;

    // populate list
    for(char c = 'a'; c <= 'z'; c++) {
        list.addLast(c);
    }

    // test setFirst
    list.setFirst('A');
    CHECK(list.getFirst() == 'A');
    list.clear();
    list.addFirst('A');
    list.setFirst('a');
    CHECK(list.getLast() == 'a');

    // test exception handling
    bool flag = true;
    list.clear();
    try {
        list.setFirst('Q');     // should cause an exception
        flag = false;           // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Change the value at the back to d.
 */
template <class T>
void DLL<T>::setLast(const T &d) {
    // throw an exception if the list is empty
    if(isEmpty()) {
        throw std::out_of_range("Empty list in DLL<T>::setLast()");
    }

    pTail->data = d;
}

// doctest unit test for setLast
TEST_CASE("testing DLL<T>::setLast") {
    DLL<char> list;

    // populate list
    for(char c = 'a'; c <= 'z'; c++) {
        list.addLast(c);
    }

    // test setFirst
    list.setLast('A');
    CHECK(list.getLast() == 'A');
    list.clear();
    list.addFirst('A');
    list.setLast('a');
    CHECK(list.getFirst() == 'a');

    // test exception handling
    bool flag = true;
    list.clear();
    try {
        list.setLast('Q');     // should cause an exception
        flag = false;           // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Assignment operator.
 */
template <class T>
DLL<T> & DLL<T>::operator=(const DLL<T> &otherList) {
    // remove any existing contents first
    clear();

    // copy other list contents to this object
    copy(otherList);

    return *this;
}

// doctest unit test for the assignment operator
TEST_CASE("testing DLL<T> assignment") {
    DLL<int> list1, list2;

    // populate lists
    for(int i = 0; i < 5; i++) {
        list1.addFirst(i);
        if(i % 2 == 0) {
            list2.addFirst(i);
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
 * the need for this to be a friend of the DLL class. 
 */
template <class T>
std::ostream &operator<<(std::ostream &out, const DLL<T> &list) {

    out << "[";

    // iterate through the list using an iterator
    typename DLL<T>::Iterator i = list.front();
    
    while(i != list.end()) {

        out << *i;

        // output comma for all but last element
        i++;
        if(i != list.end()) {
            out << ", ";
        }
    }

    out << "]";

    return out;        
}

// doctest unit test for the stream insertion operator
TEST_CASE("testing DLL<T> stream insertion") {
    DLL<int> list;

    for(int i = 0; i < 5; i++) {
        list.addFirst(i);
    }

    // test stream insertion by "printing" to a string
    std::ostringstream oss;

    oss << list;

    // did the output match?
    CHECK(oss.str() == "[4, 3, 2, 1, 0]");
}