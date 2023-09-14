#include <cstdlib>
#include <iostream>
#include "Vector2D.hpp"

int main() {
    using namespace std;

    Vector2D<double> a, b(1, 2), c;

    cout << "Vector a: " << a << endl;
    cout << "Vector b: " << b << endl;

    c = a + b;
    cout << "Vector c = a + b: " << c << endl;

    c = c + b;
    cout << "Vector c = c + b: " << c << endl;
    
    return EXIT_SUCCESS;
}