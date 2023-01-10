
#include "Flights.h"

using namespace std;

Flights::Flights(string source_, string target_, string airline_) :
        source(source_), target(target_), airline (airline_){}

std::string Flights::getSource()  {
    return source;
}

std::string Flights::getTarget() {
    return target;
}

std::string Flights::getAirline(){
    return airline;
}



