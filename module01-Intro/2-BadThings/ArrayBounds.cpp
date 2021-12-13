#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

int main() {
    // random number generator 
    std::mt19937 prng(time(0));
    std::uniform_int_distribution<int> dist(0, RAND_MAX);

    // make an array with 100000 elements, fill with 1's
    int *pArr = new int[100000];
    for(int i = 0; i < 100000; i++) {
        pArr[i] = 1;
    }

    // overwrite the array values
    for(int i = 0; i <= 100000; i++) {
        pArr[i] = dist(prng);

        // every so often report how we're doing
        if(i % 10000 == 0) {
            std::cout << "Overwriting element " << i << std::endl;
        }
    }

    // free memory used by the array
    delete [] pArr;

    return EXIT_SUCCESS;
}