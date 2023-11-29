#include <vector>
#include <iostream>
#include <random>
#include <sstream>

#include "../include/PlayerStrategies.h"
#include "../include/cards.h"
#include "../include/Territory.h"
#include "../include/Orders.h"

using namespace std;

/*
requires user interactions to make decisions, including deploy and advance orders, as well as
playing any card. 
*/
void Human::issueOrder(Player* person, GameEngine* theGame){
     // Make the player decide which territories they want to attack/defend
    const vector<Territory*>& toAttackResult = person->toAttack();
    const vector<Territory*>& toDefendResult = person->toDefend();

    // create a duplicate of reinforcementPool and use it on the while loop
    int reinforcementRef = person->getPoolSize();

    // Add deploy orders while reinforcement pool isn't empty
    cout << "You will now choose which territories you'd like to Deploy troops to." << endl;
    while (reinforcementRef > 0) {
        for (const auto& thisDefendable : toDefendResult){
            // put number of units
            cout << "How many armies would you like to send to " << thisDefendable->getName() << "? (enter an integer)" << endl;
            int armiesToSend = 0;
            cin >> armiesToSend;
            Deploy newDeploy(armiesToSend, thisDefendable, person);
            Deploy* deployPtr = &newDeploy;
            person->getOrderList()->addOrder(deployPtr);
            reinforcementRef -= armiesToSend;
        }
    }
    // Issue Advance orders to defend
    for (const auto& thisDefendable : toDefendResult){
        cout << "How many armies would you like to send to " << thisDefendable->getName() << "? (enter an integer)" << endl;
        int armiesToSend = 0;
        cin >> armiesToSend;
        cout << "Enter the territory you'd like to send from: ";
        string sendFrom = "";
        cin >> sendFrom;
        for (const auto& thisTerritory : person->getTerritories()) {
            if (thisTerritory->getName() == sendFrom) {
                Advance newAdvance(armiesToSend, thisTerritory, thisDefendable, person);
                Advance* advancePtr = &newAdvance;
                person->getOrderList()->addOrder(advancePtr);
                break;
            }
        }
    }
    // Issue Advance orders to attack
    for (const auto& thisAttackable : toAttackResult){
        cout << "How many armies would you like to send to attack " << thisAttackable->getName() << "? (enter an integer)" << endl;
        int armiesToSend = 0;
        cin >> armiesToSend;
        cout << "Enter the territory you'd like the attack from: ";
        string attackFrom = "";
        cin >> attackFrom;
        for (const auto& thisTerritory : person->getTerritories()) {
            if (thisTerritory->getName() == attackFrom) {
                Advance newAdvance(armiesToSend, thisTerritory, thisAttackable, person);
                Advance* advancePtr = &newAdvance;
                person->getOrderList()->addOrder(advancePtr);
                break;
            }
        }
    }

    // allow player to play cards
    // if has cards to play, ask player, otherwise dont ask
    if (person->getHand()->getSize() != 0){
        cout << "Decide which card you would like to play." << endl;
        cout<<"Enter the order command you would like to make (corresponding integer to the command):"<<endl;
        cout<<"1. Bomb"<<endl;
        cout<<"2. Blockade"<<endl;
        cout<<"3. Airlift"<<endl;
        cout<<"4. Negotiate"<<endl;
        cout<<"5. I don't want to play a card."<<endl;
        int cardSelect = 0;
        std::cin >> cardSelect;
        // validate the selection from the player
        while (cardSelect < 1 || cardSelect > 5){
            cout<<"Invalid order command. Please enter a valid command."<<endl;
            std::cin >> cardSelect;
        }
        vector<Player*> players = theGame->getPlayers();
        switch(cardSelect){
            // Play a bomb card. Prompt player to choose the adjacent territory to bomb
            case 1: {
                cout<<"You've chosen to play a Bomb card."<<endl;
                cout<<"Enter an enemy territory adjacent to yours to bomb:";
                string bombTerritory = "";
                cin >> bombTerritory;
                bool found = false;
                for (const auto& targetPlayer : theGame->getPlayers()) {
                    for (const auto& targetTerritory : targetPlayer->getTerritories()) {
                        if (targetTerritory->getName() == bombTerritory) {
                            Bomb newBomb(targetTerritory, person);
                            Bomb* bombPtr = &newBomb;
                            person->getOrderList()->addOrder(bombPtr);
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
                break; } 
            case 2: {
                // Play a blockade card. Prompt player for which territory they want to blockade on.
                cout<<"You've chosen to play a Blockade card."<<endl;
                cout << "Here are the territories available: " << endl;
                for (const auto& thisTerritory : person->getTerritories()){
                    cout << thisTerritory->getName();
                }
                cout << endl;
                cout <<"Enter the territory you'd like to blockade: ";
                string blockadeThis = "";
                for (const auto& targetTerritory : person->getTerritories()) {
                    if (targetTerritory->getName() == blockadeThis){
                        Blockade newBlockade(targetTerritory, person);
                        Blockade* blockadePtr = &newBlockade;
                        person->getOrderList()->addOrder(blockadePtr);
                        break;
                    }
                }
                break; }
            case 3: {
                // Play an airlift card. Prompt player to enter where to airlift from, the amount of troops to airlift, and where to airlift to.
                cout<<"You've chosen to play an Airlift card."<<endl;
                // find the territory to airlift from
                cout << "Decide which territory to airlift to " << endl;
                cout << "Here are the territories available: " << endl;
                for (const auto& thisTerritory : person->getTerritories()){
                    cout << thisTerritory->getName();
                }
                cout << endl;
                cout << "Enter the territory you want to airlift from: ";
                string stringFrom = "";
                cin >> stringFrom;
                cout << endl;
                cout << "Enter the territory you want to airlift to: ";
                string stringTo = "";
                cin >> stringTo;
                cout << endl;
                cout << "Enter the amount of units to airlift: ";
                int unitsToAirlift = 0;
                cin >> unitsToAirlift;
                cout << endl;
                Territory* fromPtr;
                Territory* toPtr;
                for (const auto& targetTerritory : person->getTerritories()) {
                    if (targetTerritory->getName() == stringFrom) fromPtr = targetTerritory;
                    else if (targetTerritory->getName() == stringTo) toPtr = targetTerritory;
                }
                Airlift newAirlift(unitsToAirlift, fromPtr, toPtr, person);
                Airlift* airliftPtr = &newAirlift;
                person->getOrderList()->addOrder(airliftPtr);
                break; }
            case 4: {
                // Play a negotiate card. Prompt the player to choose another player to target for negotiation.
                cout<<"You've chosen to play a Negotiate card."<<endl;
                // pick a player to target
                cout<<"Enter the name of the player you'd like to Negotiate: ";
                string playerName = "";
                cin >> playerName;
                // search for corresponding player
                for (const auto& targetPlayer : players) {
                    if (typeid(targetPlayer) != typeid(this)) {
                        if (targetPlayer->getName() == playerName) {
                            Negotiate newNegotiate(targetPlayer, person);
                            Negotiate* negotiatePtr = &newNegotiate;
                            person->getOrderList()->addOrder(negotiatePtr);
                            break;
                        }
                    }
                }
                break; }
            case 5:
                cout << person->getName() << " has chosen to not play a card." << endl;
                break;
            }
    } else { cout << person->getName() << " has no cards to play." << endl; }
    cout << person->getName() << " has finished issuing orders." << endl;
}

vector<Territory*>& Human::toAttack(Player* person){
    vector<Territory*> attacking;

    vector<Territory*> enemies = person->getSurroundings();

    cout<< "These are your neighbouring territories."<<endl;
    for(Territory* bad:enemies){
        cout<<bad->getName()<<" ";
    }
    cout<<endl;

    // asking player what territories they want to attack
    cout << "Decide which neighbouring territories to attack in priority." << endl;
    // if destination is enemy territory, advance
    cout << "Enter as a comma seperated list (no spaces) the territories you want to attack: ";
    string stringAttacking = "";
    cin >> stringAttacking;
    istringstream ss(stringAttacking);
    // split by commas
    vector<string> elements;
    string element;
    while (getline(ss, element, ',')) {
        elements.push_back(element);
    }
    // check for matching name
    for (const auto& thisElement : elements){
        for (const auto& thisTerritory : person->getTerritories()){
            vector<Territory*> adjacents = thisTerritory->getAdjacents();
            for (const auto& thisAdjacent : adjacents) {
                if (thisAdjacent->getName() == thisElement) attacking.push_back(thisAdjacent);
            }
        }
    }
    return attacking;
}

vector<Territory*>& Human::toDefend(Player* person){
     vector<Territory*> defending;
    int armyCounter;
    // ask how many armies they want to deploy to
    // asking player what territories they want to defend
    cout << "Decide which neighbouring territories to defend in priority." << endl;
    cout << "Here are the territories you can defend: " << endl;
    for (const auto& thisTerritory : person->getTerritories()){
        cout << thisTerritory->getName() << " ";
    }
    cout << endl;
    cout << "Enter as a comma seperated list (no spaces) the territories you want to defend: ";
    string stringDefending = "";
    cin >> stringDefending;
    istringstream ss(stringDefending);
    // split by commas
    vector<string> elements;
    string element;
    while (getline(ss, element, ',')) {
        elements.push_back(element);
    }
    // check for matching name
    for (const auto& thisElement : elements){
        for (const auto& thisTerritory : person->getTerritories()){
            if (thisTerritory->getName() == thisElement) defending.push_back(thisTerritory);
        }
    }
    return defending;
}



/*
computer player that focuses on attack (deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore; will use any card with an
aggressive purpose, as defined above). 
*/
void Aggressive::issueOrder(Player* aggresor,GameEngine* theGame){

    //CARDS PHASE

    //check player hand for aggressive cards
    vector<Card*> myHand = aggresor->getHand()->getHand();

    for(Card* card:myHand){
        if(typeid(card->getType()) == typeid(Bomb)){
            card->play(*theGame->getDeck(),*aggresor->getHand());
        }
    }

    //DEFENSE PHASE

    //only one territory is being deployed on
    Territory* champion = aggresor->toDefend().back();

    int dropIn = aggresor->getPoolSize();

    //deploys all units to strongest territory
    Deploy dep(dropIn,champion,aggresor);
    dep.execute(theGame);

    //remove units from pool
    aggresor->useReinforcement(dropIn);


    //ATTACK PHASE

    vector<Territory*> attackThem = aggresor->toAttack();
    
    for(Territory* targets: attackThem){
        Advance attack(champion->getUnits(),champion,targets,aggresor);
        attack.execute(theGame);

        if(targets->getOwner() == aggresor){
            cout<< aggresor->getName() << "'s " << champion->getName() <<" has won against" << targets->getName()<<endl;
        }
        else{
            cout<< aggresor->getName() << "'s " << champion->getName() <<" has lost against" << targets->getName()<<endl;
            break;
        }
    }

}

vector<Territory*>& Aggressive::toAttack(Player* aggresor){
        vector<Territory*> attacking;
        vector<Territory*> aroundMe;

        Territory* strongest = (aggresor->toDefend()).back();

        //using the name instead of the pointer to avoid issues checking
        string oldStrongest = strongest->getName();

        bool keepFighting = true;
        int iterations = 0;

        while(keepFighting){
        //refresh the territories surrounding the strongest after each (presumingly) successful attack
            aroundMe = strongest->getAdjacents();

            for(Territory* targets:aroundMe){
                //if its an enemy territory
                if(targets->getOwner() != aggresor){
                    attacking.push_back(targets);

                    //assuming you win the fight you'd end up here
                    strongest = targets;
                }
            }

            //if the old strongest is the same as the current strongest, no enemy territories were found around it, stop fighting
            if(oldStrongest == strongest->getName()){
                keepFighting = false;
                //just to be sure that it leaves loop
                break;
            }

            
            oldStrongest = strongest->getName();
        }

        return attacking;

}

vector<Territory*>& Aggressive::toDefend(Player* aggresor){
    vector<Territory*> defending;

    Territory* strongest = nullptr;
    vector<Territory*> myLand = aggresor->getTerritories();

    int armyCount;
    int most = 0;

     //find territory with highest count
    for(Territory* eachTerr: myLand){
        armyCount = eachTerr->getUnits();

        if(armyCount > most){
            most = armyCount;
            strongest = eachTerr;
        }
    }


    defending.push_back(strongest);
    
    return defending;
}

/*
computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories; may use cards but will never use a card in a way
that purposefully will harm anyone). 
*/
void Benevolent::issueOrder(Player* peaceKeeper,GameEngine* theGame){

    //CARDS PHASE

    vector<Card*> myHand = peaceKeeper->getHand()->getHand();

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
            card->play(*theGame->getDeck(),*peaceKeeper->getHand());
            }
        }
    }

    //DEFENSE ORDERS

    vector<Territory*> defendUs = peaceKeeper->toDefend();
    vector<Territory*> deploymentDistribution;

    int units = peaceKeeper->getPoolSize();
    int index = 0;

    int baseAmount = units / defendUs.size();
    int leftOvers = units % defendUs.size();

    for(Territory* defend:defendUs){
        Deploy dep(baseAmount,defend,peaceKeeper);  
        dep.execute(theGame);
    }

    //incase there's an uneven distribution of units/territory
    for(int i = 0;i<leftOvers;i++){
        //modding i by the size is redundant, but leave it
        Deploy dep(1,defendUs.at(i%defendUs.size()),peaceKeeper);
        dep.execute(theGame);
    }

    //ATTACK ORDERS
    cout<<"No Attacking for me, thanks:)"<<endl;

}

vector<Territory*>& Benevolent::toAttack(Player* peaceKeeper){
        vector<Territory*> attacking;
        return attacking;
}

vector<Territory*>& Benevolent::toDefend(Player* peaceKeeper){
    vector<Card*> myHand = peaceKeeper->getHand()->getHand();
    vector<Territory*> myLand = peaceKeeper->getTerritories();

    vector<Territory*> weaklings;

    int least = 0;

    //check for weakest country
    for(Territory* eachTerr: myLand){
        if(eachTerr->getUnits() < least){
            least = eachTerr->getUnits();
        }
    }

    //All units that are equally the weakest are put together
    for(Territory* eachTerr:myLand){
        if(eachTerr->getUnits() <= least){
            weaklings.push_back(eachTerr);
        }
    }

    return weaklings;
}

/*
computer player that never issues any order, nor uses any cards, though it may have or receive
cards. If a Neutral player is attacked, it becomes an Aggressive player. 
*/
void Neutral::issueOrder(Player* relaxed,GameEngine* theGame){

    if(relaxed->getBeenAttacked())
        relaxed->setStrategy(new Aggressive());
}

vector<Territory*>& Neutral::toAttack(Player* passive){
        vector<Territory*> attacking;
        return attacking;

}

vector<Territory*>& Neutral::toDefend(Player* passive){
    vector<Territory*> defending;    
    return defending;
}

/*
computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards. 
*/
void Cheater::issueOrder(Player* hacker,GameEngine* theGame){

    //DEFENSE PHASE

    //ATTACK PHASE
    
    vector<Territory*> attackThem = hacker->toAttack();

    Territory* space;

    for(Territory* targets:attackThem){
        targets->setOwner(hacker);

        cout<< hacker->getName() << " now owns " << targets->getName()<<endl;

    }
   
}

vector<Territory*>& Cheater::toAttack(Player* hacker){

    //all enemy territories surrounding owned territories
    vector<Territory*> surroundings = hacker->getSurroundings();

    return surroundings;


}

vector<Territory*>& Cheater::toDefend(Player* hacker){
    vector<Territory*> defending;
    int armyCounter;
    
    return defending;
}
