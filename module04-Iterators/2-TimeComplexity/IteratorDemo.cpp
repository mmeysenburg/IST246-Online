#include <doctest.h>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include "IteratorSLL.hpp"
#include "SLL.hpp"

void fillLists(int n, std::uniform_int_distribution<int> &dist, 
    std::mt19937_64 &prng,SLL<int> &sllList, IteratorSLL<int> &iteratorList) {

    sllList.clear();
    iteratorList.clear();

    for(int i = 0; i < n; i++) {
        int v = dist(prng);
        sllList.add(v);
        iteratorList.add(v);
    }
}

void traverseSLLList(SLL<int> &list) { 
    list.numFOs = 0ul;

    for(size_t i = 0; i < list.size(); i++) {
        int v = list.get(i);
        if(v % 2 == 0) {
            list.set(i, v * 2);
        }
    }
}

void traverseIteratorList(IteratorSLL<int> &list) {
    list.numFOs = 0ul;

    IteratorSLL<int>::Iterator i = list.front();
    while(i != list.end()) {
        if(*i % 2 == 0) {
            *i *= 2;
        }
        i++;
    }
}

int main() {

    // high quality pseudo-random number generator
    std::mt19937_64 prng(time(0));
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    // two one without iterators, one with
    SLL<int> sllList;
    IteratorSLL<int> iteratorList;

    // repeat "time" trials with multiple list sizes
    for(int n = 2; n <= 1048576; n *= 2) {
        long double totSLLFOs = 0.0l;
        long double totIteratorFOs = 0.0l;
        // perform 5 trials for each n
        for(int i = 0; i < 5; i++) {
            fillLists(n, dist, prng, sllList, iteratorList);
            traverseIteratorList(iteratorList);
            totSLLFOs += iteratorList.numFOs;
            traverseSLLList(sllList);
            totIteratorFOs += sllList.numFOs;
        }
        printf("%d,%Lf,%Lf\n", n, totSLLFOs / 5.0, totIteratorFOs / 5.0);
    }

    return EXIT_SUCCESS;
}