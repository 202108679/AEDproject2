
#include <cmath>
#include "Coordinates.h"

Coordinates::Coordinates(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

double Coordinates::distance(Coordinates c1){
    double dLat = (c1.getLatitude() - latitude) *
                  M_PI / 180.0;
    double dLon = (c1.longitude - longitude) *
                  M_PI / 180.0;

    // convert to radians
    double lat1 = (latitude) * M_PI / 180.0;
    double lat2 = (c1.getLatitude()) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

double Coordinates::getLatitude(){
    return latitude;
}

double Coordinates::getLongitude(){
    return longitude;
}