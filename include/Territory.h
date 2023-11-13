
#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_set>
#include "Player.h"

using namespace std;
class Continent;
class Player;

class Territory {

private:
	string name;
	vector<Territory*> adjacents;
	int x, y, armyUnits;
	Player* owner;
	Continent* continent;

public:

	vector<string> adjacent; //holds names of adjacents. (temporary)
	explicit Territory();
	explicit Territory(const string& name);
	explicit Territory(const Territory& other);
	string getName() const;
	Player* getOwner() const;
	int getArmyUnits() const;
	Continent* getContinent() const;
	vector<Territory*> getAdjacents() const;


	void connect(Territory* other);

	void setContinent(Continent* newContinent);

	void setCoordinates(int newx, int newy);

	void setArmyUnits(int units);

	void setPlayer(Player* ownerIn);
};