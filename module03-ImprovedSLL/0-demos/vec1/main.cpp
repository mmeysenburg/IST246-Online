#include <cstdlib>
#include <iostream>
#include "Vector2D.hpp"

int main() {
    using namespace std;

    Vector2D<double> a, b(1, 2);

    cout << "Vector a: ";
    a.print();

    cout << "Vector b: ";
    b.print();
    
    return EXIT_SUCCESS;
}