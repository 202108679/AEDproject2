//
// Created by Utilizador on 03/01/2023.
//

#ifndef PROJ2_AED_MENU_H
#define PROJ2_AED_MENU_H

#include <string>
#include "AirTrafficControl.h"


using namespace  std;

class Menu {
public:
    Menu(string lines, string ports, string flights);
    void printBaseMenu();
    void printMenu1();
    void printMenu2();
    int baseMenuLoop();
    void printPath(const Path &p);
    unordered_set<string> defAirlines();
private:
    AirTrafficControl traffic;

};


#endif //PROJ2_AED_MENU_H
