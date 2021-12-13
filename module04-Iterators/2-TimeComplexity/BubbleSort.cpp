#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

void print(int *pArr, int n) {
    std::cout << "[";
    for(int i = 0; i < n - 1; i++) {
        std::cout << pArr[i] << ", ";
    }
    std::cout << pArr[n - 1] << "]" << std::endl;
}

void bubbleSort(int *pArr, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(pArr[j] > pArr[j + 1]) {
                std::swap(pArr[j], pArr[j+1]);
            }
        }
    }
}

int main() {
    std::mt19937_64 prng(time(0));
    std::uniform_int_distribution<int> dist(0, 100);

    int n = 20;

    int *pArr = new int[n];
    for(int i = 0; i < n; i++) {
        pArr[i] = dist(prng);
    }

    print(pArr, n);
    bubbleSort(pArr, n);
    print(pArr, n);

    delete [] pArr;
    
    return EXIT_SUCCESS;
}
