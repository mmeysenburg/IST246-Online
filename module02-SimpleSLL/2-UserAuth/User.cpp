#include "User.h"

// function definitions for the User class.

// copy constructor
User::User(const User &other) {
    name = other.name;
    password = other.password;
}

// assignment operator
User& User::operator=(const User &other) {
    name = other.name;
    password = other.password;

    return *this;
}

// equality operator
bool User::operator==(const User &other) {
    return name == other.name && password == other.password;
}