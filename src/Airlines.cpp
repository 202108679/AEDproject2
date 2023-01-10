//
// Created by Utilizador on 24/12/2022.
//
#include "Airlines.h"


using namespace std;

Airlines::Airlines(string code_, string name_, string callSign_ , string country_ ) :
        code(code_), name(name_), callSign(callSign_), country(country_){}

string Airlines::getCode() {
    return code;
}

string Airlines::getName() {
    return name;
}

string Airlines::getCallSign() {
    return callSign;
}

string Airlines::getCountry(){
    return country;
}