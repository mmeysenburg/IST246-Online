#pragma once

#include <cmath>
#include <doctest.h>

/*-----------------------------------------------------------------------------
 * class definition
 *---------------------------------------------------------------------------*/

/**
 * @brief CMP 246 Module 1 class representing an (x, y) coordinate.
 * 
 * This class represents an (x, y) coordinate. The class is templated, and
 * can support float, double, or long double for the type of each element of 
 * the coordinate.
 */
template <class T> class Coordinate {
public:
    /**
     * @brief Default constructor.
     * 
     * Create a new coordinate with each element set to zero.
     */
    Coordinate() : x(), y() { }

    /**
     * @brief Initializing constructor.
     * 
     * Create a new coordinate with the specified values.
     * 
     * @param inX x-value for this coordinate.
     * @param inY y-value for this coordinate.
     */
    Coordinate(T inX, T inY) : x(inX), y(inY) { }

    /**
     * @brief Mutator for the x-value.
     * 
     * @param inX New x-value for this coordinate.
     */
    void setX(T inX) { x = inX; }

    /**
     * @brief Mutator for the y-value.
     * 
     * @param inY New y-value for this coordinate.
     */
    void setY(T inY) { y = inY; }

    /**
     * @brief Accessor for the x-value.
     * 
     * @return This coordinate's x-value.
     */
    T getX() const { return x; }

    /**
     * @brief Accessor for the y-value.
     * 
     * @return This coordinate's y-value.
     */
    T getY() const { return y; }

    /**
     * @brief Euclidean distance method.
     * 
     * Calculate the Euclidean distance between this coordinate and another.
     * 
     * @param other Reference to the other coordinate to use.
     * @return Euclidean distance between this coordinate and the other.
     */
    T distanceTo(const Coordinate<T> &other) const;
private:
    /**
     * X-value of this coordinate.
     */
    T x;

    /**
     * Y-value of this coordinate.
     */
    T y;
};

/*-----------------------------------------------------------------------------
 * method implementations
 *---------------------------------------------------------------------------*/

/*
 * Distance method.
 */
template <class T>
T Coordinate<T>::distanceTo(const Coordinate<T> &other) const {
    T dx = x - other.x;
    dx = dx * dx;
    T dy = y - other.y;
    dy = dy * dy;
    return sqrt(dx + dy);
}

// Doctest unit tests for distanceTo
TEST_CASE("testing Coordinate<T>::distanceTo") {
    Coordinate<float> f1, f2;

    // distance should be 0
    CHECK(f1.distanceTo(f2) == 0.0f);

    f1.setX(11.0f); f1.setY(11.0f);
    f2.setX(11.0f); f2.setY(11.0f);
    // distance should still be 0
    CHECK(f1.distanceTo(f2) == 0.0f);

    Coordinate<double> f3(0.7071068, 0.0d);
    Coordinate<double> f4(0.0d, 0.7071068);
    // distance should be 1 -- within floating point tolerance errors
    CHECK(f3.distanceTo(f4) == doctest::Approx(1.0));

    Coordinate<long double> f5(2.0L, 3.0L);
    Coordinate<long double> f6(-3.0L, -2.0L);
    // distance should be approx 7.071
    CHECK(f5.distanceTo(f6) == doctest::Approx(7.071));
}