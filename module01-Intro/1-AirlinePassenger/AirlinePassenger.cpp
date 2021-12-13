#include <cstdlib>
#include <iostream>
#include "AirlinePassenger.h"

AirlinePassenger::AirlinePassenger(std::string fn, std::string n, 
    std::string s, int mpc) : flightNumber(fn), name(n), seat(s), 
    mealPreferenceCode(mpc) {

}

// ... and more

std::ostream& operator<<(std::ostream &out, const AirlinePassenger &ap) {
    out << "Flight: " << ap.flightNumber << std::endl;
    out << "Passenger: " << ap.name << std::endl;
    out << "Seat: " << ap.seat << std::endl;
    out << "Meal preference code: " << ap.mealPreferenceCode << std::endl;
    return out;
}

int main() {
    AirlinePassenger ap("UAL1345", "Jane Smith", "32A", 1); 

    ap.setSeat("1B");

    AirlinePassenger *pAp = new AirlinePassenger("SWA5462", "James Johnson", 
        "25C", 2);

    pAp->setSeat("25A");

    AirlinePassenger &apr = ap;

    std::cout << ap << std::endl;

    std::cout << *pAp << std::endl;

    std::cout << apr << std::endl;

    apr.setSeat("13D");

    std::cout << ap << std::endl;
    
    std::cout << apr << std::endl;

    delete pAp;

    return EXIT_SUCCESS;
}