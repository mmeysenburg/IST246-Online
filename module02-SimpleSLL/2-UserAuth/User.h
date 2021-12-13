#pragma once

#include <iostream>
#include <string>

/**
 * @brief CMP 246 Module 2 class representing an online user.
 * 
 * Simple class holding the name and password of a fictional online user.
 * Has a copy constructor and overrides assignment (=), equality testing (==),
 * and stream insertion (<<).
 */
class User {
public:
    /**
     * @brief Default constructor.
     * 
     * Builds a default user, with empty-string name and password fields.
     */
    User() : name(""), password("") { }

    /**
     * @brief Initializing constructor.
     * 
     * Builds a user with the specified name and password.
     * 
     * @param n std::string containing the user's username.
     * 
     * @param p std::string containing the user's password.
     */
    User(std::string n, std::string p) : name(n), password(p) { }

    /**
     * @brief Copy constructor.
     * 
     * Builds a user just like another user.
     * 
     * @param other User object to copy name and password from.
     */
    User(const User &other);

    /**
     * @brief Name accessor.
     * 
     * Get this user's name.
     * 
     * @return std::string containing this user's name.
     */
    std::string getName() { return name; }

    /**
     * @brief Password accessor.
     * 
     * Get this user's password.
     * 
     * @return std::string containing this user's password.
     */
    std::string getPassword() { return password; }

    /**
     * @brief Assignment operator.
     * 
     * Overridden assignment operator, allowing safe assignment of one User 
     * object to another.
     * 
     * @param other Reference to the user to copy name and password from. 
     * 
     * @return Reference to this object.
     */
    User& operator=(const User &other);

    /**
     * @brief Equality operator.
     * 
     * Overridden equality testing operator, for comparing two User objects.
     * 
     * @param other Reference to the other user to compare against. 
     * 
     * @return true if this user has same name and password as the other user,
     * false otherwise.
     */
    bool operator==(const User &other);

    /**
     * @brief Stream insertion operator.
     * 
     * Overridden stream insertion operator, defined as a friend to the User
     * class. 
     * 
     * @param out Reference to the output stream to write to.
     * 
     * @param user Reference to the User object to write to the output stream.
     * 
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream &out, const User &user) {
        out << user.name << " (" << user.password << ")";
        return out;
    }

private:
    /** Name of the user. */
    std::string name;
    /** Password of the user. */ 
    std::string password;
};