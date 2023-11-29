/*
*   This is the Player header file. This file includes method
*   declarations for the object Player.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#pragma once

#include <vector>
#include "Orders.h"
#include "PlayerStrategies.h"

using std::string;
using std::vector;
class Hand;
class PlayerStrategy;

class Player {

    private:
        string name;
        vector<Territory*> territories;
        OrdersList* ordersList;
        Hand* hand;
        int reinformentPool;
        vector<Player*> alliances;
        PlayerStrategy* strat;

        bool beenAttacked;

    public:
        Player(const string& playerName);
        Player(const string& playerName, PlayerStrategy* plan);
        void addTerritory(Territory& territory);
        const vector<Territory*>& toDefend();
        const vector<Territory*>& toAttack();
        void issueOrder(Player* player, GameEngine* engine);
        string getName() const;
        Player(const Player& player);
        vector<Territory*> getTerritories();
        void earnReinforcement(int added);
        void useReinforcement(int used);
        int getPoolSize();
        Hand* getHand();
        vector<Player*> getAlliances();
        void addAlliance(Player* ally);
        
        void setName(const string& newName);

        void setBeenAttacked(bool status);
        bool getBeenAttacked();
        OrdersList* getOrderList();

        vector<Territory*> getSurroundings();
        void setStrategy(PlayerStrategy* plan);

};
