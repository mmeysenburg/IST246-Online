#include <cstdlib>
#include <iostream>

void bar(double &d) {
    d = 13;
    std::cout << "in bar, d = " << d << std::endl;
}

void foo(const double &d) {
    // this would be a syntax error
    //d = 13; 
}

int main() {
    double md = 0;

    std::cout << "before bar, md = " << md << std::endl;
    bar(md);
    std::cout << "after bar, md = " << md << std::endl;

    return EXIT_SUCCESS;
}
