#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "../1-IteratorSLL/IteratorSLL.hpp"

// global integer for use in the RANDU PRNG
int vj;

/**
 * @brief Infamous RANDU PRNG
 * 
 * RANDU was provided as the random number generator for IBM mainframes in 
 * the 1960s and early 1970s. It is very flawed, and once the flaws were
 * discovered, quite a bit of research that used pseudo-random numbers had 
 * to be re-done. 
 * 
 * @see https://en.wikipedia.org/wiki/RANDU
 * 
 * @return int Pseudo-random integer in the range [INT_MIN, INT_MAX]
 */
int randu() {
    vj = 65539L * vj % 0x80000000;

    // map vj to [INT_MIN, INT_MAX]
    long double os = INT_MIN;
    long double oe = INT_MAX;
    long double is = 1;
    long double ie = 2147483647;
    long double o = os + (oe - os) / (ie - is) * (vj - is);
    return (int)o;
}

/**
 * @brief NIST monobit statistical test of PRNG quality
 * 
 * This is a fundamental test of pseudo-random number generator quality. 
 * Given a sequence of values, this test looks at the proportion of zeroes and
 * ones in their binary representations. A return value less than 0.01 indicates
 * that the sequence does not appear to be random. 
 * 
 * @see https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
 * 
 * @param numbers List of pseudo-random integers in the range [INT_MIN, INT_MAX]
 * 
 * @return double P-value, representing confidence that the sequence appears to
 * be random. A value less than 0.01 indicates that the sequence does not 
 * appear to be random. 
 */
double monobit(const IteratorSLL<int> &numbers) {
    double S = 0.0;

    // iterate through all values
    IteratorSLL<int>::Iterator i = numbers.front();
    while(i != numbers.end()) {
        // assuming 32-bit integers here
        unsigned mask = 0x00000001;

        // sum up zeroes / ones according to the NIST monobit test
        for(int j = 0; j < 32; j++) {
            int v = *i;
            S += (v & mask) == 0x00000000 ? -1.0 : 1.0;
            mask <<= 1;
        }
        i++;
    }

    // compute P-value according to the NIST monobit test
    double stat = abs(S) / sqrt(numbers.size() * 32.0);
    double PValue = erfc(stat / sqrt(2.0));

    return PValue;
}

/**
 * @brief Application entry point
 * 
 * @return int Exit status for the app.
 */
int main() {
    // Mersenne Twister: a high-quality PRNG
    std::mt19937_64 mtPRNG(time(0));

    // Minimum standard PRNG: just good enough
    std::minstd_rand0 minStdPRNG(time(0));

    // distribution object to map values to the proper range
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    // list holding pseudo-random integers
    IteratorSLL<int> randInts;

    // number of values to generate / test
    int n = 10000000;

    // test the Mersenne Twister PRNG
    for(int i = 0; i < n; i++) {
        int v = dist(mtPRNG);
        randInts.add(v);
    }
    double PValue = monobit(randInts);
    std::cout << "Mersenne Twister monobit: " << PValue << std::endl;

    // test the minimum standard PRNG
    randInts.clear();
    for(int i = 0; i < n; i++) {
        int v = dist(minStdPRNG);
        randInts.add(v);
    }
    PValue = monobit(randInts);
    std::cout << "Minimum standard monobit: " << PValue << std::endl;

    // test RANDU PRNG
    randInts.clear();
    vj = time(0);
    for(int i = 0; i < n; i++) {
        int v = randu();
        randInts.add(v);
    }
    PValue = monobit(randInts);
    std::cout << "RANDU monobit: " << PValue << std::endl;

    return EXIT_SUCCESS;
}