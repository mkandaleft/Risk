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
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;
using std::vector;

Player::Player(const string& playerName) : name(playerName),reinforcementPool(0) {
    hand = new Hand();
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
vector<Territory*>& Player::toDefend() const{
    vector<Territory*> defending;
    int armyCounter;
    // ask how many armies they want to deploy to
    // asking player what territories they want to defend
    cout << "Decide which neighbouring territories to defend in priority." << endl;
    cout << "Here are the territories you can defend: " << endl;
    for (const auto& thisTerritory : getTerritories()){
        cout << thisTerritory->getName() << " ";
    }
    cout << endl;
    cout << "Enter as a comma seperated list (no spaces) the territories you want to defend: ";
    string stringDefending = "";
    cin >> stringDefending;
    istringstream ss(stringDefending);
    // split by commas
    vector<string> elements;
    string element;
    while (getline(ss, element, ',')) {
        elements.push_back(element);
    }
    // check for matching name
    for (const auto& thisElement : elements){
        for (const auto& thisTerritory : getTerritories()){
            if (thisTerritory->getName() == thisElement) defending.push_back(thisTerritory);
        }
    }
    return defending;
}

// Returns a list of territories to be attacked
vector<Territory*>& Player::toAttack() const{
    vector<Territory*> attacking;
    // asking player what territories they want to attack
    cout << "Decide which neighbouring territories to attack in priority." << endl;
    // if destination is enemy territory, advance
    cout << "Enter as a comma seperated list (no spaces) the territories you want to attack: ";
    string stringAttacking = "";
    cin >> stringAttacking;
    istringstream ss(stringAttacking);
    // split by commas
    vector<string> elements;
    string element;
    while (getline(ss, element, ',')) {
        elements.push_back(element);
    }
    // check for matching name
    for (const auto& thisElement : elements){
        for (const auto& thisTerritory : getTerritories()){
            vector<Territory*> adjacents = thisTerritory->getAdjacents();
            for (const auto& thisAdjacent : adjacents) {
                if (thisAdjacent->getName() == thisElement) attacking.push_back(thisAdjacent);
            }
        }
    }
    return attacking;
}

// Creates an order object and adds it to the list of orders
void Player::issueOrder(GameEngine& engine){
    // Make the player decide which territories they want to attack/defend
    const vector<Territory*>& toAttackResult = toAttack();
    const vector<Territory*>& toDefendResult = toDefend();

    // create a duplicate of reinforcementPool and use it on the while loop
    int reinforcementRef = reinforcementPool;

    // Add deploy orders while reinforcement pool isn't empty
    cout << "You will now choose which territories you'd like to Deploy troops to." << endl;
    while (reinforcementRef > 0) {
        for (const auto& thisDefendable : toDefendResult){
            // put number of units
            cout << "How many armies would you like to send to " << thisDefendable->getName() << "? (enter an integer)" << endl;
            int armiesToSend = 0;
            cin >> armiesToSend;
            Deploy newDeploy = Deploy(armiesToSend, thisDefendable, this);
            Deploy* deployPtr = &newDeploy;
            ordersList->addOrder(deployPtr);
            reinforcementRef -= armiesToSend;
        }
    }
    // Issue Advance orders to defend
    for (const auto& thisDefendable : toDefendResult){
        cout << "How many armies would you like to send to " << thisDefendable->getName() << "? (enter an integer)" << endl;
        int armiesToSend = 0;
        cin >> armiesToSend;
        cout << "Enter the territory you'd like to send from: ";
        string sendFrom = "";
        cin >> sendFrom;
        for (const auto& thisTerritory : getTerritories()) {
            if (thisTerritory->getName() == sendFrom) {
                Advance newAdvance = Advance(armiesToSend, thisTerritory, thisDefendable, this);
                Advance* advancePtr = &newAdvance;
                ordersList->addOrder(advancePtr);
                break;
            }
        }
    }
    // Issue Advance orders to attack
    for (const auto& thisAttackable : toAttackResult){
        cout << "How many armies would you like to send to attack " << thisAttackable->getName() << "? (enter an integer)" << endl;
        int armiesToSend = 0;
        cin >> armiesToSend;
        cout << "Enter the territory you'd like the attack from: ";
        string attackFrom = "";
        cin >> attackFrom;
        for (const auto& thisTerritory : getTerritories()) {
            if (thisTerritory->getName() == attackFrom) {
                Advance newAdvance = Advance(armiesToSend, thisTerritory, thisAttackable, this);
                Advance* advancePtr = &newAdvance;
                ordersList->addOrder(advancePtr);
                break;
            }
        }
    }

    // allow player to play cards
    // if has cards to play, ask player, otherwise dont ask
    if (getHand()->getSize() != 0){
        cout << "Decide which card you would like to play." << endl;
        cout<<"Enter the order command you would like to make (corresponding integer to the command):"<<endl;
        cout<<"1. Bomb"<<endl;
        cout<<"2. Blockade"<<endl;
        cout<<"3. Airlift"<<endl;
        cout<<"4. Negotiate"<<endl;
        cout<<"5. I don't want to play a card."<<endl;
        int cardSelect = 0;
        std::cin >> cardSelect;
        // validate the selection from the player
        while (cardSelect < 1 || cardSelect > 5){
            cout<<"Invalid order command. Please enter a valid command."<<endl;
            std::cin >> cardSelect;
        }
        vector<Player*> players = engine.getPlayers();
        switch(cardSelect){
            // Play a bomb card. Prompt player to choose the adjacent territory to bomb
            case 1: {
                cout<<"You've chosen to play a Bomb card."<<endl;
                cout<<"Enter an enemy territory adjacent to yours to bomb:";
                string bombTerritory = "";
                cin >> bombTerritory;
                bool found = false;
                for (const auto& targetPlayer : engine.getPlayers()) {
                    for (const auto& targetTerritory : targetPlayer->getTerritories()) {
                        if (targetTerritory->getName() == bombTerritory) {
                            Bomb newBomb = Bomb(targetTerritory, this);
                            Bomb* bombPtr = &newBomb;
                            ordersList->addOrder(bombPtr);
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
                break; } 
            case 2: {
                // Play a blockade card. Prompt player for which territory they want to blockade on.
                cout<<"You've chosen to play a Blockade card."<<endl;
                cout << "Here are the territories available: " << endl;
                for (const auto& thisTerritory : getTerritories()){
                    cout << thisTerritory->getName();
                }
                cout << endl;
                cout <<"Enter the territory you'd like to blockade: ";
                string blockadeThis = "";
                for (const auto& targetTerritory : getTerritories()) {
                    if (targetTerritory->getName() == blockadeThis){
                        Blockade newBlockade = Blockade(targetTerritory, this);
                        Blockade* blockadePtr = &newBlockade;
                        ordersList->addOrder(blockadePtr);
                        break;
                    }
                }
                break; }
            case 3: {
                // Play an airlift card. Prompt player to enter where to airlift from, the amount of troops to airlift, and where to airlift to.
                cout<<"You've chosen to play an Airlift card."<<endl;
                // find the territory to airlift from
                cout << "Decide which territory to airlift to " << endl;
                cout << "Here are the territories available: " << endl;
                for (const auto& thisTerritory : getTerritories()){
                    cout << thisTerritory->getName();
                }
                cout << endl;
                cout << "Enter the territory you want to airlift from: ";
                string stringFrom = "";
                cin >> stringFrom;
                cout << endl;
                cout << "Enter the territory you want to airlift to: ";
                string stringTo = "";
                cin >> stringTo;
                cout << endl;
                cout << "Enter the amount of units to airlift: ";
                int unitsToAirlift = 0;
                cin >> unitsToAirlift;
                cout << endl;
                Territory* fromPtr;
                Territory* toPtr;
                for (const auto& targetTerritory : getTerritories()) {
                    if (targetTerritory->getName() == stringFrom) fromPtr = targetTerritory;
                    else if (targetTerritory->getName() == stringTo) toPtr = targetTerritory;
                }
                Airlift newAirlift = Airlift(unitsToAirlift, fromPtr, toPtr, this);
                Airlift* airliftPtr = &newAirlift;
                ordersList->addOrder(airliftPtr);
                break; }
            case 4: {
                // Play a negotiate card. Prompt the player to choose another player to target for negotiation.
                cout<<"You've chosen to play a Negotiate card."<<endl;
                // pick a player to target
                cout<<"Enter the name of the player you'd like to Negotiate: ";
                string playerName = "";
                cin >> playerName;
                // search for corresponding player
                for (const auto& targetPlayer : players) {
                    if (targetPlayer != this) {
                        if (targetPlayer->getName() == playerName) {
                            Negotiate newNegotiate = Negotiate(targetPlayer, this);
                            Negotiate* negotiatePtr = &newNegotiate;
                            ordersList->addOrder(negotiatePtr);
                            break;
                        }
                    }
                }
                break; }
            case 5:
                cout << getName() << " has chosen to not play a card." << endl;
                break;
            }
    } else { cout << getName() << " has no cards to play." << endl; }
    cout << getName() << " has finished issuing orders." << endl;
}

OrdersList* Player::getOrdersList(){
    return ordersList;
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



