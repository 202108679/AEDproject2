#ifndef UNTITLED_LEITURA_H
#define UNTITLED_LEITURA_H

#include "Airlines.h"
#include "Airports.h"
#include "Flights.h"


#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class FileReader {
    public:
        FileReader(){};
        FileReader(string airlines_file,string airports_file, string flights_file) : airlines_file(airlines_file), airports_file(airports_file), flights_file(flights_file){};
        vector<Airlines> readAirlines();
        vector<Airports> readAirports();
        vector<Flights> readFlights();

    private:
        string airlines_file;
        string airports_file;
        string flights_file;
};


#endif //UNTITLED_IO_H