#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

int sum(int* pArr, int n) {
    int s = 0;
    for(int i = 0; i < n; i++) {
        s += pArr[i];
    }

    return s;
}

int main() {
    // random number generator 
    std::mt19937 prng(time(0));
    std::uniform_int_distribution<int> dist(0, 100);

    // make an array with 100000 elements, fill with random values
    int *pArr = new int[100000];
    for(int i = 0; i < 100000; i++) {
        pArr[i] = dist(prng);
    }

    // output the sum
    std::cout << "The sum of the array is: " << sum(pArr, 100000) << std::endl;

    // free memory used by the array
    delete [] pArr;

    return EXIT_SUCCESS;
}