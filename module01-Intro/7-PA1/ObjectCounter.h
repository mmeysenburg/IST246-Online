#pragma once

#include <stdexcept>
#include <doctest.h>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 1 Object Counter.
 * 
 * This class is a counter, designed to keep track of how many times objects 
 * that can be numbered with labels in the closed range [1, n] have occurred. 
 */
class ObjectCounter {
public:
    /**
     * @brief Default constructor.
     * 
     * Create an object counter for objects numbered from 1 to 10.
     */
    ObjectCounter() : n(11) { createArray(); }

    /**
     * @brief Initializing constructor.
     * 
     * Create an object counter for objects numbered from 1 to num.
     * 
     * @param num Upper limit (inclusive) for range of object labels.
     */
    ObjectCounter(size_t num) : n(num + 1) { createArray(); }

    /**
     * Free the object's memory.
     */
    ~ObjectCounter() { delete [] pArr; }

    /**
     * @brief Accessor for an individual count.
     * 
     * Get the number of times the object labeled idx was seen.
     * 
     * @param idx Label number for the object.
     * 
     * @return Number of times object number idx was seen.
     * 
     * @throws std::out_of_range if idx is less than 1 or greater than num.
     */
    unsigned getCount(size_t idx);

    // TODO: Write Doxygen comments for the increment() method. Use the 
    // comments for getCount() as a model.
    void increment(size_t idx);

    /**
     * @brief Reset the state of the counter.
     * 
     * Reset all of the object counts to zero.
     */
    void resetCounter();

private:
    /**
     * Helper method to allocate count array and fill it with zeros.
     */
    void createArray();

    /** Pointer to the backing array of unsigned integers. */
    unsigned *pArr;

    /** 
     * Number of elements in the array, 1 more than the number from the 
     * constructor. Array element zero is unused.
     */
    size_t n;
};

//-----------------------------------------------------------------------------
// function implementations
//-----------------------------------------------------------------------------

/*
 * Create backing array and initialize.
 */
void ObjectCounter::createArray() {
    pArr = new unsigned[n];
    resetCounter();
}

/*
 * Get the count for object idx.
 */
unsigned ObjectCounter::getCount(size_t idx) {
    if(idx < 1u || idx >= n) {
        throw std::out_of_range("index out of range in ObjectCounter::getCount()");
    }

    // TODO: return count for object number idx
    return -1; // stub
}

// doctest unit test for the getCount() method
TEST_CASE("testing ObjectCounter::getCount") {
    ObjectCounter oc;

    // 10 values should be all zero
    for(size_t i = 1; i <= 10; i++) {
        CHECK(oc.getCount(i) == 0u);
    }

    // test exception handling
    bool flag = true;
    try {
        oc.getCount(0);     // should throw an exception
        flag = false;       // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
    flag = true;
    try {
        oc.getCount(11);    // should throw an exception
        flag = false;       // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Increment the count for object idx
 */
void ObjectCounter::increment(size_t idx) {
    // TODO: write exception handling code, similar to getCount()

    // TODO: increment the count at location idx by one

}

// doctest unit test for the increment() method
TEST_CASE("testing ObjectCounter::increment") {
    ObjectCounter oc(15);

    // multiple calls to increment
    for(size_t i = 1; i <= 15; i++) {
        for(size_t j = 0; j < i; j++) {
            oc.increment(i);
        }
    }

    // verify results
    for(size_t i = 1; i <= 15; i++) {
        CHECK(oc.getCount(i) == i);
    }

    // check exception handling
    bool flag = true;
    try {
        oc.increment(0);    // should throw an exception
        flag = false;       // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
    flag = true;
    try {
        oc.increment(16);   // should throw an exception
        flag = false;       // should never happen
    } catch(std::out_of_range oor) {
        CHECK(flag);
    }
}

/*
 * Reset all counts to zero.
 */
void ObjectCounter::resetCounter() {
    for(size_t i = 0; i < n; i++) {
        pArr[i] = 0u;
    }
}