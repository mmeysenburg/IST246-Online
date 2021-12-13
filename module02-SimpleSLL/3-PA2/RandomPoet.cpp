#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "SimpleSLL.hpp"

/**
 * Program to produce random poetry, using a linked list of dictionary words.
 *
 * TODO: complete Doxygen tags for the main program.
 * @author <your name here>
 * @date <date code was authored>
 */
int main() {
    // welcome message
    std::cout << "Welcome to the random poetry generator!\n" <<
        "Please wait while the dictionary is loaded." << std::endl;
    
    // load dictionary
    SimpleSLL<std::string> dictionary;
    std::ifstream inFile("dictionary.txt");
    std::string w;
    while(inFile >> w) {
        dictionary.add(w);
    }
    inFile.close();
    
    // lines, words, prompt variables
    unsigned lines = 0, words = 0, prompt = 0;
    
    // poetry loop
    do {
        std::cout << "Let's make some poetry, dude! Enter the number of lines: ";
        std::cin >> lines;
        
        std::cout << "Radical! Now, enter the number of words per line: ";
        std::cin >> words;
        
        std::cout << "\nHere's your poem, man!\n\n";
        
        for(unsigned i = 0u; i < lines; i++) {
            std::cout << "\t";
            for(unsigned j = 0u; j < words; j++) {
                // TODO: get a random word from the dictionary and print it,
                // followed by a space
            }
            std::cout << std::endl;
        }
        
        std::cout << "\nWould you like to make another poem? " << 
            "Enter 1 for yes, 0 for no: ";
        std::cin >> prompt;
        
    } while(prompt == 1);
    
    return EXIT_SUCCESS;
}