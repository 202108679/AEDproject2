//
// Created by guca on 25-12-2022.
//

#ifndef PROJ2_AED_FLIGHTS_H
#define PROJ2_AED_FLIGHTS_H

#include <list>
#include <string>

using namespace std;


class Flights {

public:
    Flights(string  source_, string  target_,string  airline_);
    string getSource();
    string getTarget();
    string getAirline();


private:
    string source;
    string target;
    string airline;

};



#endif //PROJ2_AED_FLIGHTS_H
