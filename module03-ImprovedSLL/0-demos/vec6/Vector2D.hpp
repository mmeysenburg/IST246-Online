#pragma once
#include <iostream>

/**
 * @brief Simple vector in two-dimensional space.
 * 
 * This class adds an override of the assignment operator. 
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
    Vector2D(T ix = 0, T iy = 0);

    /**
     * @brief Destroy the Vector2D object
     * 
     */
    ~Vector2D();

    /**
     * @brief Accessor for the x field
     * 
     * @return value of the x field
     */
    T getX() { return *pX; }

    /**
     * @brief Accessor for the y field
     * 
     * @return value of the y field
     */
    T getY() { return *pY; }

    /**
     * @brief Override of the addition operator.
     * 
     * @param other Vector2D<T> to add to this one.
     * @return Vector2D<T> reference to this object. 
     */
    Vector2D<T> operator+(const Vector2D<T> &other) const;

    /**
     * @brief Override of the assignment operator.
     * 
     * @param other vector to copy from.
     * @return Vector2D<T>& reference to this vector, for chaining.
     */
    Vector2D<T> &operator=(const Vector2D<T> &other);

    /**
     * @brief Override of the stream insertion operator.
     * 
     * Note this is not a member of the class, but a friend function. 
     * 
     * @param out ostream reference to print to
     * @param vec Vecto2D<T> object to print
     * @return std::ostream& reference to the ostream, for chaining.
     */
    template <class T1> 
    friend std::ostream& operator<<(std::ostream& out, const Vector2D<T1> &vec);

    /**
     * @brief Mutator for the x field.
     * 
     * @param ix New value for the x field
     */
    void setX(T ix) { *pX = ix; }

    /**
     * @brief Mutator for the y field.
     * 
     * @param iy New value for the y field
     */
    void setY(T iy) { *pY = iy; }
private:
    /** Pointer to the x field.*/
    T *pX;

    /** Pointer to the y field. */
    T *pY;
};

template <class T>
Vector2D<T>::Vector2D(T ix, T iy) {
    pX = new T(ix);
    pY = new T(iy);
}

template <class T>
Vector2D<T>::~Vector2D() {
    delete pX;
    delete pY;
}

template <class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> &other) const {
    Vector2D c(*pX + *(other.pX), *pY + *(other.pY));
    return c;
}

template <class T>
Vector2D<T> &Vector2D<T>::operator=(const Vector2D<T> &other) {
    *pX = *other.pX;
    *pY = *other.pY;
    return *this;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector2D<T> &vec) {
    out << "(" << *(vec.pX) << ", " << *(vec.pY) << ")";
    return out; 
}