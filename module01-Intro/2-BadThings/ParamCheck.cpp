#include <cstdlib>
#include <iostream>

void foo(int x) {
    std::cout << "Foo says: You sent me: " << x << std::endl;
}

int main() {
    foo(13);
    foo(13.13);

    return EXIT_SUCCESS;
}