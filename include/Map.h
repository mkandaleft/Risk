#pragma once

using namespace std;
class Continent {
private:
	string name;
	int value;
	vector<Territory*> territories;
public:
	explicit Continent(const string& name);
	explicit Continent();
	string getName();
	vector<Territory*> getTerritory();
	void addTerritory(Territory* territory);
	int getValue();
	void setValue(int v);

};


class Map {

private:
	map<string, Territory*> territories;
	map<string, Continent*> continents;	

public:
	
	// Default constructor
	Map();

	// Copy constructor
	Map(const Map& other);

	// Assignment operator
	Map& operator=(const Map& other);


	// Destructor
	~Map();

	
	void dfs(Territory* territory, unordered_set<string>& visited) const;

	map<string, Territory*> getTerritories() ;

	map<string, Continent*> getContinents() ;

	//create a new territry, add it to territories map, and return its pointer
	Territory* addTerritory(const string& name);

	Continent* addContinent(const string& name) ;

	//connect 2 territories in map
	void connect(const string& name1, const string& name2);

	void display() const ;


	bool areContinentsSubgraphs() ;

	bool isMapConnected() ;

	bool validate();



};