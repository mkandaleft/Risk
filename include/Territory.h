
#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;
class Continent;
class Player;


class Territory {

private:
	string name;
	vector<Territory*> adjacents;
	int x, y;
	Continent* continent;
	int armyUnits;
	Player* owner;

public:

	vector<string> adjacent; //holds names of adjacents. (temporary)
	explicit Territory();
	explicit Territory(const string& name);
	explicit Territory(const Territory& other);
	string getName() const;
	Continent* getContinent() const;
	vector<Territory*> getAdjacents() const;
	int getUnits();
	Player* getOwner();
	
	void connect(Territory* other);

	void setContinent(Continent* newContinent);

	void setCoordinates(int newx, int newy);
	void setUnits(int units);
	void setOwner(Player* ownerIn);

};