//
// Created by Utilizador on 24/12/2022.
//

#include <iostream>
#include <string>
#include <vector>
#include "Airlines.h"
#include "FileReader.h"
#include "Airports.h"
#include "Flights.h"

using namespace std;

vector<Airlines> FileReader::readAirlines() {
    ifstream airline(airlines_file);

    if (!airline.is_open()){
        cerr << "Could not access airlines.csv file.\n";
        exit(EXIT_FAILURE);
    }

    vector<Airlines> airlines;
    string line;
    //string code, name, callSign, country;
    getline(airline, line); // first line
    while(getline(airline, line)){
        vector<string> parts;
        string part;
        stringstream ss(line);
        while(getline(ss,part,',')){
            parts.push_back(part);
        }
        Airlines air = Airlines(parts[0], parts[1], parts[2], parts[3]);
        airlines.push_back(air);
        }
        return  airlines;
    }

vector<Airports> FileReader::readAirports(){
    ifstream airports(airports_file);

    if (!airports.is_open()){
        cerr << "Could not access airports.csv file.\n";
        exit(EXIT_FAILURE);
    }

    vector<Airports> v_airports;
    string line;
    /*
    string code, name, city, country;
    string latitude,longitude;
     */
    getline(airports, line); // first line
    while(getline(airports, line)){
        vector<string> parts;
        string part;
        stringstream ss(line);
        while(getline(ss,part,',')){
            parts.push_back(part);
        }
        Airports airport = Airports(parts[0], parts[1], parts[2], parts[3], Coordinates(stod(parts[4]), stod(parts[5])));
        v_airports.push_back(airport);
    }
    return  v_airports;
}


vector<Flights> FileReader::readFlights(){
    ifstream flights(flights_file);

    if (!flights.is_open()){
        cerr << "Could not access flights.csv file.\n";
        exit(EXIT_FAILURE);
    }

    vector<Flights> v_flights;
    string line;

    getline(flights, line); // first line
    while(getline(flights, line)){
        vector<string> parts;
        string part;
        stringstream ss(line);
        while(getline(ss,part,',')){
            parts.push_back(part);
        }
        Flights flight = Flights(parts[0], parts[1], parts[2]);
        v_flights.push_back(flight);
    }
    return  v_flights;
}

/*
unordered_map<int,Airports> FileReader::readToMapAirports() {
    ifstream airports(airports_file);

    if (!airports.is_open()) {
        cerr << "Could not access airports.csv file.\n";
        exit(EXIT_FAILURE);
    }

    unordered_map<int, Airports> m_airports;
    int key = 1;
    string line;
    getline(airports, line); // first line
    while (getline(airports, line)) {
        vector<string> parts;
        string part;
        stringstream ss(line);
        while (getline(ss, part, ',')) {
            parts.push_back(part);
        }
        Airports airport = Airports(parts[0], parts[1], parts[2], parts[3],
                                    Coordinates(stod(parts[4]), stod(parts[5])));
        m_airports.insert({key, airport});
        key++;
    }
    return m_airports;


    unordered_map<string,Airports> FileReader::readToMapAirports2() {
        ifstream airports(airports_file);

        if (!airports.is_open()) {
            cerr << "Could not access airports.csv file.\n";
            exit(EXIT_FAILURE);
        }

        unordered_map<string, Airports> m_airports;
        string line;
        getline(airports, line); // first line
        while (getline(airports, line)) {
            vector<string> parts;
            string part;
            stringstream ss(line);
            while (getline(ss, part, ',')) {
                parts.push_back(part);
            }
            Airports airport = Airports(parts[0], parts[1], parts[2], parts[3],
                                        Coordinates(stod(parts[4]), stod(parts[5])));
            m_airports.insert({parts[0], airport});
        }
        return m_airports;
}
 */