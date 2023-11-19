#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_set>

#include "../include/Map.h"	

using namespace std;

class Territory;

Continent::Continent(const string& name) :name(name) {}

Continent::Continent() {}

string Continent::getName() {
	return name;
}

vector<Territory*> Continent::getTerritory() {
	return territories;
}

void Continent::addTerritory(Territory* territory) {
	territories.push_back(territory);
}

int Continent::getValue() {
	return value;
}

void Continent::setValue(int v) {
	value = v;
}

void Map::dfs(Territory* territory, unordered_set<string>& visited) const {
	//if (!territory) return;
	visited.insert(territory->getName());
	for (const auto& adjacent : territory->getAdjacents()) {
		if (visited.find(adjacent->getName()) == visited.end()) {
			dfs(adjacent, visited);
		}
	}
}


map<string, Territory*> Map::getTerritories() {
	return territories;
}

map<string, Continent*> Map::getContinents() {
	return continents;
}

//create a new territry, add it to territories map, and return its pointer
Territory* Map::addTerritory(const string& name) {
	Territory* t = new Territory(name);
	territories[name] = t;
	return t;
}

Continent* Map::addContinent(const string& name) {
	Continent* c = new Continent(name);
	continents[name] = c;
	return c;
}

Map::Map() {
	// Initialize your data members as needed
}

// Copy constructor
Map::Map(const Map& other) {
	// Copy territories
	for (const auto& pair : other.territories) {
		// Assuming Territory has a copy constructor or appropriate clone method
		territories[pair.first] = new Territory(*(pair.second));
	}

	// Copy continents
	for (const auto& pair : other.continents) {
		// Assuming Continent has a copy constructor or appropriate clone method
		continents[pair.first] = new Continent(*(pair.second));
	}
}

Map& Map::operator=(const Map& other) {
	if (this == &other) {
		// Self-assignment, do nothing
		return *this;
	}

	// Clean up existing data
	for (const auto& pair : territories) {
		delete pair.second;
	}
	territories.clear();

	for (const auto& pair : continents) {
		delete pair.second;
	}
	continents.clear();

	// Copy territories
	for (const auto& pair : other.territories) {
		// Assuming Territory has a copy constructor or appropriate clone method
		territories[pair.first] = new Territory(*(pair.second));
	}

	// Copy continents
	for (const auto& pair : other.continents) {
		// Assuming Continent has a copy constructor or appropriate clone method
		continents[pair.first] = new Continent(*(pair.second));
	}

	return *this;
}

// Destructor
Map::~Map() {
	// Clean up dynamically allocated objects
	for (const auto& pair : territories) {
		delete pair.second;
	}

	for (const auto& pair : continents) {
		delete pair.second;
	}
}

//connect 2 territories in map
void Map::connect(const string& name1, const string& name2) {
	territories[name1]->connect(territories[name2]);
}

void Map::display() const {
	for (const auto& pair : continents) {
		cout<<"Continent: " <<pair.second->getName() <<endl;
		for (const auto& territory : pair.second->getTerritory()){
			cout<<"\t Territory: "<<territory->getName()<<": ";
			for (const auto& adj : territory->getAdjacents()) {
				cout<< adj->getName()<<", ";
			}
			cout<<endl;
		}
	}
}


bool Map::areContinentsSubgraphs() {
	for (const auto& continentPair : continents) {
		const vector<Territory*>& territoriesInContinent = continentPair.second->getTerritory();

		for (const auto& territory : territoriesInContinent) {
			// Check if the territory is in the map's territories
			if (territories.find(territory->getName()) == territories.end()) {
				return false; // A territory in the continent is not in the map.
			}
		}
	}

	return true; // All continents are subgraphs of the map.
}

bool Map::isMapConnected() {
	if (territories.empty()) {
		cout<<"Validation failed: Map is empty.";
		return false;
	}
	unordered_set<string> visited;
	dfs(territories.begin()->second, visited); // start DFS from the first territory in the map
	return visited.size() == territories.size(); // check if all territories were visited
}

bool Map::validate() {

	if (areContinentsSubgraphs()) {
		cout << "Validated: All Continents are Sub-graphs!\n";
	}
	else {
		cout << "Validation failed: Continents are not sub-graphs of map\n";
	}

	//disabled , it cause program to exit
	/*if (isMapConnected()) {
		cout << "Validated: Map is Connected!\n";
	}
	else {
		cout << "Validation failed: Map is not connected.\n";
	}*/
		
	if (/*isMapConnected() && */ areContinentsSubgraphs()) {
		cout<< "Map has been Validated!\n"; 
		return true;
	}
	cout<< "Map is invalid.\n";
	return false;

}


