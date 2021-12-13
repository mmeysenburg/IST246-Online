#include <cstdlib>
#include <fstream>
#include <iostream>
#include "../1-SimpleSLL/SimpleSLL.hpp"
#include "User.h"

/**
 * @brief CMP 246 Module 2 main program to exercise the SimpleSLL class. 
 * 
 * This program loads the username / password pairs from 'users.txt' into a 
 * SimpleSLL of User objects. Then, the program prompts for a username and 
 * password, and checks to see if that pair is in the list -- i.e., if the 
 * user has been authenticated or not. 
 */
int main() {
    // read users.txt into a list of User objects
    SimpleSLL<User> userList;

    std::ifstream inFile("users.txt");
    std::string name, password;
    while(inFile >> name) {
        inFile >> password;
        userList.add(User(name, password));
    }

    // prompt for username and password, then authenticate
    std::cout << "Enter username (q to quit): ";
    std::cin >> name;
    while(name != "q") {
        std::cout << "Enter password: ";
        std::cin >> password;

        User u(name, password);

        // username and password correct? 
        if(userList.contains(u) != -1) {
            std::cout << "WELCOME TO OUR SITE!" << std::endl;
            std::cout << "...logged off." << std::endl;
        } else {
            std::cout << "ACCESS DENIED." << std::endl;
        }

        // prompt for next username
        std::cout << "Enter username (q to quit): ";
        std::cin >> name;
    }
    
    return EXIT_SUCCESS;
}