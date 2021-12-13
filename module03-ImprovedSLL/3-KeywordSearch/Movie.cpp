#include "Movie.h"

//-----------------------------------------------------------------------------
// Movie class function implementations
//-----------------------------------------------------------------------------

/*
 * Stream insertion friend function.
 */
std::ostream &operator<<(std::ostream &out, const Movie &mov) {
    out << mov.title << " (" << mov.year << ")";
    // out << mov.keywords;
    return out;
}

/*
 * Equality operator override. 
 */
bool Movie::operator==(std::string keyword) {
    return keywords.contains(keyword) != -1;
}