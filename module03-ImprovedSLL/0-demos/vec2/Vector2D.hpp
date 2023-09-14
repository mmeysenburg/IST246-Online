#pragma once
#include <iostream>

/**
 * @brief Simple vector in two-dimensional space.
 * 
 * This class adds an override for the addition operator.
 * 
 * @tparam T Numeric type used to hold x and y.
 */
template <class T> 
class Vector2D {
public:
    /**
     * @brief Construct a new Vector2D object
     * 
     * Note the use of default values for the parameters. 
     * 
     * @param ix value for the x coordinate of this vector.
     * @param iy value for the y coordinate of this vector. 
     */
    Vector2D(T ix = 0, T iy = 0) : x(ix), y(iy) { }

    /**
     * @brief Accessor for the x field
     * 
     * @return value of the x field
     */
    T getX() { return x; }

    /**
     * @brief Accessor for the y field
     * 
     * @return value of the y field
     */
    T getY() { return y; }

    /**
     * @brief Override of the addition operator.
     * 
     * @param other Vector2D<T> to add to this one.
     * @return Vector2D<T> reference to this object. 
     */
    Vector2D<T> operator+(const Vector2D<T> &other) const;

    /**
     * @brief Print the vector
     * 
     */
    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
    
    /**
     * @brief Mutator for the x field.
     * 
     * @param ix New value for the x field
     */
    void setX(T ix) { x = ix; }

    /**
     * @brief Mutator for the y field.
     * 
     * @param iy New value for the y field
     */
    void setY(T iy) { y = iy; }
private:
    /** X field.*/
    T x;

    /** Y field. */
    T y;
};

template <class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> &other) const {
    Vector2D c(x + other.x, y + other.y);
    return c;
}