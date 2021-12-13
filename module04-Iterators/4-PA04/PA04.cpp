#include <cstdlib>
#include <iostream>
#include "IteratorSLL.hpp"

int main() {
    IteratorSLL<int> L, M;

    for(int i = 4; i >= 1; i--) {
        L.add(i);
    }

    for(int i = -5; i <= -1; i++) {
        M.add(i);
    }

    IteratorSLL<int> merged(L, M);

    std::cout << "List L: " << L << std::endl;
    std::cout << "List M: " << M << std::endl;
    std::cout << "Merged list: " << merged << std::endl;
    
    return EXIT_SUCCESS;
}