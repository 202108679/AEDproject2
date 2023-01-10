//
// Created by Utilizador on 03/01/2023.
//

#include <iostream>
#include "Path.h"


bool Path::operator<(const Path &p1) const{
    if(ord.size() < p1.ord.size()){
        return true;
    }
    else if (ord.size() == p1.ord.size()){
        if(per < p1.per){
            return true;
        }
    }
    return false;
}