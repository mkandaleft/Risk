#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <filesystem>

#include "../include/Map.h"
#include "../include/Territory.h"

Map* testLoadMap(string mapFileName) {

    cout << "Starting to read" << mapFileName << endl;

    bool printLogs = true; //toggle print loading detail on/off

    auto wd = std::filesystem::current_path();

    ifstream file(mapFileName); // This function produces warning!!
    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        exit;
    }

    map<string, string> map_info;

    Map* mymap = new Map();

    string line, section; //current line and current section

    while (getline(file, line)) {
        // Skip empty lines.
        if (line.empty()) continue;

        // Check for section headers.
        if (line[0] == '[') {
            section = line.substr(1, line.find(']') - 1);
            continue;
        }

        auto delimiter_pos = line.find('=');

        if (section == "Map") {
            auto key = line.substr(0, delimiter_pos);
            auto value = line.substr(delimiter_pos + 1);
            map_info[key] = value;
        }
        else if (section == "Continents") {
            auto name = line.substr(0, delimiter_pos);
            Continent c(name);
            auto value = line.substr(delimiter_pos + 1);
            c.setValue(stoi(value));
            //continents[name] = c;
            mymap->addContinent(name);

        }
        else if (section == "Territories") {

            istringstream iss(line);
            string adjacent;

            string name, x, y, continentName;
            getline(iss, name, ',');
            getline(iss, x, ',');
            getline(iss, y, ',');
            getline(iss, continentName, ',');

            if (name.empty() || continentName.empty()) {
                cerr << "Missing name or continent: " << line << endl;
                continue;
            }

            //Territory t(name);
            Territory* t = mymap->addTerritory(name);

            t->setCoordinates(stoi(x), stoi(y));
            Continent* continent = mymap->getContinents()[continentName];
            t->setContinent(continent);

            while (getline(iss, adjacent, ',')) {
                if (adjacent.empty()) {
                    cerr << "Error - empty adjacent territory " << line << endl;
                    continue; // Skip this adjacent territory
                }
                t->adjacent.push_back(adjacent);
            }

            //territories[name] = *t;
            //continents[continentName].addTerritory(t);
            mymap->getContinents()[continentName]->addTerritory(t);

        }
    }


    //create links to other territory node based on string vector (names of adjacents)
    for (pair<string, Territory*> territoryPair : mymap->getTerritories()) {
        Territory* territory = territoryPair.second; // Reference to the Territory
        auto territories = mymap->getTerritories();
        for (string adj : territory->adjacent) {
            auto it = territories.find(adj);
            if (it != territories.end()) {
                territory->connect(it->second);// it->second gives the Territory
            }
            else {
                cout << "no adjacents found" << endl;
            }
        }
    }

    if (printLogs) {
        //printMapInfo(map_info);
        //printMapInfo(continents);
        //printMapInfo(territories);
    }

    //mymap.display();

    return mymap;
}

void printMapInfo(map<string, string> map_info) {

    cout << "Map Data:\n";
    for (const auto& element : map_info) {
        cout << "Key: " << element.first << ", Value: " << element.second << '\n';
    }
}

//int main() {
//    Map myMap = testLoadMap("Map/Earth.map");
//    myMap.display();
//    myMap.validate();
//    
//    return 0;
//}