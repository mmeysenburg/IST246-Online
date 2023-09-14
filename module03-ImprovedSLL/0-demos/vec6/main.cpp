#include <cstdlib>
#include <iostream>
#include "Vector2D.hpp"

int main() {
    using namespace std;

    Vector2D<double> a(1, 2), b(3, 4);

    cout << "Vector a: " << a << endl;
    cout << "Vector b: " << b << endl;

    cout << "\nExecuting a = b." << endl;
    a = b;

    cout << "\nVector a: " << a << endl;
    cout << "Vector b: " << b << endl;

    cout << "\nSetting a.x to 13." << endl;
    a.setX(13);

    cout << "\nMUCH BETTER!" << endl;
    cout << "Vector a: " << a << endl;
    cout << "Vector b: " << b << endl;
        
    return EXIT_SUCCESS;
}