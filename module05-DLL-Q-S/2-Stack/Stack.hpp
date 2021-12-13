#pragma once

#include <doctest.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "../1-DLL/DLL.hpp"

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 5 generic stack.
 * 
 * Stack is a generic stack data structure. It supports push, pop, and peek
 * methods, and clear, isEmpty, and size administrative methods. It also has
 * a copy constructor, and overrides the assignment and stream insertion 
 * operators.
 */
template <class T> class Stack {
public:
    /**
     * @brief Default constructor.
     * 
     * Make a new, empty stack.
     */
    Stack() {}

    /**
     * @brief Copy constructor.
     * 
     * Make a new stack, just like the parameter.
     * 
     * @param stack Constant reference to the stack to copy from.
     */
    Stack(const Stack<T> &stack) { copy(stack); }

    /**
     * @brief Empty the stack.
     * 
     * Removes all elements from this stack.
     */
    void clear() { list.clear(); }

    /**
     * @brief Determine if the stack is empty.
     * 
     * @return True if the stack is empty, false otherwise.
     */
    bool isEmpty() { return list.isEmpty(); }

    /**
     * @brief Access top element.
     * 
     * @return The top element of the stack, without 
     * removing the element from the stack.
     * 
     * @throws std::out_of_range if the stack is empty.
     */
    T peek() const;

    /**
     * @brief Pop top element.
     * 
     * Removes and returns the top element of the stack.
     * 
     * @return Element of type T that was at the top of the stack.
     * 
     * @throws std::out_of_range if the stack is empty.
     */
    T pop();

    /**
     * @brief Push a new element.
     * 
     * Pushes a value of type T onto the top of the stack.
     * 
     * @param v Element to push.
     */
    void push(const T &v) { list.addFirst(v); }

    /**
     * @brief Get the size of the stack.
     * 
     * @return Number of elements in the stack.
     */
    unsigned size() { return list.size(); }

    /**
     * @brief Assignment operator override.
     * 
     * @param stack Stack to copy from.
     * 
     * @return Reference to this stack, after it has copied the parameter, 
     * for chaining purposes.
     */
    Stack<T> &operator=(const Stack<T> &stack);

    /**
     * @brief Stream insertion override.
     * 
     * @param out ostream object to output to, e.g., cout.
     * 
     * @param stack Stack to output.
     * 
     * @return Reference to the out ostream object.
     */
    friend std::ostream &operator<<(std::ostream &out, const Stack<T> &stack) {
        out << stack.list;
        return out;
    }

private:
    /**
     * Doubly-linked list used as the underlying data store for the stack.
     */
    DLL<T> list;

    /**
     * @brief Copy stack contents.
     * 
     * Private helper method for copy constructor and assignment override.
     * 
     * @param stack Stack to copy from. 
     */
    void copy(const Stack<T> &stack) { list = stack.list; }
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

// doctest unit test for the copy constructor
TEST_CASE("testing Stack<T>::Stack(stack) constructor") {
    Stack<char> source;

    for(char c = 'a'; c <= 'z'; c++) {
        source.push(c);
    }

    Stack<char> stackCopy(source);

    // should have same elements, in the same order
    while(!stackCopy.isEmpty()) {
        char a = source.pop();
        char b = stackCopy.pop();
        CHECK(a == b);
    }

    // make sure both are empty
    bool res = source.isEmpty() && stackCopy.isEmpty();
    CHECK(res);
}

// doctest unit test for the clear method
TEST_CASE("testing Stack<T>::clear()") {
    Stack<int> stack;

    for(int i = 0; i < 10; i++) {
        stack.push(i);
    }

    // clear and valdiate size is zero
    stack.clear();

    CHECK(stack.size() == 0u);
    CHECK(stack.isEmpty());
}

// doctest unit test for the isEmpty method
TEST_CASE("testing Stack<T>::isEmpty()") {
    Stack<double> stack;

    // initial one is empty?
    CHECK(stack.isEmpty());

    // populate
    for(int i = 0; i < 10; i++) {
        stack.push(i);
    }

    // should not be empty
    CHECK(!stack.isEmpty());

    // clear
    stack.clear();

    // should be empty again
    CHECK(stack.isEmpty());
}

// copy is private, and so it is tested in copy constructor, assignment tests

/*
 * Peek function implementation.
 */
template <class T>
T Stack<T>::peek() const {
    if(list.isEmpty()) {
        throw std::out_of_range("Empty stack in Stack::peek()");
    }

    return list.getFirst();
}

// doctest unit test for the peek method
TEST_CASE("testing Stack<T>::peek()") {
    Stack<char> stack;

    for(char c = 'a'; c <= 'z'; c++) {
        stack.push(c);
    }

    // check access to top element
    char c = stack.peek();

    CHECK(c == 'z');

    stack.pop();

    c = stack.peek();
    CHECK(c == 'y');

    // check exception handling
    stack.clear();
    bool flag = true;
    try {
        c = stack.peek();   // should cause an exception
        flag = false;       // should never happen
    } catch(std::out_of_range oor) {
        // flag should still be true
        CHECK(flag);
    }
}

/*
 * Pop function implementation.
 */
template <class T>
T Stack<T>::pop() {
    if(list.isEmpty()) {
        throw std::out_of_range("Empty stack in Stack::ppo()");
    }

    return list.removeFirst();
}

// doctest unit test for pop function
TEST_CASE("testing Stack<T>::pop()") {
    Stack<int> stack;
    for(int i = 0; i < 10; i++) {
        stack.push(i);
    }

    // check pop always removes top element
    for(int i = 9; i >= 0; i--) {
        CHECK(stack.pop() == i);
        CHECK(stack.size() == 10 - (10 - i));
    }

    CHECK(stack.isEmpty());

    // check exception handling
    bool flag = true;
    try {
        stack.pop();    // should cause an exception
        flag = false;   // should never happen
    } catch (std::out_of_range oor) {
        // flag should still be true
        CHECK(flag);
    }
}

// doctest unit test for push function
TEST_CASE("testing Stack<T>::push()") {
    Stack<char> stack;
    stack.push('a');
    CHECK(stack.peek() == 'a');
    CHECK(stack.size() == 1u);

    stack.push('b');
    CHECK(stack.size() == 2u);
    CHECK(stack.pop() == 'b');
    CHECK(stack.peek() == 'a');
}

// doctest unit test for size function
TEST_CASE("testing Stack<T>::size()") {
    Stack<int> stack;
    CHECK(stack.size() == 0);
    for(int i = 0; i < 10; i++) {
        stack.push(i);
        CHECK(stack.size() == (i + 1));
    }

    for(int i = 10; i >= 1; i--) {
        stack.pop();
        CHECK(stack.size() == (i - 1));
    }
}

/*
 * Assignment operator override.
 */
template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &stack) {
    copy(stack);
    return *this;
}

// doctest unit test for the assignment operator
TEST_CASE("testing Stack<T> assignment operator") {
    Stack<char> source;

    for(char c = 'a'; c <= 'z'; c++) {
        source.push(c);
    }

    Stack<char> stackCopy = source;

    // should have same elements, in the same order
    while(!stackCopy.isEmpty()) {
        char a = source.pop();
        char b = stackCopy.pop();
        CHECK(a == b);
    }

    // make sure both are empty
    bool res = source.isEmpty() && stackCopy.isEmpty();
    CHECK(res);
}

// doctest unit test for the stream insertion operator
TEST_CASE("testing Stack<T> stream insertion") {
    Stack<int> stack;

    for(int i = 0; i < 5; i++) {
        stack.push(i);
    }

    // test stream insertion by "printing" to a string
    std::ostringstream oss;

    oss << stack;

    // did the output match?
    CHECK(oss.str() == "[4, 3, 2, 1, 0]");
}