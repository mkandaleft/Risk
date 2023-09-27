#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

//forward declaration
class Map;
class Continent;

class Territory {

private:
	string name;
	vector<Territory*> adjacents;
	int x,y;
	Continent* continent;

public:

	vector<string> adjacent; //holds names of adjacents. (temporary)
	explicit Territory(){}
	explicit Territory(const string& name): name(name) {}
	string getName() const { return name; }
	Continent* getContinent() const { return continent; }
	vector<Territory*> getAdjacents() const { return adjacents; }


	void connect(Territory* other) {
		adjacents.push_back(other);
		other->adjacents.push_back(this);
	}

	void setContinent(Continent* newContinent) {
		continent = newContinent;
	}

	void setCoordinates(int newx, int newy) {
		x=newx;
		y=newy;
	}

};

class Continent {
private:
	string name;
	int value;
	vector<Territory*> territories;
public:
	explicit Continent(const string& name):name(name){}
	explicit Continent() {}
	string getName() {
		return name;
	}

	vector<Territory*> getTerritory() {
		return territories;
	}

	void addTerritory(Territory* territory) {
		territories.push_back(territory);
	}

	int getValue() {
		return value;
	}

	void setValue(int v) {
		value = v;
	}

};

class Map {

private:
	map<string,Territory*> territories;
	map<string, Continent*> continents;

	void dfs(Territory* territory, unordered_set<string>& visited) const {
		//if (!territory) return;
		visited.insert(territory->getName());
		for (const auto& adjacent : territory->getAdjacents()) {
			if (visited.find(adjacent->getName()) == visited.end()) {
				dfs(adjacent, visited);
			}
		}
	}

public:

	map<string, Territory*> getTerritories() {
		return territories;
	}

	map<string, Continent*> getContinents() {
		return continents;
	}

	//create a new territry, add it to territories map, and return its pointer
	Territory* addTerritory(const string& name) {
		Territory* t = new Territory(name);
		territories[name] = t;
		return t;
	}

	Continent* addContinent(const string& name) {
		Continent* c = new Continent(name);
		continents[name] = c;
		return c;
	}

	//connect 2 territories in map
	void connect(const string& name1, const string& name2) {
		territories[name1]->connect(territories[name2]);
	}

	void display() const {
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


	bool areContinentsSubgraphs() {
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

	bool isMapConnected() const {
		if (territories.empty()) {
			cout<<"Validation failed: Map is empty.";
			return false;
		}
		unordered_set<string> visited;
		dfs(territories.begin()->second, visited); // start DFS from the first territory in the map
		return visited.size() == territories.size(); // check if all territories were visited
	}

	bool validate() {

		if (areContinentsSubgraphs()) {
			cout << "Validated: All Continents are Sub-graphs!\n";
		}
		else {
			cout << "Validation failed: Continents are not sub-graphs of map\n";
		}

		if (isMapConnected()) {
			cout << "Validated: Map is Connected!\n";
		}
		else {
			cout << "Validation failed: Map is not connected.\n";
		}
		
		if (isMapConnected() && areContinentsSubgraphs()) {
			cout<< "Map has been Validated!\n"; 
			return true;
		}
		cout<< "Map is invalid.\n";
		return false;

	}



};