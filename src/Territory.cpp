
#include "../include/Territory.h"

class Map;
class Continent;
class Player;

Territory::Territory() {}
Territory::Territory(const string& name) : name(name) {}

Territory::Territory(const Territory& other):name(other.name),adjacents(other.adjacents),x(other.x),y(other.y),continent(other.continent){}

string Territory::getName() const { return name; }
Continent* Territory::getContinent() const { return continent; }
vector<Territory*> Territory::getAdjacents() const { return adjacents; }
int Territory::getArmyUnits() const { return armyUnits; }
Player* Territory::getOwner() { return owner; }

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