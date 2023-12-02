
#include "../include/Territory.h"

class Map;
class Continent;

Territory::Territory() {}
Territory::Territory(const string& name) : name(name), armyUnits(0) {}

Territory::Territory(const Territory& other) : name(other.name), adjacents(other.adjacents), x(other.x), y(other.y), continent(other.continent), armyUnits(other.armyUnits) {}

string Territory::getName() const { return name; }
Continent* Territory::getContinent() const { return continent; }
vector<Territory*> Territory::getAdjacents() const { return adjacents; }
int Territory::getUnits() {
	return armyUnits;
}

Player* Territory::getOwner() {
	return owner;
}


void Territory::connect(Territory* other) {
	adjacents.push_back(other);
	other->adjacents.push_back(this);
}

void Territory::setUnits(int units) {
	this->armyUnits = units;
}

void Territory::addUnits(int units) {
	this->armyUnits += units;
}

void Territory::setContinent(Continent* newContinent) {
	continent = newContinent;
}

void Territory::setCoordinates(int newx, int newy) {
	x = newx;
	y = newy;
}

void Territory::setOwner(Player* ownerIn) {
	this->owner = ownerIn;
}