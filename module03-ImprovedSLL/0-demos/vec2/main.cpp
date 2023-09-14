#include <cstdlib>
#include <iostream>
#include "Vector2D.hpp"

int main() {
    using namespace std;
    Vector2D<double> a, b(1, 2), c;

    cout << "Vector a: ";
    a.print();
    cout << "Vector b: ";
    b.print();

    c = a + b;
    cout << "\nc = a + b: ";
    c.print();

    c = c + b;
    cout << "\nc = c + b: ";
    c.print();
    
    return EXIT_SUCCESS;
}