
#include "../include/Territory.h"

class Map;
class Continent;

Territory::Territory() {}
Territory::Territory(const string& name) : name(name) {}
string Territory::getName() const { return name; }
Continent* Territory::getContinent() const { return continent; }
vector<Territory*> Territory::getAdjacents() const { return adjacents; }

void Territory::connect(Territory* other) {
	adjacents.push_back(other);
	other->adjacents.push_back(this);
}

void Territory::setContinent(Continent* newContinent) {
	continent = newContinent;
}

void Territory::setCoordinates(int newx, int newy) {
	x = newx;
	y = newy;
}