#pragma once

#include "Orders.h"
#include "GameEngine.h"
#include "Player.h"

class PlayerStrategy{
    private:

    public:
        virtual void issueOrder(Player* player,GameEngine* theGame) = 0;
        virtual vector<Territory*> toAttack(Player* player) = 0;
        virtual vector<Territory*> toDefend(Player* player) = 0;

};

/*
requires user interactions to make decisions, including deploy and advance orders, as well as
playing any card. 
*/
class Human : public PlayerStrategy{
    public: 
        void issueOrder(Player* player,GameEngine* theGame);
        vector<Territory*> toAttack(Player* player);
        vector<Territory*> toDefend(Player* player);
};

/*
computer player that focuses on attack (deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore; will use any card with an
aggressive purpose, as defined above). 
*/
class Aggressive : public PlayerStrategy{
    public:
        void issueOrder(Player* player,GameEngine* theGame);
        vector<Territory*> toAttack(Player* player);
        vector<Territory*> toDefend(Player* player);

};


/*
computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories; may use cards but will never use a card in a way
that purposefully will harm anyone). 
*/
class Benevolent: public PlayerStrategy{
    public:
        void issueOrder(Player* player,GameEngine* theGame);        
        vector<Territory*> toAttack(Player* player);
        vector<Territory*> toDefend(Player* player);
};

/*
computer player that never issues any order, nor uses any cards, though it may have or receive
cards. If a Neutral player is attacked, it becomes an Aggressive player. 
*/
class Neutral: public PlayerStrategy{
    public:
        void issueOrder(Player* player,GameEngine* theGame);
        vector<Territory*> toAttack(Player* player);
        vector<Territory*> toDefend(Player* player);
};


/*
computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards. 
*/
class Cheater: public PlayerStrategy{
public:
        void issueOrder(Player* player,GameEngine* theGame);
        vector<Territory*> toAttack(Player* player);
        vector<Territory*> toDefend(Player* player);
};