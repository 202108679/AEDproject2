//
// Created by Utilizador on 06/01/2023.
//

#ifndef PROJ2_AED_AIRTRAFFICCONTROL_H
#define PROJ2_AED_AIRTRAFFICCONTROL_H


#include <map>
#include "FileReader.h"
#include "Path.h"
#include "graph.h"
#include <set>
#include <unordered_set>


typedef pair<int, int> flight;
struct comp
{

    bool operator()(const flight &l, const flight &r) const
    {
        if (l.first == r.first) {
            return l.second > r.second;
        }

        return l.first < r.first;
    }
};


class AirTrafficControl{
public:
    AirTrafficControl(){};
    AirTrafficControl(string airlines_file,string airports_file, string flights_file);
    vector<Path> fliPortPort(int s, int d);
    vector<Path> fliPortCity(int s, list<Airports> d);
    vector<Path> fliCityPort(list<Airports> s, int d);
    vector<Path> fliCityCity(list<Airports> s, list<Airports> d);
    vector<Path> fliLocPort(Coordinates s, int d);
    vector<Path> fliLocCity(Coordinates s, list<Airports> d);
    vector<Path> fliPortPortRes(int s, int d, unordered_set<string> &a);
    vector<Path> fliPortCityRes(int s, list<Airports> d, unordered_set<string> &a);
    vector<Path> fliCityPortRes(list<Airports> s, int d, unordered_set<string> &a);
    vector<Path> fliCityCityRes(list<Airports> s, list<Airports> d, unordered_set<string> &a);
    vector<Path> fliLocPortRes(Coordinates s, int d, unordered_set<string> &a);
    vector<Path> fliLocCityRes(Coordinates s, list<Airports> d, unordered_set<string> &a);
    unordered_map<string, int> getCodeToInt();
    unordered_map<int, Airports> getIntToPort();
    unordered_map<string, list<Airports>> getPortsByCity();
    unordered_map<string, Airlines> getMapAirlines();
    void RestrictTravel(unordered_set<string> &s);

    vector<Airports> leaveAirports(string v);
    int countryDestiny(string p);
    int cityDestiny(string p);
    vector<Airlines> leaveFligth(string v);

    vector<Airports> comeAirports(string v);
    int countryComing(string p);
    int cityComing(string p);
    vector<Airlines> comeFligth(string v);

    vector<pair<Airports, int>> DistanceAirports(string sr, int max);
    vector<pair<int, int>> cityForDist(string sr, int max);
    vector<pair<int, int>> countryForDist(string sr, int max);
    vector<pair<int, int>> airportsForDist(string sr, int max);

    vector<pair<int, int>> cityForDist2(string sr, int max);
    void nodeAirline();


private:
    FileReader reader;
    vector<Airports> vecAirports;
    vector<Airlines> vecAirlines;
    vector<Flights> vecFlights;
    unordered_map<string, int> airportCodeToInt;
    unordered_map<int, Airports> intToAirport;
    unordered_map<string, list<Airports>> airportsByCity;
    map<flight, vector<string>, comp> mapFlight;
    unordered_map<string, Airlines> mapAirlines;
    Graph graphComplete;
    void setMaps();
    void makeGraph();
};


#endif //PROJ2_AED_AIRTRAFFICCONTROL_H
