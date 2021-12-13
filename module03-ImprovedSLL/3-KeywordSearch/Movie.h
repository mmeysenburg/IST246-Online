#pragma once

#include <doctest.h>
#include <iostream>
#include <string>
#include "../1-SLL/SLL.hpp"

/**
 * @brief CMP Module 3 class representing a movie.
 * 
 * Simple class representing a movie in a movie database. The movie has fields
 * for the title of the movie, the year of its release, and a list of keywords
 * describing the movie. The class has overrides for stream insertion, and 
 * the equality operator, which compares a movie object to a keyword string
 * and returns true if the keyword is in the movie's keyword list. 
 */
class Movie {
public:
    /**
     * @brief Initializing constructor.
     * 
     * @param inTitle String containing the title of the movie.
     * 
     * @param inYear Integer containing the year the movie was released.
     * 
     * @param inKeywords SLL of strings holding the keywords for this movie.
     */
    Movie(std::string inTitle, int inYear, const SLL<std::string> &inKeywords) 
        : title(inTitle), year(inYear), keywords(inKeywords) { }

    /**
     * Friend function override of stream insertion. Prints the name of the 
     * movie and the year it was released. 
     * 
     * @param out Reference to the std::ostream to write to.
     * 
     * @param mov Movie object to print.
     * 
     * @return The std::ostream object. 
     */
    friend std::ostream &operator<<(std::ostream &out, const Movie &mov);

    /**
     * Equality operator override.
     * 
     * @param keyword std::string containing a keyword.
     * 
     * @return true if this object's keyword list contains the parameter, 
     * false otherwise.
     */
    bool operator==(std::string keyword);

private:
    /** Movie's title */
    std::string title;

    /** Year movie was released */
    int year;

    /** List of keyword strings for the movie */
    SLL<std::string> keywords;
};