#include <cstdlib>
#include <iostream>
#include <limits>

int main() {
    // display min / max value of signed, unsigned integral types
    std::numeric_limits<short> signedShort;
    std::numeric_limits<unsigned short> unsignedShort;
    std::numeric_limits<int> signedInt;
    std::numeric_limits<unsigned> unsignedInt;
    std::numeric_limits<long> signedLong;
    std::numeric_limits<unsigned long> unsignedLong;

    std::cout << "signed short: [" << signedShort.min() << ", " <<
        signedShort.max() << "]" << std::endl;
    std::cout << "unsigned short: [" << unsignedShort.min() << ", " <<
        unsignedShort.max() << "]" << std::endl;

    std::cout << "signed int: [" << signedInt.min() << ", " <<
        signedInt.max() << "]" << std::endl;
    std::cout << "unsigned int: [" << unsignedInt.min() << ", " <<
        unsignedInt.max() << "]" << std::endl;

    std::cout << "signed long: [" << signedLong.min() << ", " <<
        signedLong.max() << "]" << std::endl;
    std::cout << "unsigned long: [" << unsignedLong.min() << ", " <<
        unsignedLong.max() << "]" << std::endl;

    return EXIT_SUCCESS;
}