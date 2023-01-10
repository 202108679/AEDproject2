//
// Created by Utilizador on 25/12/2022.
//

#ifndef PROJ2_AED_AIRPORTS_H
#define PROJ2_AED_AIRPORTS_H


#include <list>
#include <string>
#include "Coordinates.h"
using namespace std;

class Airports {
public:
    Airports(): code(" "), name(" "), city(" "), country(" "), coordinates(Coordinates()){};
    Airports(string  code_, string  name_,string  city_,string  country_, Coordinates coordinates_);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    Coordinates getCoordinates();
private:
    string code;
    string name;
    string city;
    string country;
    Coordinates coordinates;
};

#endif //PROJ2_AED_AIRPORTS_H
