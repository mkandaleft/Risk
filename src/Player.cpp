/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "../include/Player.h"
#include "../include/Orders.h"
#include "../include/Territory.h"
#include "../include/GameEngine.h"
#include "../include/GameEngine.h"
#include "../include/PlayerStrategies.h"

#include <algorithm>

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;
using std::vector;

Player::Player(const string& playerName) : name(playerName),reinforcementPool(0){
    hand = new Hand(10,this);
    beenAttacked = false;
    strat = new Neutral();
    ordersList = new OrdersList();
}

Player::Player(const string& playerName, PlayerStrategy* plan) : name(playerName),reinforcementPool(0){
    hand = new Hand();
    beenAttacked = false;
    strat = plan;
        ordersList = new OrdersList();
}

Player::~Player() {
    delete ordersList;
    ordersList = nullptr;

    delete hand;
    hand = nullptr;

    for (Territory* territory : territories) {
        delete territory;
    }
    territories.clear();
}

void Player::addTerritory(Territory& territory) {
    territories.push_back(&territory);
}

// Returns a list of territories to be defended
const vector<Territory*> Player::toDefend(){
    return strat->toDefend(this);
}

// Returns a list of territories to be attacked
const vector<Territory*> Player::toAttack(){
    return strat->toAttack(this);
}

// Creates an order object and adds it to the list of orders
void Player::issueOrder(Player* player, GameEngine* engine){
    strat->issueOrder(this,engine);
}

string Player::getName() const {
    return name;
}

int Player::getReinforcement() const {
    return reinforcementPool;
}

bool Player::operator==(const Player& other) const {
    return (getName() == other.getName());
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
    reinforcementPool+= add;
}

void Player::useReinforcement(int use){
    reinforcementPool-= use;
}

int Player::getPoolSize(){
    return reinforcementPool;
}

OrdersList* Player::getOrdersList(){
    return ordersList;
}

vector<Territory*> Player::getTerritories() const {
    return territories;
}

Hand* Player::getHand(){
    return hand;
}

vector<Player*> Player::getAlliances()
{
    return alliances;
}

void Player::addAlliance(Player* ally)
{
    alliances.push_back(ally);
}

//Gets all territories not owned by me, that are touching a territory owned by me
vector<Territory*> Player::getSurroundings(){
    
    vector<Territory*> surroundings;
    vector<Territory*> nextToMe;

    //check all owned territories
    for(Territory* ownedTerr:getTerritories()){

        //check all adjacent territories of owned territories
        nextToMe = ownedTerr->getAdjacents();
        for(Territory* adj:nextToMe){
            auto it = find(nextToMe.begin(), nextToMe.end(), adj);

            //if the adjacent territory was already added, or its owned by this player, don't add
            if(it != nextToMe.end() || adj->getOwner() == this){
                continue;
            }
            else{
                surroundings.push_back(adj);
            }
        }
    }

    //all enemy territories surrounding owned territories
    return surroundings;
}

void Player::setBeenAttacked(bool status){
    beenAttacked = status;
}

bool Player::getBeenAttacked(){
    return beenAttacked;
}

void Player::setStrategy(PlayerStrategy* plan){

    //reset so neutral player doesn't immediately become aggressive
    if(typeid(plan) == typeid(Neutral))
        beenAttacked = false;

    strat = plan;
}


