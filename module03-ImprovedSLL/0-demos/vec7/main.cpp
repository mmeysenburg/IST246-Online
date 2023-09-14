#include <cstdlib>
#include <iostream>
#include "Vector2D.hpp"

int main() {
    using namespace std;

    Vector2D<double> a(1, 2), b(3, 4);

    cout << "Vector a: " << a << endl;
    cout << "Vector b: " << b << endl;

    Vector2D<double> c(a);

    cout << "\nNew vector c, based on a: " << c << endl;

    cout << "\nExecuting a.y = 27." << endl;
    a.setY(27);

    cout << "\nVector a: " << a << endl;
    cout << "Vector c: " << c << endl;
        
    return EXIT_SUCCESS;
}