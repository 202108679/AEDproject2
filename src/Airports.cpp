
#include "Airports.h"

using namespace std;

Airports::Airports(string code_, string name_, string city_ , string country_, Coordinates coordinates_ ) :
        code(code_), name(name_), city (city_), country(country_), coordinates(coordinates_){}

std::string Airports::getCode() {
    return code;
}

std::string Airports::getName() {
    return name;
}

std::string Airports::getCity() {
    return city;
}

std::string Airports::getCountry(){
    return country;
}

Coordinates Airports::getCoordinates(){
    return coordinates;
}

