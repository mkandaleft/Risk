/*
*   This is the Player header file. This file includes method
*   declarations for the object Player.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#pragma once

#include <vector>
#include "../include/Orders.h"
#include "../include/PlayerStrategies.h"

using std::string;
using std::vector;
class Hand;


class Player {

    private:
        string name;
        vector<Territory*> territories;
        OrdersList* ordersList;
        Hand* hand;
        int reinformentPool;
        vector<Player*> alliances;
        PlayerStrategy* strat;


    public:
        Player(const string& playerName);
        void addTerritory(Territory& territory);
        const vector<Territory*>& toDefend() const;
        const vector<Territory*>& toAttack() const;
        void issueOrder(Orders& order);
        string getName() const;
        Player(const Player& player);
        vector<Territory*> getTerritories();
        void earnReinforcement(int added);
        void useReinforcement(int used);
        Hand* getHand();
        vector<Player*> getAlliances();
        void addAlliance(Player* ally);
        
        void setName(const string& newName);

        void setStrategy(PlayerStrategy* plan);

};
