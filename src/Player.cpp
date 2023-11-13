/*
*   This is the player source code. This file includes method
*   definitions of the object Player as well as its attributes.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#include "../include/Player.h"
//#include "Orders.cpp"
using std::string;

Player::Player(const string& playerName) : name(playerName),reinforcementPool(0) {
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
            std::cin >> input;
            // in case the troops entered is too large
            while (input > reinforcementPool || input < 0){
                cout << "You do not have enough troops to deploy, or the input isn't valid." << endl;
                std::cin >> input;
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

    cout << "Now decide which territories you'd like to defend in priority: " << endl;
    for (const auto& thisTerritory : getTerritories()){
        vector<Territory*> adjacents = thisTerritory->getAdjacents();

        for (const auto& thisAdjacent : adjacents) {
            // make sure that you can't defend your opponent's territory
            if (thisAdjacent->getOwner() == this) {
                cout << "You have " << thisTerritory->getArmyUnits() << " troops on this territory." << endl;
                cout << "How many troops would you like to move to " << thisAdjacent->getName() << "?" << endl;
                int input = 0;
                std::cin >> input;
                while (input > thisTerritory->getArmyUnits() || input < 0){
                    cout << "You do not have enough troops to move, or the input isn't valid." << endl;
                    std::cin >> input;
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
                std::cin >> input;
                // check for valid input (Y/N)
                while (input.compare("y") != 0  && input.compare("Y") != 0  && input.compare("n") != 0  && input.compare("Y") != 0){
                    cout << "Incorrect answer. Try again." << endl;
                    cout << "Attack this adjacent in priority? (Y/N)" << endl;
                    std::cin >> input;
                }
                // choose troop number to attack
                if (input.compare("y") == 0 || input.compare("Y") == 0) {
                    cout << "You have " << getReinforcement() << " troops in your reinforcement pool." << endl;
                    cout << "How many troops would you like use to attack " << thisAdjacent->getName() << "?" << endl;
                    int input = 0;
                    std::cin >> input;
                    // if input is invalid
                    while (input > thisTerritory->getArmyUnits() || input < 0){
                        cout << "You do not have enough troops to attack, or the input is negative." << endl;
                        std::cin >> input;
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

    // allow player to play cards
    cout << "Decide which cards you would like to play: " << endl;
    bool playCards = true;
    // ask player to issue orders by playing cards
    while (playCards){
        cout<<"Enter the order command you would like to make (corresponding integer to the command):"<<endl;
        cout<<"1. Bomb"<<endl;
        cout<<"2. Blockade"<<endl;
        cout<<"3. Airlift"<<endl;
        cout<<"4. Negotiate"<<endl;
        cout<<"5. I have no more cards to play this turn."<<endl;
        int cardSelect = 0;
        std::cin >> cardSelect;
        // validate the selection from the player
        while (cardSelect < 1 || cardSelect > 5){
            cout<<"Invalid order command. Please enter a valid command."<<endl;
            std::cin >> cardSelect;
        }
        vector<Player*> players = engine.getPlayers();
        bool playOrder = false;
        Orders orderToPlay = nullptr;
        string orderName = "";
        switch(cardSelect){
            // Play a bomb card. Prompt player to choose the adjacent territory to bomb
            case 1:
                cout<<"You've chosen to play a Bomb card."<<endl;
                for (const auto& thisTerritory : getTerritories()) {
                    // player has to bomb a territory that is not theirs
                    for (const auto& thisAdjacent : thisTerritory->getAdjacents()){
                        // prompt player if they want to bomb the adjacent territory if it is not one of theirs
                        if (thisAdjacent->getOwner() != this) {
                            cout<<"Bomb Territory " << thisAdjacent->getName() << "? (Y/N)"<<endl;
                            string yesOrNo;
                            std::cin >> yesOrNo;
                            while (yesOrNo.compare("y") != 0  && yesOrNo.compare("Y") != 0  && yesOrNo.compare("n") != 0  && yesOrNo.compare("Y") != 0){
                                cout<<"Incorrect answer. Try again."<<endl;
                                std::cin >> yesOrNo;
                            } 
                            if (yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0) {
                                playOrder = true;
                                orderToPlay = Bomb(1);
                                orderName = "Bomb";
                            }
                        }
                    }
                }
                break;
            case 2:
                // Play a blockade card. Prompt player for which territory they want to blockade on.
                cout<<"You've chosen to play a Blockade card."<<endl;
                for (const auto& thisTerritory : getTerritories()) {
                    cout<<"Blockade Territory " << thisTerritory->getName() << "? (Y/N)"<<endl;
                    string yesOrNo;
                    std::cin >> yesOrNo;
                    while (yesOrNo.compare("y") != 0  && yesOrNo.compare("Y") != 0  && yesOrNo.compare("n") != 0  && yesOrNo.compare("Y") != 0){
                        cout<<"Incorrect answer. Try again."<<endl;
                        std::cin >> yesOrNo;
                    } 
                    if (yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0) {
                        playOrder = true;
                        orderToPlay = Blockade(1);
                        orderName = "Blockade";
                    }
                }
                break;
            case 3:
                // Play an airlift card. Prompt player to enter where to airlift from, the amount of troops to airlift, and where to airlift to.
                cout<<"You've chosen to play an Airlift card."<<endl;
                // find the territory to airlift from
                for (const auto& thisTerritory : getTerritories()) {
                    cout<<"Airlift from Territory " << thisTerritory->getName() << "? (Y/N)"<<endl;
                    string yesOrNo;
                    std::cin >> yesOrNo;
                    while (yesOrNo.compare("y") != 0  && yesOrNo.compare("Y") != 0  && yesOrNo.compare("n") != 0  && yesOrNo.compare("Y") != 0){
                        cout<<"Incorrect answer. Try again."<<endl;
                        std::cin >> yesOrNo;
                    } 
                    // if this is the right territory, proceed, and pick the amount of units to airlift
                    if (yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0) {
                        int unitsToAirlift = 0;
                        cout << "Enter the amount of units to move via airlift to another territory." << endl;
                        std::cin >> unitsToAirlift;
                        while (unitsToAirlift > thisTerritory->getArmyUnits() || unitsToAirlift <= 0){
                            cout<<"Invalid amount of units entered. Either the territory doesn't have enough units or the amount you entered is not a positive integer."<<endl;
                            std::cin >> yesOrNo;
                        }
                        // pick the territory to airlift to
                        for (const auto& airLiftTo : getTerritories()) {
                            cout<<"Airlift to Territory " << thisTerritory->getName() << "? (Y/N)"<<endl;
                            string yesOrNo;
                            std::cin >> yesOrNo;
                            while (yesOrNo.compare("y") != 0  && yesOrNo.compare("Y") != 0  && yesOrNo.compare("n") != 0  && yesOrNo.compare("Y") != 0){
                                cout<<"Incorrect answer. Try again."<<endl;
                                std::cin >> yesOrNo;
                            }
                            // once player has confirmed to airlift to a territory from a territory
                            if (yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0){
                                playOrder = true;
                                orderToPlay = Airlift(1);
                                orderName = "Airlift";
                            }
                        }
                    }
                }
                break;
            case 4:
                // Play a negotiate card. Prompt the player to choose another player to target for negotiation.
                cout<<"You've chosen to play a Negotiate card."<<endl;
                // pick a player to target
                for (const auto& targetPlayer : players) {
                    if (targetPlayer != this) {
                        cout<<"Negotiate player " << targetPlayer->getName() << "? (Y/N)"<<endl;
                        string yesOrNo;
                        std::cin >> yesOrNo;
                        while (yesOrNo.compare("y") != 0  && yesOrNo.compare("Y") != 0  && yesOrNo.compare("n") != 0  && yesOrNo.compare("Y") != 0){
                            cout<<"Incorrect answer. Try again."<<endl;
                            std::cin >> yesOrNo;
                        }
                        // once player has confirmed to airlift to a territory from a territory
                        if (yesOrNo.compare("y") == 0 || yesOrNo.compare("Y") == 0){
                            playOrder = true;
                            orderToPlay = Negotiate(1);
                            orderName = "Negotiate";
                        }
                    }
                }
                break;
            case 5:
                cout << getName() << " has finished issuing orders." << endl;
                playCards = false;
                break;
            }
        // If an order card was declared, the hand must be checked to see if the player has the corresponding card.
        if (playOrder){
            // check for valid card in hand
            bool foundCard = false;
            for (int i = 0; i < hand->getSize(); i++){
                Card* currentCard = hand->getCard(i);
                Orders type = currentCard->getType();
                Deck* deck = engine.getDeck();
                if (type.getName().compare(orderName) == 0){
                    currentCard->play(*deck,*hand);
                    ordersList->addOrder(orderToPlay);
                    foundCard = true;
                    break;
                }
            }
            if (foundCard){
                cout << "You have successfully played your card." << endl;
            } else {
                cout << "The card you tried to play was not in your hand. The order was not issued." << endl;
            }
        }
        if (!playCards) {
            break;
        } 
    }
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

