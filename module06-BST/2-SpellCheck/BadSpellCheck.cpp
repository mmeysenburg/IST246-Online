#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

/**
 * @brief See if a character is alphabetic.
 * 
 * Checks to see if a character is alphabetic.
 * 
 * @param c Character to check.
 * 
 * @return true if the character meets the stated requirements, false otherwise.
 */
bool isAlpha(char c) {
    return (c >= 'a' && c <='z');
}

/**
 * @brief Convert a string to all lowercase.
 * 
 * @param word std::string to convert.
 * 
 * @return all-lowercase version of the string.
 */
std::string toLower(std::string word) {
    std::transform(word.begin(), word.end(), word.begin(), 
        [](unsigned char c){ return std::tolower(c); });
    return word;
}

/**
 * @brief Remove all non-alphabetic characters from a string.
 * 
 * @param word std::string to conver.
 * 
 * @return word, but with all non-alphabetic characters removed.
 */
std::string stripNonAlpha(std::string word) {
    std::string newString = "";
    for(size_t i = 0; i < word.size(); i++) {
        if(isAlpha(word[i])) {
            newString += word[i];
        }
    }
    return newString;
}

/**
 * Application entry point.
 */
int main() {
    // read dictionary words into a STL list (a doubly-linked list)
    std::list<std::string> dictionary;
    std::ifstream dictionaryFile("dictionary.txt");
    std::string word;
    while(dictionaryFile >> word) {
        dictionary.push_back(word);
    }
    dictionaryFile.close();

    // read file to check from standard input
    while(std::cin >> word) {
        word = stripNonAlpha(toLower(word));
        // dump all words not in the dictionary to standard output
        if(word != "") {
            // STL list does not have a built-in search method, so we use the
            // std::find() function from the <algorithm> header.
            auto spot = std::find(dictionary.begin(), dictionary.end(), word);
            if(spot == dictionary.end()) {
                std::cout << word << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}