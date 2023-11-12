/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "../include/Player.h"
#include "Orders.cpp"
#include "GameEngine.cpp"
using std::string;

Player::Player(const string& playerName) : name(playerName),reinforcementPool(0) {
    hand = new Hand();
}

void Player::addTerritory(Territory& territory) {
    territories.push_back(&territory);
}

// Returns a list of territories to be defended
const vector<Territory*>& Player::toDefend() const{
    return toBeDefended;
}

// Returns a list of territories to be attacked
const vector<Territory*>& Player::toAttack() const{
    return toBeAttacked;
}

// Creates an order object and adds it to the list of orders
void Player::issueOrder(GameEngine& engine){
    // Deploys reinforcement until the pool is empty
    cout << "First, add your reinforcement pool to your owned territories." << endl;
    while(reinforcementPool > 0){
        // for each territory the player owns ask them if they want to deploy.
        for (const auto& thisTerritory : getTerritories()){
            // show amount of troops in reinforcement, ask how many troops to add
            cout << "You have " << getReinforcement() << " troops in your reinforcement pool." << endl;
            cout << "How many troops would you like to deploy to " << thisTerritory->getName() << "?" << endl;
            int input = 0;
            cin >> input;
            // in case the troops entered is too large
            while (input > reinforcementPool || input < 0){
                cout << "You do not have enough troops to deploy, or the input isn't valid." << endl;
                cin >> input;
            }
            // remove from reinforcement pool, add to orderslist
            ordersList->addOrder(Deploy(input));
            reinforcementPool = reinforcementPool - input;
            cout << "You've sent " << input << " troops to " << thisTerritory->getName() << "." << endl;
            if (input > 0) {
                toBeDefended.push_back(thisTerritory);
            }
        }
    }
    cout << "Troops deployed!" << endl;


    for (const auto& thisTerritory : getTerritories()){
        vector<Territory*> adjacents = thisTerritory->getAdjacents();
        for (const auto& thisAdjacent : adjacents) {
            // make sure that you can't defend your opponent's territory
            if (thisAdjacent->getOwner() == this) {
                cout << "You have " << thisTerritory->getArmyUnits() << " troops on this territory." << endl;
                cout << "How many troops would you like to move to " << thisAdjacent->getName() << "?" << endl;
                int input = 0;
                cin >> input;
                while (input > thisTerritory->getArmyUnits() || input < 0){
                    cout << "You do not have enough troops to move, or the input isn't valid." << endl;
                    cin >> input;
                }
                // add move to orderlist
                if (input > 0) {
                    toBeDefended.push_back(thisAdjacent);
                    ordersList->addOrder(Advance(input));
                    cout << "You've sent " << input << " troops to defend " << thisAdjacent->getName() << "." << endl;
                } else {
                    cout << "Did not send troops to defend. No troops were declared." << endl;
                }
            }
        }
    }

    cout << "Decide which neighbouring territories to attack in priority: " << endl;
    for (const auto& thisTerritory : getTerritories()){
        //
        vector<Territory*> adjacents = thisTerritory->getAdjacents();
        for (const auto& thisAdjacent : adjacents) {
            // make sure that you can't attack your own territory
            if (thisAdjacent->getOwner() != this) {
                // Prompt to attack territories in priority
                cout << thisAdjacent->getName() << endl;
                cout << "Attack this adjacent in priority? (Y/N)" << endl;
                string input = "";
                cin >> input;
                // check for valid input (Y/N)
                while (input.compare("y") != 0  && input.compare("Y") != 0  && input.compare("n") != 0  && input.compare("Y") != 0){
                    cout << "Incorrect answer. Try again." << endl;
                    cout << "Attack this adjacent in priority? (Y/N)" << endl;
                    cin >> input;
                }
                // choose troop number to attack
                if (input.compare("y") == 0 || input.compare("Y") == 0) {
                    cout << "You have " << getReinforcement() << " troops in your reinforcement pool." << endl;
                    cout << "How many troops would you like use to attack " << thisAdjacent->getName() << "?" << endl;
                    int input = 0;
                    cin >> input;
                    // if input is invalid
                    while (input > thisTerritory->getArmyUnits() || input < 0){
                        cout << "You do not have enough troops to attack, or the input is negative." << endl;
                        cin >> input;
                    }
                    if (input > 0) {
                        toBeAttacked.push_back(thisAdjacent);
                        ordersList->addOrder(Advance(input));
                        cout << "You've sent " << input << " troops to attack " << thisAdjacent->getName() << "." << endl;
                    } else {
                        cout << "Did not send troops to attack. No troops were declared." << endl;
                    }
                }
            }   
        }
    }
}

                    // TODO not specified in this assignment, but might implement other methods of order later.

                    // choose method of attack (I don't know if these are all necessarily attack methods)
                    /*cout<<"Enter the order command you would like to make (corresponding integer to the command):"<<endl;
                    cout<<"1. Bomb"<<endl;
                    cout<<"2. Blockade"<<endl;
                    cout<<"3. Airlift"<<endl;
                    cout<<"4. Negotiate"<<endl;
                    int attackSelect = 0;
                    cin >> attackSelect;
                    while (attackSelect < 1 || attackSelect > 4){
                        cout<<"Invalid order command. Please enter a valid command."<<endl;
                        cin >> attackSelect;
                        // check for valid card in hand
                    for (int i = 0; i < hand->getSize(); i++){
                        Card* currentCard = hand->getCard(i);
                        Orders type = currentCard->getType();
                        Deck* deck = engine.getDeck();

                        if (type.getName().compare("Advance") == 0){
                            currentCard->play(*deck,*hand);
                            ordersList->addOrder(Advance(input));
                            added = true;
                            break;
                        }
                    }
                    }*/
                    // add order according to the attack selected
                    // TODO add card effects

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

void Player::earnReinforcement(int add){
    reinforcementPool+= add;
}

void Player::useReinforcement(int use){
    reinforcementPool-= use;
}

vector<Territory*> Player::getTerritories(){
    return territories;
}

Hand* Player::getHand(){
    return hand;
}

