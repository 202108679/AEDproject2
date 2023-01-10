//
// Created by Utilizador on 03/01/2023.
//

#include <algorithm>
#include "Menu.h"


using namespace std;

Menu::Menu(string lines, string ports,string flights) {
    traffic = AirTrafficControl(lines, ports, flights);
}

void Menu::printBaseMenu() {
    cout << "Menu" << endl;
    cout << "0 - Sair" << endl;
    cout << "1 - Informacoes Voos" << endl;
    cout << "2 - Informacoes Aeroportos" << endl;
}

void Menu::printMenu1() {
    bool running = true;
    while(running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - De Aeroporto para Aeroporto" << endl;
        cout << "2 - De Aeroporto para Cidade" << endl;
        cout << "3 - De Cidade para Aeroporto" << endl;
        cout << "4 - De Cidade para Cidade" << endl;
        cout << "5 - De locadidade para Aeroporto" << endl;
        cout << "6 - De localidade para Cidade" << endl;

        cout << "Opcao pretendida: ";
        int opt1 = 0;
        cin >> opt1; cout << endl;

        switch(opt1) {
            case 0:
                running = false;
                break;
            case 1:
            {
                string source, dest;
                cout << "Aeroporto de Partida: " << endl;
                cin >> source;
                cout << "Aeroporto de Destino: " << endl;
                cin >> dest;

                try {
                    int s = traffic.getCodeToInt().at(source);
                    int d = traffic.getCodeToInt().at(dest);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                int s = traffic.getCodeToInt().at(source);
                int d = traffic.getCodeToInt().at(dest);

                vector<Path> paths;

                string p = " ";
                // string line = " ";
                //unordered_set<string> airlines = {};
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados" << endl;
                        break;
                    }
                    paths = traffic.fliPortPortRes(s,d,airlines);
                }
                else{
                    paths  = traffic.fliPortPort(s,d);
                }

                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                sort(paths.begin(),paths.end());
                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;
                break;
            }
            case 2:
            {
                string source, dest;
                cout << "Aeroporto de Partida: " << endl;
                cin >> source;
                cout << "Cidade de Destino (se tiver espaço use underscore): " << endl;
                cin >> dest;
                replace(dest.begin(), dest.end(), '_', ' ');;
                try {
                    int s = traffic.getCodeToInt().at(source);
                    list<Airports> d = traffic.getPortsByCity().at(dest);

                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                int s = traffic.getCodeToInt().at(source);
                list<Airports> d = traffic.getPortsByCity().at(dest);
                vector<Path> paths;
                string p = " ";
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados"<< endl;
                        break;
                    }
                    paths = traffic.fliPortCityRes(s,d,airlines);
                }
                else{
                    paths = traffic.fliPortCity(s, d);}
                sort(paths.begin(),paths.end());
                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;
                break;
            }
            case 3:
            {
                string source, dest;
                cout << "Cidade de Partida (se tiver espaço use underscore): " << endl;
                cin >> source;
                replace(source.begin(), source.end(), '_', ' ');
                cout << "Aeroporto de Destino: " << endl;
                cin >> dest;
                try {
                    list<Airports> s = traffic.getPortsByCity().at(source);
                    int d = traffic.getCodeToInt().at(dest);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                list<Airports> s = traffic.getPortsByCity().at(source);
                int d = traffic.getCodeToInt().at(dest);

                vector<Path> paths;
                string p = " ";
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados"<<endl;
                        break;
                    }
                    paths = traffic.fliCityPortRes(s,d,airlines);
                }
                else{
                    paths = traffic.fliCityPort(s, d);}

                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                sort(paths.begin(),paths.end());
                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;
                break;
            }
            case 4:
            {
                string source, dest;
                cout << "Cidade de Partida:"  << endl;
                cin >> source;
                replace(source.begin(), source.end(), '_', ' ');
                cout << "Cidade de Destino:"  << endl;
                cin >> dest;
                replace(dest.begin(), dest.end(), '_', ' ');
                try {
                    list<Airports> s = traffic.getPortsByCity().at(source);
                    list<Airports> d = traffic.getPortsByCity().at(dest);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                list<Airports> s = traffic.getPortsByCity().at(source);
                list<Airports> d = traffic.getPortsByCity().at(dest);

                vector<Path> paths;
                string p = " ";
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados" << endl;
                        break;
                    }
                    paths = traffic.fliCityCityRes(s,d,airlines);
                }
                else{
                    paths = traffic.fliCityCity(s, d);}

                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                sort(paths.begin(),paths.end());
                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;

                break;
            }
            case 5:
            {
                double latitude, longitude;
                string dest;
                cout << "Localidade de Partida: " << endl;
                cout << "Latitude (]-90, 90[): " << endl;
                cin >> latitude;
                if(latitude > -90 && latitude < 90){
                    cout << "Valor Invalido: " << endl;
                    break;
                }

                cout << "Longitude (]-180:180[): " << endl;
                cin >> longitude;
                if(latitude < -180 || latitude > 180){
                    cout << "Valor Invalido: " << endl;
                    break;
                }

                cout << "Aeroporto de Destino:" << endl;
                cin >> dest;
                try {
                    int d = traffic.getCodeToInt().at(dest);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                int d = traffic.getCodeToInt().at(dest);

                vector<Path> paths;

                string p = " ";
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados";
                        break;
                    }
                    paths = traffic.fliLocPortRes(Coordinates(latitude,longitude), d, airlines);
                }
                else{
                    paths = traffic.fliLocPort(Coordinates(latitude,longitude), d);}
                sort(paths.begin(),paths.end());
                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                cout << endl;
                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;
                break;

            }
            case 6:
            {
                double latitude, longitude;
                string dest;
                cout << "Localidade de Partida: " << endl;
                cout << "Latitude (]-90, 90[): " << endl;
                cin >> latitude;
                cout<< latitude;
                if(latitude < -90.0 || latitude > 90.0){
                    cout << "Valor Invalido: " << endl;
                    break;
                }

                cout << "Longitude (]-180:180[): " << endl;
                cin >> longitude;
                if(longitude < -180.0 || longitude > 180.0){
                    cout << "Valor Invalido: " << endl;
                    break;
                }

                cout << "Cidade de Destino:" << endl;
                cin >> dest;
                replace(dest.begin(), dest.end(), '_', ' ');
                try {
                    list<Airports> d = traffic.getPortsByCity().at(dest);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Argumentos invalidos" <<'\n';
                    break;
                }
                list<Airports> d = traffic.getPortsByCity().at(dest);
                vector<Path> paths;

                string p = " ";
                cout << "Companhias aereas especificas? (n/y)" << endl;
                cin >> p;
                if(p == "y"){
                    unordered_set<string> airlines = defAirlines();
                    if(airlines.size()<1){
                        cout << "Falta de dados";
                        break;
                    }
                    paths = traffic.fliLocCityRes(Coordinates(latitude,longitude), d, airlines);
                }
                else{
                    paths = traffic.fliLocCity(Coordinates(latitude,longitude), d);}

                sort(paths.begin(),paths.end());
                cout << "Numero de Caminhos Minimos: " << paths.size() << endl;
                cout << endl;

                for(auto p : paths ){
                    printPath(p);
                    cout << endl;
                }
                cout << endl;
                break;
            }

            default:
            {
                cout << "Numero de opcao invalido." << endl;
                break;
            }
        }
    }
}


void Menu::printMenu2() {
    bool running = true;
    while(running) {
        cout << "0 - Voltar" << endl;
        cout << "1 - Voos a partir do Aeroporto x" << endl;
        cout << "2 - Voos de destino o Aeroporto x" << endl;
        cout << "3 - Companhias que voam para o Aeroporto x" << endl;
        cout << "4 - Companhias que voam a partir do Aeroporto x" << endl;
        cout << "5 - Aeroportos a uma distancia de n ou menos voos" << endl;
        cout << "6 - Paises a uma distancia de n ou menos voos" << endl;
        cout << "7 - Cidades a uma distancia de n ou menos voos" << endl;

        cout << "Opção pretendida: ";
        int opt1 = 0;
        cin >> opt1; cout << endl;
        unordered_map<string ,int> m1 = traffic.getCodeToInt();
        unordered_map<int,Airports> m2 = traffic.getIntToPort();
        switch(opt1) {
            case 0:
                running = false;
                break;
            case 1:
            {
            string aeroporto;
            cout << "Aeroporto: ";
            cin >> aeroporto;
            try {
                int i = m1.at(aeroporto);
            }
            catch (const std::out_of_range& oor) {
            std::cerr << "Aeroporto invalido" <<'\n';
            break;
            }
            vector<Airports> aeroportes = traffic.leaveAirports(aeroporto);
            int cities = traffic.cityDestiny(aeroporto);
            int countries = traffic.countryDestiny(aeroporto);

            cout << "Do " << m2[m1[aeroporto]].getName() << " partem voos para " << aeroportes.size() << " aeroportos"<< endl;
            cout << "Em " << cities << " cidades e " << countries << " paises diferentes" << endl;
            cout << endl;
                break;
            }
            case 2:
            {
                string aeroporto;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Aeroporto invalido" <<'\n';
                    break;
                }
                vector<Airports> aeroportes = traffic.comeAirports(aeroporto);
                int cities = traffic.cityComing(aeroporto);
                int countries = traffic.countryComing(aeroporto);
                cout << "Chegam ao " << aeroporto << " voos  provenientes de " << aeroportes.size() << " aeroportos"<< endl;
                cout << "Em " << cities << " cidades e " << countries << " paises diferentes" << endl;
                cout << endl;


                break;
            }
            case 3:
            {
                string aeroporto;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Aeroporto invalido" <<'\n';
                    break;
                }
                vector<Airlines> airlines = traffic.comeFligth(aeroporto);
                cout << endl;
                cout << "Chegam em " << m2[m1[aeroporto]].getName() << " voos de " << airlines.size() << " companhias aereas " << endl;
                cout <<endl;
                for(auto a : airlines){
                    cout << a.getName() << endl;
                }
                cout << endl;
                break;
            }
            case 4:
            {
                string aeroporto;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range& oor) {
                    std::cerr << "Aeroporto invalido" <<'\n';
                    break;
                }
                vector<Airlines> airlines = traffic.leaveFligth(aeroporto);
                cout << endl;
                cout << "Partem de " << m2[m1[aeroporto]].getName() << " voos de " << airlines.size() << " companhias aereas " << endl;
                cout <<endl;
                for(auto a : airlines){
                    cout << a.getName() << endl;
                }
                cout << endl;
                break;
            }
            case 5: {
                string aeroporto;
                int max;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                cout << "Numero de voos: ";
                cin >> max;
                cout << endl;
                if(max<1){
                    cout<< "Numero impossivel"<< endl;
                    cout << endl;
                    break;
                }
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range &oor) {
                    std::cerr << "Aeroporto invalido" << '\n';
                    break;
                }
                cout << endl;
                vector<pair<int, int>> airInDist = traffic.airportsForDist(aeroporto,max);
                cout<< "Número de aeroportos alcançados pela primeira vez e numero de voos" << endl;
                for(auto p : airInDist){
                    cout<< p.first << " Aeroportos a " << p.second << " voos" << endl;
                }

                cout << endl;
                break;
            }
            case 6: {
                string aeroporto;
                int max;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                cout << "Numero de voos: ";
                cin >> max;
                cout << endl;
                if(max<1){
                    cout<< "Numero impossivel"<< endl;
                    cout << endl;
                    break;
                }
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range &oor) {
                    std::cerr << "Aeroporto invalido" << '\n';
                    break;
                }
                cout << endl;
                vector<pair<int, int>> airInDist = traffic.countryForDist(aeroporto,max);
                cout<< "Numero de paises alcançados pela primeira vez e numero de voos" << endl;
                for(auto p : airInDist){
                    cout<< p.first << " paises a " << p.second << " voos" << endl;
                }
                cout << endl;
                break;
            }
            case 7: {
                int max;
                string aeroporto;
                cout << "Aeroporto: ";
                cin >> aeroporto;
                cout << "Numero de voos: ";
                cin >> max;
                cout << endl;
                if(max<1){
                    cout<< "Numero impossivel"<< endl;
                    cout << endl;
                    break;
                }
                try {
                    int i = m1.at(aeroporto);
                }
                catch (const std::out_of_range &oor) {
                    std::cerr << "Aeroporto invalido" << '\n';
                    break;
                }
                cout << endl;
                vector<pair<int, int>> airInDist = traffic.cityForDist(aeroporto,max);
                cout<< "Numero de cidades alcançados pela primeira vez e numero de voos" << endl;
                for(auto p : airInDist){
                    cout<< p.first << " cidades a " << p.second << " voos" << endl;
                }
                cout << endl;

                break;
            }
            default:
            {
                cout << "Número de opção inválido." << endl;
                break;
            }
        }
    }
}


int Menu::baseMenuLoop() {
    bool running = true;
    while (running) {
        printBaseMenu();
        cout << "Opcao pretendida: ";
        int opt = 0;
        cin >> opt; cout << endl;
        switch(opt) {
            case 0:
                running = false;
                break;
            case 1:
                printMenu1();
                break;
            case 2:
                printMenu2();
                break;
            default:
                cout << "Numero de opcao invalido." << endl;
                break;
        }
    }
    return 0;
}

void Menu::printPath(const Path &p){
    unordered_map<int, Airports> nameAirport = traffic.getIntToPort();
    unordered_map<string,Airlines> nameAirline = traffic.getMapAirlines();
    vector<int> v;
    auto it1 = p.ord.begin();
    auto it2 = p.ports.begin();
    while(it1 != p.ord.end()){
        v.push_back(*it1);
        it1++;
    }
    cout << endl;
    cout << "Numero de escalas: " << (p.ports.size() - 1) << endl;
    cout << nameAirport[v[0]].getName();
    for(int i = 1; i< v.size(); i++){
        cout << " --> " << nameAirport[v[i]].getName();
    }
    cout << endl;

    for(int i = 1; i< v.size(); i++){
        cout << "Trajeto " << i << endl;
        cout << nameAirport[v[i-1]].getName() << " --> " << nameAirport[v[i]].getName() << endl;
        cout << "Possiveis Airlines:" << endl;
        for(string s : *it2){
            cout << nameAirline[s].getName() << endl;
        }
        cout << endl;
        it2++;
    }
    cout << "Total distancia percorrida em KM: " << p.per << endl;

}

unordered_set<string> Menu::defAirlines(){
    string line = " ";
    unordered_set<string> airlines = {};
    cout << "Companhias aereas (0 para terminar): " << endl;
    unordered_map<string,Airlines> m = traffic.getMapAirlines();
    while(true) {
        cin >> line;
        if (line == "0") { break; }
        if (m.find(line) != m.end()) {
            airlines.insert(line);
        } else {
            cout << "Companhia impossivel" << endl;

        }
    }
    return airlines;
}