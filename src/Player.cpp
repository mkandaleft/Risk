/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "../include/Player.h"
#include "../include/Orders.h"
using std::string;

Player::Player(const string& playerName) : name(playerName),reinformentPool(0) {
    hand = new Hand();
}

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

void Player::setName(const string& newName) {
    name = newName;
}

void Player::earnReinforcement(int add){
    reinformentPool+= add;
}

void Player::useReinforcement(int use){
    reinformentPool-= use;
}

vector<Territory*> Player::getTerritories(){
    return territories;
}

Hand* Player::getHand(){
    return hand;
}

