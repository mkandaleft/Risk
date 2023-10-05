/*
*   This is the Player header file. This file includes method
*   declarations for the object Player.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/

#pragma once

#include "Territory.h"
#include "Hand.h"
#include "OrderList.h"
#include "Order.h"
#include <vector>

using std::string;
using std::vector;


class Player {

    private:
        string name;
        vector<Territory*> territories;
        OrderList orderlist;
        Hand hand;

    public:
        Player(const string& playerName);
        void addTerritory(Territory& territory);
        const vector<Territory*>& toDefend() const;
        const vector<Territory*>& toAttack() const;
        void issueOrder(Order& order);
        string getName() const;
        Player(const Player& player);

};
