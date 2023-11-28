/*
*   This is the Player header file. This file includes method
*   declarations for the object Player.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#pragma once

#include <vector>
#include "Territory.h"
#include "GameEngine.h"
#include "Orders.h"

using std::vector;
using std::string;

class Hand;

class Player {

    private:
        string name;
        vector<Territory*> territories;
        OrdersList* ordersList;
        Hand* hand;
        int reinforcementPool;
        vector<Player*> alliances;

    public:
        Player(const string& playerName);
        void addTerritory(Territory& territory);
        vector<Territory*>& toDefend() const;
        vector<Territory*>& toAttack() const;
        void issueOrder(GameEngine& engine);
        string getName() const;
        Player(const Player& player);
        vector<Territory*> getTerritories() const;
        int getReinforcement() const;
        void earnReinforcement(int added);
        void useReinforcement(int used);
        Hand* getHand();
        OrdersList* getOrdersList();
        bool operator==(const Player& other) const;
        vector<Player*> getAlliances();
        void addAlliance(Player* ally);
        
        void setName(const string& newName);

};
