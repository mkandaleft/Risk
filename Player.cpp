/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "Player.h"

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
const vector<Territory*>& Player::toAttack() const{
    return territories;
}

// Creates an order object and adds it to the list of orders
void Player::issueOrder(Order& order){
    orderlist.addOrder(order);
}

string Player::getName() const {
    return name;
}



