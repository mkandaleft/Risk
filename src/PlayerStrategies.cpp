#include <vector>
#include <iostream>
#include <random>

#include "../include/PlayerStrategies.h"
#include "../include/cards.h"
#include "../include/Orders.h"
#include "../include/Territory.h"

using namespace std;


/*
computer player that focuses on attack (deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore; will use any card with an
aggressive purpose, as defined above). 
*/
void Aggressive::execute(Player* aggresor){
    Territory* strongest = nullptr;
    vector<Territory*> myTerritories = aggresor->getTerritories();


    int armyCount = 0;
    int most = 0;
    bool keepFighting = true;
    int iterations = 0;


    //check player hand for aggressive cards
    vector<Card*> myHand = aggresor->getHand()->getHand();

    for(Card* card:myHand){
        if(typeid(card->getType()) == typeid(Bomb)){
            //TODO: card->play();
        }
    }

    //find territory with highest count


    for(Territory* eachTerr: myTerritories){
        armyCount = eachTerr->getUnits();

        if(armyCount > most){
            most = armyCount;
            strongest = eachTerr;
        }
    }

    //deploy on that territory
    int dropIn = aggresor->getPoolSize();
    Deploy dep(dropIn,strongest,aggresor);

    //TODO: dep.execute();

    aggresor->useReinforcement(dropIn);
    vector<Territory*> aroundMe;



    while(keepFighting){
        //refresh the territories surrounding the strongest after each attack
        aroundMe = strongest->getAdjacents();

        for(Territory* targets:aroundMe){
            
            //if its an enemy territory
            if(targets->getOwner() != aggresor){

                //attack while you still have troops
                while (strongest->getUnits() > 1)
                {

                    Advance attack(strongest->getUnits(),strongest,targets,aggresor);
                    /* TODO:
                    attack.execute();

                    if win
                        advance
                        strongest = targets
                        //once you've won, break out and check the surrounding territories of the country you just advanced to
                        break;
                    */
                
                    
                }
                break;
            }

            //all territories around the strongest are owned by the same player and shouldn't be attacked
            if(iterations++ >= aroundMe.size()-1){
                //TODO: advance to a different territory

                //nobody left to fight
                keepFighting = false;
            }
            
        }

        //lost all your troops trying to attack
        if(strongest->getUnits() <= 0){
            keepFighting = false;
        }
    }
}

/*
computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories; may use cards but will never use a card in a way
that purposefully will harm anyone). 
*/
void Benevolent::execute(Player* peaceKeeper){
    vector<Card*> myHand = peaceKeeper->getHand()->getHand();
    vector<Territory*> myLand = peaceKeeper->getTerritories();

    Territory* weakest = nullptr;
    int least = 0;


    random_device rd;
    mt19937 gen(rd());

    bernoulli_distribution distribution(0.5);

    bool playCard = distribution(gen);

    for(Card* card:myHand){
        //check that the card isn't harmful
        if(typeid(card->getType()) == typeid(Blockade) 
        || typeid(card->getType()) == typeid(Negotiate)
        || typeid(card->getType()) == typeid(Airlift)){

            //50% chance to play the card
            if (playCard) {
                //card->play();
            }
        }
    }

    //check for weakest owned territory
    for(Territory* eachTerr: myLand){
        if(eachTerr->getUnits() < least){
            least = eachTerr->getUnits();
            weakest = eachTerr;
        }
    }

    int dropIn = peaceKeeper->getPoolSize();
    Deploy dep(dropIn,weakest,peaceKeeper);

    //TODO: dep.execute();

    peaceKeeper->useReinforcement(dropIn);

}

/*
computer player that never issues any order, nor uses any cards, though it may have or receive
cards. If a Neutral player is attacked, it becomes an Aggressive player. 
*/
void Neutral::execute(Player* relaxed){

    //TODO: if attacked
    relaxed->setStrategy(new Aggressive());
    //else do nothing
}

/*
computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards. 
*/
void Cheater::execute(Player* hacker){

    //get all territories, adjacent to a territory owned by this player

    vector<Territory*> aroundMe = hacker->getSurroundings();

    for(Territory* conquer: aroundMe){
        conquer->setOwner(hacker);
    }

}