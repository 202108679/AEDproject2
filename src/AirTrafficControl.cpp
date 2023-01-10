//
// Created by Utilizador on 06/01/2023.
//

#include "AirTrafficControl.h"


AirTrafficControl::AirTrafficControl(string airlines_file,string airports_file, string flights_file){
    reader = FileReader(airlines_file, airports_file, flights_file);
    vecAirports = reader.readAirports();
    vecAirlines = reader.readAirlines();
    vecFlights = reader.readFlights();
    setMaps();
    graphComplete = Graph(mapFlight.size(),true);
    makeGraph();
}

void AirTrafficControl::setMaps(){
    int index = 1;
    for(Airports a : this->vecAirports){
        airportCodeToInt.insert({a.getCode(), index});
        intToAirport.insert({index,a});
        index++;
        if(airportsByCity.find(a.getCity()) == airportsByCity.end()){
            list<Airports> tmp = {a};
            airportsByCity.insert(make_pair(a.getCity(),tmp));
        }
        else{
            airportsByCity[a.getCity()].push_back(a);
        }
    }

    for(Flights f: vecFlights){
        int s = airportCodeToInt[f.getSource()];
        int d = airportCodeToInt[f.getTarget()];
        if(mapFlight.find({s,d}) == mapFlight.end()){
            mapFlight.insert({{s,d}, {f.getAirline()}});
        }
        else{
            mapFlight[{s,d}].push_back(f.getAirline());
        }
    }
    for(Airlines a: this->vecAirlines) {
        mapAirlines.insert({a.getCode(),a});
    }
}


void AirTrafficControl::makeGraph(){
    for (const auto &entry: mapFlight)
    {
        flight f = entry.first;
        graphComplete.addEdge(f.first, f.second, entry.second, intToAirport[f.first].getCoordinates().distance(intToAirport[f.second].getCoordinates()));
        graphComplete.addArriveEdge(f.first, f.second, entry.second);
    }
    nodeAirline();

}

void AirTrafficControl::nodeAirline(){
    for(int i = 1;  i <= vecAirports.size(); i++){
        graphComplete.addAirport(i, intToAirport[i]);
    }
}

unordered_map<string, int> AirTrafficControl::getCodeToInt(){
    return airportCodeToInt;
}

unordered_map<int, Airports> AirTrafficControl::getIntToPort(){
    return intToAirport;
}

unordered_map<string, list<Airports>> AirTrafficControl::getPortsByCity(){
    return airportsByCity;
}

unordered_map<string, Airlines> AirTrafficControl::getMapAirlines(){
    return mapAirlines;
}


void AirTrafficControl::RestrictTravel(unordered_set<string> &s) {
    map<flight, vector<string>, comp> v = {};
    for (Flights f: this->vecFlights) {
        if (s.find(f.getAirline()) != s.end()) {
            int sr = airportCodeToInt[f.getSource()];
            int dt = airportCodeToInt[f.getTarget()];
            graphComplete.cleanRestrictedEdge(sr, dt);
            if (v.find({sr, dt}) == v.end()) {
                v.insert({{sr, dt},
                          {f.getAirline()}});
            } else {
                v[{sr, dt}].push_back(f.getAirline());
            }
        }
    }
    for (const auto &entry: v) {
        flight f = entry.first;
        graphComplete.addRestrictedEdge(f.first, f.second, entry.second,
                                            intToAirport[f.first].getCoordinates().distance(
                                                    intToAirport[f.second].getCoordinates()));

    }
}

// O(|V|+|E|)
vector<Path> AirTrafficControl::fliPortPort(int s, int d){
    vector<Path> final = graphComplete.PathsMin(s, d);
    return final;
}

// O(|V|+|E|)
vector<Path> AirTrafficControl::fliPortCity(int s, list<Airports> d){
    vector<Path> final = {};
    list<int> l;
    for(auto a : d){
        l.push_back(airportCodeToInt[a.getCode()]);
    }
    vector<pair<int,int>> minPath = graphComplete.distance_2(s, l);
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsMin(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;

}

// O(N(|V|+|E|))
vector<Path> AirTrafficControl::fliCityPort(list<Airports> s, int d){
    int min = INT_MAX;
    vector<int> proxAirport;
    for(auto airport : s) {
        proxAirport.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    for(int a: proxAirport){
        int n = graphComplete.distance(a,d);
        if(n>0 && n <min){
            minPath.clear();
            min = n;
        }
        if(n == min){
            minPath.push_back({a,d});
        }
    }
    vector<Path> final = {};
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsMin(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;


}

vector<Path> AirTrafficControl::fliCityCity(list<Airports> s, list<Airports> d){
    list<int> source;
    list<int> target;
    for(auto airport : s) {
        source.push_back(airportCodeToInt[airport.getCode()]);
    }
    for(auto airport : d) {
        target.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    int min = INT_MAX;
    for(int i: source){
        graphComplete.distance_3(i,target,min,minPath);
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsMin(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

vector<Path> AirTrafficControl::fliLocPort(Coordinates s, int d){
    int min = INT_MAX;
    vector<int> proxAirport;
    for(auto airport : vecAirports) {
        if (s.distance(airport.getCoordinates()) <= 250) {
            proxAirport.push_back(airportCodeToInt[airport.getCode()]);
        }
    }
    vector<pair<int,int>> minPath;
    for(int a: proxAirport){
        int n = graphComplete.distance(a,d);
        if(n>0 && n <min){
            minPath.clear();
            min = n;
        }
        if(n == min){
            minPath.push_back({a,d});
        }
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsMin(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

vector<Path> AirTrafficControl::fliLocCity(Coordinates s, list<Airports> d){
    list<int> source;
    list<int> target;
    for(auto airport : vecAirports) {
        if (s.distance(airport.getCoordinates()) <= 250) {
            source.push_back(airportCodeToInt[airport.getCode()]);
        }
    }
    for(auto airport : d) {
        target.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    int min = INT_MAX;
    for(int i: source){
        graphComplete.distance_3(i,target,min,minPath);
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsMin(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

////////////////////////////////////////////

vector<Path> AirTrafficControl::fliPortPortRes(int s, int d, unordered_set<string> &a){
    RestrictTravel(a);
    vector<Path> final = graphComplete.PathsCond(s, d);
    return final;
}

vector<Path> AirTrafficControl::fliPortCityRes(int s, list<Airports> d, unordered_set<string> &a){
    RestrictTravel(a);
    vector<Path> final;
    list<int> l;
    for(auto a : d){
        l.push_back(airportCodeToInt[a.getCode()]);
    }
    vector<pair<int,int>> minPath = graphComplete.distance_2(s, l, false);
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsCond(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;

}

// O(N(|V|+|E|))
vector<Path> AirTrafficControl::fliCityPortRes(list<Airports> s, int d, unordered_set<string> &a){
    RestrictTravel(a);
    int min = INT_MAX;
    vector<int> proxAirport;
    for(auto airport : s) {
        proxAirport.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    for(int a: proxAirport){
        int n = graphComplete.distance(a,d, false);
        if(n>0 && n <min){
            minPath.clear();
            min = n;
        }
        if(n == min){
            minPath.push_back({a,d});
        }
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsCond(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;


}

vector<Path> AirTrafficControl::fliCityCityRes(list<Airports> s, list<Airports> d, unordered_set<string> &a){
    RestrictTravel(a);
    list<int> source;
    list<int> target;
    for(auto airport : s) {
        source.push_back(airportCodeToInt[airport.getCode()]);
    }
    for(auto airport : d) {
        target.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    int min = INT_MAX;
    for(int i: source){
        graphComplete.distance_3(i,target,min,minPath, false);
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsCond(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

vector<Path> AirTrafficControl::fliLocPortRes(Coordinates s, int d, unordered_set<string> &a){
    RestrictTravel(a);
    int min = INT_MAX;
    vector<int> proxAirport;
    for(auto airport : vecAirports) {
        if (s.distance(airport.getCoordinates()) <= 250) {
            proxAirport.push_back(airportCodeToInt[airport.getCode()]);
        }
    }
    vector<pair<int,int>> minPath;
    for(int a: proxAirport){
        int n = graphComplete.distance(a,d, false);
        if(n>0 && n <min){
            minPath.clear();
            min = n;
        }
        if(n == min){
            minPath.push_back({a,d});
        }
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsCond(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

vector<Path> AirTrafficControl::fliLocCityRes(Coordinates s, list<Airports> d, unordered_set<string> &a){
    RestrictTravel(a);
    list<int> source;
    list<int> target;
    for(auto airport : vecAirports) {
        if (s.distance(airport.getCoordinates()) <= 250) {
            source.push_back(airportCodeToInt[airport.getCode()]);
        }
    }
    for(auto airport : d) {
        target.push_back(airportCodeToInt[airport.getCode()]);
    }
    vector<pair<int,int>> minPath;
    int min = INT_MAX;
    for(int i: source){
        graphComplete.distance_3(i,target,min,minPath, false);
    }
    vector<Path> final;
    for(auto p : minPath){
        vector<Path> tmp = graphComplete.PathsCond(p.first, p.second);
        final.insert(final.end(), tmp.begin(), tmp.end());
    }
    return final;
}

// O(N)
vector<Airports> AirTrafficControl::leaveAirports(string v){
    vector<int> tmp = graphComplete.targetAirports(airportCodeToInt[v]);
    vector<Airports> result;
    for(int n : tmp){
        result.push_back(intToAirport[n]);
    }
    return result;
}

// O(N)
int AirTrafficControl::countryDestiny(string p){
    vector<int> tmp = graphComplete.targetAirports(airportCodeToInt[p]);
    set<string> result;
    for(int n : tmp){
        result.insert(intToAirport[n].getCountry());
    }
    int r = result.size();
    return r;
}

//O(N)
int AirTrafficControl::cityDestiny(string p){
    vector<int> tmp = graphComplete.targetAirports(airportCodeToInt[p]);
    set<string> result;
    for(int n : tmp){
        result.insert(intToAirport[n].getCity());
    }
    int r = result.size();
    return r;
}

vector<Airports> AirTrafficControl::comeAirports(string v){
    vector<int> tmp = graphComplete.arriveAirports(airportCodeToInt[v]);
    vector<Airports> result;
    for(int n : tmp){
        result.push_back(intToAirport[n]);
    }
    return result;
}

// O(N)
int AirTrafficControl::countryComing(string p) {
    vector<int> tmp = graphComplete.arriveAirports(airportCodeToInt[p]);
    set<string> result;
    for (int n: tmp) {
        result.insert(intToAirport[n].getCountry());
    }
    int r = result.size();
    return r;
}

// O(N)
int AirTrafficControl::cityComing(string p){
    vector<int> tmp = graphComplete.arriveAirports(airportCodeToInt[p]);
    set<string> result;
    for(int n : tmp){
        result.insert(intToAirport[n].getCity());
    }
    int r = result.size();
    return r;
}

vector<Airlines> AirTrafficControl::comeFligth(string v) {
    vector<Airlines> result;
    unordered_set<string> num = graphComplete.arriveAirlines(airportCodeToInt[v]);
    for (string s: num) {
        result.push_back(mapAirlines[s]);
    }
    return result;
}

vector<Airlines> AirTrafficControl::leaveFligth(string v) {
    vector<Airlines> result;
    unordered_set<string> num = graphComplete.leaveAirlines(airportCodeToInt[v]);
    for (string s: num) {
        result.push_back(mapAirlines[s]);
    }
    return result;
}

// O(|V| + |E|)
vector<pair<Airports, int>> AirTrafficControl::DistanceAirports(string sr, int max){
    vector<pair<int,int>> dp;
    graphComplete.bfs_airports(airportCodeToInt[sr],max,dp);
    vector<pair<Airports, int>> result;
    for(auto p: dp){
        result.push_back({intToAirport[p.first],p.second});
    }
    return result;
}


vector<pair<int, int>> AirTrafficControl::airportsForDist(string sr, int max){
    vector<pair<Airports, int>> distC = DistanceAirports(sr,max);
    vector<pair<int, int>> result;
    list<Airports> airL;
    int dif = 0;
    int tmp = 1;
    for(auto p : distC){
        if(p.second != tmp){
            result.push_back({airL.size()-dif,tmp});
            dif = airL.size();
            tmp++;
        }
        airL.push_back(p.first);
    }
    result.push_back({airL.size()-dif,tmp});
    return result;
}

vector<pair<int, int>> AirTrafficControl::countryForDist(string sr, int max){
    vector<pair<Airports, int>> distC = DistanceAirports(sr,max);
    vector<pair<int, int>> result;
    unordered_set<string> country;
    int dif = 0;
    int tmp = 1;
    for(auto p : distC){
        if(p.second != tmp){
            result.push_back({country.size()-dif,tmp});
            tmp++;
            dif = country.size();
        }
        country.insert(p.first.getCountry());
    }
    result.push_back({country.size()-dif,tmp});
    return result;
}
vector<pair<int, int>> AirTrafficControl::cityForDist(string sr, int max){
    vector<pair<Airports, int>> distC = DistanceAirports(sr,max);
    vector<pair<int, int>> result;
    unordered_set<string> cities;
    int dif = 0;
    int tmp = 1;
    for(auto p : distC){
        if(p.second != tmp){
            result.push_back({cities.size()-dif,tmp});
            tmp++;
            dif = cities.size();
        }
        cities.insert(p.first.getCity());
    }
    result.push_back({cities.size()-dif,tmp});
    return result;
}

vector<pair<int, int>> cityForDist2(string sr, int max){

}