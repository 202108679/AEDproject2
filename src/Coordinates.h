//
// Created by Utilizador on 25/12/2022.
//

#ifndef PROJ2_AED_COORDINATES_H
#define PROJ2_AED_COORDINATES_H

class Coordinates {
    public:
        Coordinates(): latitude(0.0), longitude(0.0){};
        Coordinates(double latitude, double longitude);
        double distance(Coordinates c1);
        double getLatitude();
        double getLongitude();
    private:
        double latitude;
        double longitude;
};


#endif //PROJ2_AED_COORDINATES_H
