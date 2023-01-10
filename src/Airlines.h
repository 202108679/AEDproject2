
#ifndef AED_AIRLINES_H
#define AED_AIRLINES_H


#include <list>
#include <string>

using namespace std;

class Airlines {
    public:
        Airlines():code(" "), name(" "), callSign(" "), country(" "){};
        Airlines(string  code_, string  name_, string  callSign_, string  country_);
        string getCode();
        string getName();
        string getCallSign();
        string getCountry();


    private:
        string code;
        string name;
        string callSign;
        string country;

};


#endif //AED_AIRLINES_H



