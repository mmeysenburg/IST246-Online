#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "Coordinate.hpp"

/**
 * @brief CMP 246 Module 1 main program to exercise the Coordinate class.
 * 
 * This program uses the Monte Carlo technique to create an estimate of the 
 * number pi, using float and long double coordinates.
 */
int main() {
    // Mersenne Twister high-quality pseudo-random number generator
    std::mt19937_64 prng(time(0));

    // distributions to produce numbers in [0, 1] for floats and long doubles
    std::uniform_real_distribution<float> distribF(0.0f, 1.0f);
    std::uniform_real_distribution<long double> distribLD(0.0L, 1.0L);

    // prompt for number of coordinates
    unsigned n;
    std::cout << "Enter number of darts to throw: ";
    std::cin >> n;

    // perform the estimate using float coordinates
    Coordinate<float> zeroF, dartF;
    float numInF = 0.0f;
    for(unsigned i = 0u; i < n; i++) {
        dartF.setX(distribF(prng));
        dartF.setY(distribF(prng));
        if(zeroF.distanceTo(dartF) < 1.0f) {
            numInF++;
        }
    }
    float estPiF = numInF / n * 4.0f;

    std::cout << "Float estimate of pi: " << estPiF << std::endl;

    // perform the estimate using long double coordinates
    Coordinate<long double> zeroLD, dartLD;
    long double numInLD = 0.0L;
    for(unsigned i = 0u; i < n; i++) {
        dartLD.setX(distribLD(prng));
        dartLD.setY(distribLD(prng));
        if(zeroLD.distanceTo(dartLD) < 1.0L) {
            numInLD++;
        }
    }
    long double estPiLD = numInLD / n * 4.0L;

    std::cout << "Long double estimate of pi: " << estPiLD << std::endl;

    return EXIT_SUCCESS;
}