#pragma once

#include <iostream>
#include <string> 

class AirlinePassenger {
private:
    std::string flightNumber;
    std::string name;
    std::string seat;
    int mealPreferenceCode;

public:
    AirlinePassenger(std::string fn, std::string n, std::string s, int mpc);

    // ... and more

    void setSeat(std::string s) { seat = s; }

    friend std::ostream& operator<<(std::ostream &out, const AirlinePassenger &ap);
};