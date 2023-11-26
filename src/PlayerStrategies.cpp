#include "../include/PlayerStrategies.h"


/*
computer player that focuses on attack (deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore; will use any card with an
aggressive purpose, as defined above). 
*/
void Aggresive::execute(Player* aggresor){
    //check player hand for aggressive cards (i.e. )

}

/*
computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories; may use cards but will never use a card in a way
that purposefully will harm anyone). 
*/
void Benevolent::execute(Player* peaceKeeper){

}

/*
computer player that never issues any order, nor uses any cards, though it may have or receive
cards. If a Neutral player is attacked, it becomes an Aggressive player. 
*/
void Neutral::execute(Player* relaxed){

}

/*
computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards. 
*/
void Cheater::execute(Player* hacker){
    
}