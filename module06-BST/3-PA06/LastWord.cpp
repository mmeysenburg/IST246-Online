#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "BST.hpp"

/**
 * CMP 246 PA06 demo app: find the last word (alphabetically) in the spell-
 * check demo dictionary.
 */
int main() {
    BST<std::string> dictionary;

    // populate the dictionary with the words from the spell checker demo.
    std::ifstream inFile("../2-SpellCheck/dictionary.txt");
    std::string word;
    while(inFile >> word) {
        dictionary.insert(word);
    }
    inFile.close();

    // use the removeMax method to get the last word in the dictionary
    word = dictionary.removeMax();

    std::cout << "The last word in the dictionary is: " << word << std::endl;

    return EXIT_SUCCESS;
}