/*
*   This is the Player header file. This file includes method
*   declarations for the object Player.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#pragma once

#include "Territory.h"
#include "cards.h"
#include "Orders.h"
#include <vector>

using std::string;
using std::vector;


class GameEngine;

class Player {

    private:
        string name;
        vector<Territory*> territories;
        vector<Territory*> toBeAttacked;
        vector<Territory*> toBeDefended;
        OrdersList* ordersList;
        Hand* hand;
        int reinforcementPool;

    public:
        Player(const string& playerName);
        void addTerritory(Territory& territory);
        const vector<Territory*>& toDefend() const;
        const vector<Territory*>& toAttack() const;
        void issueOrder(GameEngine& engine);
        int getReinforcement() const;
        string getName() const;
        void setName(const string& newName);
        Player(const Player& player);
        vector<Territory*> getTerritories();
        void earnReinforcement(int added);
        void useReinforcement(int used);
        Hand* getHand();
        OrdersList* getOrdersList();
        bool operator==(const Player& other) const;
};