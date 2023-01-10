//
// Created by Utilizador on 03/01/2023.
//

#ifndef PROJ2_AED_PATH_H
#define PROJ2_AED_PATH_H

#include <list>
#include <string>
#include <vector>
using namespace std;

class Path{
    public:
        list<int> ord;
        list<vector<string>> ports;
        double per;
        Path(list<int> ord,list<vector<string>> ports,double per) : ord(ord), ports(ports), per(per){};
        bool operator<(const Path &p1) const;
};
#endif //PROJ2_AED_PATH_H
