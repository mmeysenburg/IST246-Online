#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include "../1-DLL/DLL.hpp"

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 5 generic queue.
 * 
 * Queue is a generic queue data structure. It supports enqueue and dequeue  
 * methods, and clear, isEmpty, and size administrative methods. It also has
 * a copy constructor, and overrides the assignment and stream insertion 
 * operators.
 */
template <class T> class Queue {
public:
    /**
     * @brief Default constructor.
     * 
     * Make a new, empty queue.
     */
    Queue() { }

    /**
     * @brief Copy constructor.
     * 
     * Make a new queue, just like the parameter.
     * 
     * @param queue Constant reference to the queue to copy from.
     */
    Queue(const Queue<T> &queue) { copy(queue); }

    /**
     * @brief Empty the queue.
     * 
     * Removes all elements from this queue.
     */
    void clear() { list.clear(); }

    /**
     * @brief Dequeue first element.
     * 
     * Removes and returns the first element from the queue.
     * 
     * @return Element of type T that was the first element in the queue.
     * 
     * @throws std::out_of_range if the queue is empty
     */
    T dequeue();

    /**
     * @brief Enqueue a new element.
     * 
     * Adds a value of type T to the back of the queue.
     * 
     * @param v Element to enqueue
     */
    void enqueue(const T& v) { list.addLast(v); }

    /**
     * @brief Determine if the queue is empty.
     * 
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() { return list.isEmpty(); }

    /**
     * @brief Assignment operator override.
     * 
     * @param queue Queue to copy from.
     * 
     * @return Reference to this queue, after it has copied the parameter, 
     * for chaining purposes.
     */
    Queue<T> &operator=(const Queue<T> &queue);

    /**
     * @brief Stream insertion override.
     * 
     * @param out ostream object to output to, e.g., cout.
     * 
     * @param queue Queue to output.
     * 
     * @return Reference to the out ostream object.
     */
    friend std::ostream &operator<<(std::ostream &out, const Queue<T> &queue) {
        out << queue.list;
        return out;
    }

    /**
     * @brief Get the size of the queue.
     * 
     * @return Number of elements in the queue.
     */
    unsigned size() { return list.size(); }

private:
    /**
     * Doubly-linked list used as the underlying data store for the queue.
     */
    DLL<T> list;

    /**
     * @brief Copy queue contents.
     * 
     * Private helper method for copy constructor and assignment override.
     * 
     * @param queue Queue to copy from. 
     */
    void copy(const Queue<T> &queue) { list = queue.list; }
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

// doctest unit tests for copy constructor
TEST_CASE("Testing Queue<T>::Queue(queue) constructor") {
    Queue<int> q1;
    for(int i = 1; i <= 5; i++) {
        q1.enqueue(i);
    }

    Queue<int> q2(q1);

    for(int i = 1; i <= 5; i++) {
        CHECK(i == q2.dequeue());
    }
}

// doctest unit tests for clear method
TEST_CASE("Testing Queue<T>::clear()") {
    Queue<char> q;
    for(char c = 'a'; c <= 'z'; c++) {
        q.enqueue(c);
    }
    q.clear();
    CHECK(q.isEmpty());
}

// copy is private, so it is tested in copy constructor and assignment
// operator tests

/*
 * Dequeue method.
 */
template <class T>
T Queue<T>::dequeue() {
    if(list.isEmpty()) {
        throw std::out_of_range("dequeue of empty queue");
    }

    return list.removeFirst();
}

// doctest unit tests for dequeue method
TEST_CASE("Testing Queue<T>::dequeue()") {
    Queue<int> q;
    for(int i = 0; i < 5; i++) {
        q.enqueue(i);
    }

    for(int i = 0; i < 5; i++) {
        CHECK(i == q.dequeue());
        CHECK((4 - i) == q.size());
    }

    bool flag = true;
    try {
        q.dequeue();  // should cause an exception
        flag = false;   // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

// doctest unit tests for enqueue method
TEST_CASE("Testing Queue<T>::enqueue()") {
    Queue<double> q;

    for(int i = 1; i <= 5; i++) {
        q.enqueue(i);
        CHECK(i == q.size());
    }

    for(int i = 1; i <= 5; i++) {
        CHECK(i == q.dequeue());
    }
}

// doctest unit tests for isEmpty method
TEST_CASE("Testing Queue<T>::isEmpty()") {
    Queue<std::string> q;

    CHECK(q.isEmpty());

    q.enqueue("Bob");

    CHECK(!q.isEmpty());

    q.dequeue();

    CHECK(q.isEmpty());
}

/*
 * Implementation for assignment operator.
 */
template <class T>
Queue<T> & Queue<T>::operator=(const Queue<T> &queue) { 
    copy(queue); 
    return *this;
}

// doctest unit test for assignment operator
TEST_CASE("Testing Queue<T>::operator=") {
    Queue<int> q1, q2;

    for(int i = 0; i < 5; i++) {
        q1.enqueue(i);
        q2.enqueue(5 - i);
    }
    q2.enqueue(-1);

    q2 = q1;

    CHECK(5 == q2.size());
    for(int i = 0; i < 5; i++) {
        CHECK(i == q2.dequeue());
    }
}

// doctest unit test for the stream insertion operator
TEST_CASE("testing Queue<T> stream insertion") {
    Queue<int> q;

    for(int i = 0; i < 5; i++) {
        q.enqueue(i);
    }

    // test stream insertion by "printing" to a string
    std::ostringstream oss;

    oss << q;

    // did the output match?
    CHECK(oss.str() == "[0, 1, 2, 3, 4]");
}

// doctest unit tests for size method
TEST_CASE("Testing Queue<T>::size") {
    Queue<char> q;

    CHECK(0 == q.size());

    for(int i = 1; i <= 5; i++) {
        q.enqueue('a');
        CHECK(i == q.size());
    }

    for(int i = 4; i >= 0; i--) {
        q.dequeue();
        CHECK(i == q.size());
    }
}