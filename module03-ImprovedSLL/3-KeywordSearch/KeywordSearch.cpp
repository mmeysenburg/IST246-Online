#include <cstdio>
#include <cstdlib>
#include <doctest.h>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include "Movie.h"
#include "../1-SLL/SLL.hpp"

/**
 * Function to create a list of movie objects from a text file.
 * 
 * @param filename String containing the name of the file to read from.
 * 
 * @return SLL<Movie> object encapsulating all of the data in the file.
 */
SLL<Movie> makeMovieList(std::string filename) {

    std::ifstream inFile(filename);
    std::string title, keyword;
    int year;
    SLL<Movie> movieList;

    while(!inFile.eof()) {
        std::getline(inFile, title);

        inFile >> year;

        // there are a variable number of keywords per movie
        SLL<std::string> keywords;
        std::getline(inFile, keyword);
        // read until a sentinel value is detected
        while(keyword != "XXX") {
            keywords.add(keyword);
            std::getline(inFile, keyword);
        }

        // build Movie object based on the data, add to the return list
        movieList.add(Movie(title, year, keywords));
    }
    inFile.close();

    return movieList;
}

/**
 * Function to create a list of keyword strings from a text file.
 * 
 * @param filename String containing the name of the file to read from.
 * 
 * @return SLL<std::string> object encapsulating all of the keywords in the
 * input file.
 */
SLL<std::string> makeKeywordList(std::string filename) {
    // a STL set is used to elminate duplicates and sort the keywords
    // alphabetically
    std::set<std::string> keywordSet;

    std::ifstream inFile(filename);
    std::string title, keyword;
    int year;

    // read all the data
    while(!inFile.eof()) {
        // title and year are read, but not used here
        std::getline(inFile, title);
        inFile >> year;

        // variable number of keywords per movie
        std::getline(inFile, keyword);
        // read until sentinel value is encountered
        while(keyword != "XXX") {
            keywordSet.insert(keyword);
            std::getline(inFile, keyword);
        }
    }
    inFile.close();

    // Once we have the set, place its values into the SLL
    SLL<std::string> keywordList;
    // These iterators move through the set backwards, so when
    // added to the SLL the final list will be alpha A to Z
    auto itr = keywordSet.rbegin();
    while(itr != keywordSet.rend()) {
        keywordList.add(*itr);
        ++itr;
    }

    // Remove phantom empty string keyword 
    keywordList.remove(0);

    return keywordList;
}

/**
 * Function to build a list of all movies with a specified keyword.
 * 
 * @param movies Reference to a SLL<Movie> object containing the movies to 
 * search
 * 
 * @param keyword String keyword to search for
 * 
 * @return SLL<Movie> object will all movies that have the specified keyword
 */
SLL<Movie> findKeywordMatches(const SLL<Movie> &movies, std::string keyword) {
    SLL<Movie> matches;

    for(size_t i = 0; i < movies.size(); i++) {
        Movie m = movies.get(i);
        if(m == keyword) {
            matches.add(m);
        }
    }

    return matches;
}

/**
 * Show the menu on standard output.
 */
void showMenu() {
    std::cout << "\nSelect from one of the following options:" << std::endl;
    std::cout << "\t1) Display the movies in our database" << std::endl;
    std::cout << "\t2) Display a list of possible keywords" << std::endl;
    std::cout << "\t3) Perform a keyword search of the database" << std::endl;
    std::cout << "\t9) Exit the application" << std::endl;
    std::cout << "Enter selection: ";
}

/**
 * Display the menu and get the user's selection. Only allows valid inputs.
 */
int getSelection() {
    int choice = -1;

    while(!(choice == 1 || choice == 2 || choice == 3 || choice == 9)) {
        showMenu();
        std::cin >> choice;
    }

    return choice;
}

/**
 * Main method for the Module 3 keyword search application. 
 */
int main() {
    // build movie and keyword "databases"
    SLL<Movie> movieList = makeMovieList("movies.txt");
    SLL<std::string> keywordList = makeKeywordList("movies.txt");

    std::cout << "Welcome to our movie search program!" << std::endl;

    // main menu loop
    int choice = -1;
    while(choice != 9) {
        choice = getSelection();

        switch (choice)
        {
        case 1:
            // option 1: display all of the movies
            for(size_t i = 0; i < movieList.size(); i++) {
                std::cout << "\t" << movieList.get(i) << std::endl;
            }
            break;

        case 2:
            // option 2: display all of the keywords; they are shown in 
            // columnar format to make the list shorter
            for(size_t i = 0; i < keywordList.size(); i += 3) {
                printf("%26s  %26s  %26s\n", keywordList.get(i).c_str(), 
                    keywordList.get(i + 1).c_str(), 
                    keywordList.get(i + 2).c_str());
            }
            break;
        case 3:
            // option 3: get a keyword, search for matches, print results
            std::string keyword;
            std::getline(std::cin, keyword); // eat extra endline 
            std::cout << "Enter keyword: ";
            std::getline(std::cin, keyword);
            SLL<Movie> matches = findKeywordMatches(movieList, keyword);
            std::cout << "Movies matching " << keyword << std::endl;

            if(matches.isEmpty()) {
                std::cout << "\tNONE" << std::endl;
            } else {
                for(size_t i = 0; i < matches.size(); i++) {
                    std::cout << "\t" << matches.get(i) << std::endl;
                }
            }
            break;
        }
    }

    return EXIT_SUCCESS;
}