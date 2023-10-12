/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "../include/Player.h"

using std::string;

Player::Player(const string& playerName) : name(playerName) {}

void Player::addTerritory(Territory& territory) {
    territories.push_back(&territory);
}

// Returns a list of territories to be defended
const vector<Territory*>& Player::toDefend() const{
    return territories;
}

// Returns a list of territories to be attacked
const std::vector<Territory*>& Player::toAttack() const{
    
    std::vector<Territory*>* adjacentTerritories = new std::vector<Territory*>();
    
    // Iterate through all owned territories
    for (const Territory* territory : territories) {
        
        const std::vector<Territory*> adjacents = territory->getAdjacents();
        adjacentTerritories->insert(adjacentTerritories->end(), adjacents.begin(), adjacents.end());
    }
    return *adjacentTerritories;
}

// Creates an order object and adds it to the list of orders
void Player::issueOrder(Orders& order){
    ordersList->addOrder(order);
}

string Player::getName() const {
    return name;
}

Player::Player(const Player& player) {
    name = player.name;
    territories = player.territories;
    ordersList = player.ordersList;
}


