
#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;
class Map;
class Continent;

class Territory {

private:
	string name;
	vector<Territory*> adjacents;
	int x, y;
	Continent* continent;

public:

	vector<string> adjacent; //holds names of adjacents. (temporary)
	explicit Territory();
	explicit Territory(const string& name);
	string getName() const;
	Continent* getContinent() const;
	vector<Territory*> getAdjacents() const;


	void connect(Territory* other);

	void setContinent(Continent* newContinent);

	void setCoordinates(int newx, int newy);

};