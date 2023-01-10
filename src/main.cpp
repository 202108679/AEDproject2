
#include "FileReader.h"
#include "graph.h"
#include <utility>
#include "Menu.h"

#define AIRLINES_FILE "../csv/airlines.csv"
#define AIRPORTS_FILE "../csv/airports.csv"
#define FLIGHTS_FILE "../csv/flights.csv"

using namespace std;

int main() {

    Menu menu(AIRLINES_FILE, AIRPORTS_FILE, FLIGHTS_FILE);
    menu.baseMenuLoop();


}
