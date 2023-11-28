
#include "../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/cards.h"
#include "../include/Orders.h"
#include "../include/Territory.h"
#include "MapDriver.cpp"
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

GameEngine::GameEngine(const string &state) : currentState(state){
    currentState = "start";
    gameDeck = new Deck(100);
    gameMap = new Map();
}

string GameEngine::getState() const{
    return currentState;
}

void GameEngine::setState(string state) {
    currentState = state;
}

void GameEngine::loadMap(string command) {
    if (currentState == "start" || currentState == "maploaded") {
        
        int spaceIdx = command.find(' ');

        //if spaceIdx is less, than the space either does not exist, or is the last character, so there was no file provided
        if(spaceIdx < command.length()-1){
            string map = command.substr(spaceIdx + 1);
            *gameMap = testLoadMap(map); //assignment operator called
            setState("maploaded");
            cout << "current state: " << getState() << endl;
        }
        else{
            cout<<"No map file provided"<<endl;
        }
        
    } else {
        cout << "Unable to load state, must be at state 'start' or 'map loaded' to load" << endl;
    }
}

void GameEngine::validateMap() {
    
    if (getState() == "maploaded") {
        if (gameMap->validate()) {
            setState("mapvalidated");
        }
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'map loaded' to load" << endl;
    }
}

void GameEngine::addPlayer(string command) {

    if (currentState == "mapvalidated" || currentState == "playersadded" ) {

        
        int spaceIdx = command.find(' ');

        //if spaceIdx is less, than the space either does not exist, or is the last character, so there was no name added
        if(spaceIdx < command.length()-1){
            //if command is properly called (e.g. "addplayer name"), "addplayer" will be disregarded
            string name = command.substr(spaceIdx+1);

            //stops players from having no name
                Player* gamer = new Player(name);
        
                participants.push_back(gamer);
                currentState = "playersadded";
                cout <<"current state: "<< currentState << endl;
        }
        else{
            cout<<"No name provided"<<endl;

        }
    } else {
        cout << "Unable to load state, must be at state 'map validated' or 'players added' to load" << endl;
    }
}

void GameEngine::addPlayerObject(Player* player) {
    participants.push_back(player);
}


void GameEngine::assignCountries(){
    if (currentState == "playersadded"){
        //used to randomize the distribution of territories
        random_device rd;
        mt19937 ran(rd());

        //takes the game Map(obj) and puts the territory map's(data structure) values into a vector
        vector<Territory*> gameTerritories;

        for (const auto& pair : gameMap->getTerritories()) {
            gameTerritories.push_back(pair.second);
        }

        //as a vector the elements can be shuffled randomly
        shuffle(gameTerritories.begin(),gameTerritories.end(),ran);

        for(int i =0;i<gameMap->getTerritories().size();i++){
            //loops through the participants, adding the back territory from the vector to a participant
            participants[i%participants.size()]->addTerritory(*gameTerritories.back());

            gameTerritories.back()->setOwner(participants[i % participants.size()]);
            //removes the last element to allow access to the next one
            gameTerritories.pop_back();
        }
        //currentState = "assign reinforcement";
        //cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'players added' to load" << endl;
    }
}

void GameEngine::gameStart(){
if (currentState == "playersadded"){
    //4a
    assignCountries();
    //4b
    random_device rd;
    mt19937 ran(rd());
                
    shuffle(participants.begin(),participants.end(),ran);

    for(Player* gamer: participants){
        //4c
        gamer->earnReinforcement(50);

        //4d

        gamer->getHand()->addCard(gameDeck->draw());
        gamer->getHand()->addCard(gameDeck->draw());
    }

        currentState = "assignreinforcement";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'assign reinforcement' or 'issue orders' to load" << endl;
    }
}

void GameEngine::issueOrder(){
    if (currentState == "assignreinforcement" || currentState == "issueorders"){
        currentState = "issueorders";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'assign reinforcement' or 'issue orders' to load" << endl;
    }
}

void GameEngine::endIssueOrders(){
    if (currentState == "issue orders") {
        currentState = "execute orders";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'issue orders' to load" << endl;
    }
}

void GameEngine::execOrder() {
    if (currentState == "execute orders"){
        currentState = "execute orders";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::endExecOrders() {
    if (currentState == "execute orders"){
        currentState = "assign reinforcement";
        cout <<"current state: "<< currentState << endl;
        for (const auto& player : participants)
        {
            player->getAlliances().clear();
        }
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::win() {
    if (currentState == "execute orders"){
        currentState = "win";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::end() {
    if (currentState == "win"){
        cout << "Game Over. Thanks for playing!" << endl;

        for(Card* card:gameDeck->getDeck()){
            delete card;
            card = nullptr;
        }
        delete gameDeck;
        gameDeck = nullptr;
        delete gameMap;
        gameMap = nullptr;
        for(Player* gamer:participants){
            for(Card* card:gamer->getHand()->getHand()){
                delete card;
                card = nullptr;
            }
            delete gamer->getHand();
            
            gamer = nullptr;
        }

        abort();
    } else {
        cout << "Unable to load state, must be at state 'win' to load" << endl;
    }
}

void GameEngine::play() {
    if (currentState == "win" ||currentState == "start"){

        currentState = "start";
        cout <<"current state: "<< currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'win' to load" << endl;
    }
}

void GameEngine::startUpPhase(){

    string command ="";

    bool startingUp = true;

    cout << "Welcome! Please enter a command to begin playing!" << endl;

    while(startingUp || (participants.size() < 2)){
        command = processor.getCommand();
        if (command.find("loadmap",0)==0){
            cout<<"Loading Map"<<endl;
            this->loadMap(command);
        } else if (command == "validatemap") {
            cout<<"Validating Map"<<endl;
            this->validateMap();
        } else if (command.find("addplayer",0)==0) {
            cout<<"Adding Player"<<endl;
            if(participants.size() < 6){
                    this->addPlayer(command);
            }else{
                cout<<"Maximum number of players reached"<<endl;
            }
        } else if (command == "gamestart") {
            if(participants.size()>=2){
                cout<<"Starting Game"<<endl;
                gameStart();

                //4e
                startingUp = false;
                
            }else{
                cout<<"Not enough players have been added"<<endl;
            }
        }
        else{
            cout<<"Unknown command"<<endl;
        }
    }
}

/*static Player* GameEngine::getNeutralPlayer()
{
    return neutralPlayer;
}
*/

// go through each phase of the main game loop
void GameEngine::mainGameLoop() {
    // null player pointer
    // assign to winner
    Player *winningPlayer = nullptr;
    while(winningPlayer = nullptr){
        reinforcementPhase();
        issueOrderPhase();
        executeOrdersPhase();

        // remove players than have no more territories
        for (const auto& playerPtr : participants) {
            int numOfTerritories = 0;
            for (const auto& thisTerritory : playerPtr->getTerritories()) {
                numOfTerritories++;
            }
            if (numOfTerritories <= 0) {
                cout << "Player " << playerPtr->getName() << " has no territories, they have lost!" << endl;
                delete playerPtr;
            }
        }
        if (participants.size() == 1) {
            cout << "Player " << participants[0]->getName() << " has won the game!!!" << endl;
            winningPlayer = participants[0];
        }
    }
}

void GameEngine::reinforcementPhase() {
    // get the map and continents from it
    map<string, Continent*> continents = gameMap->getContinents();

    // Give each player their units to play this turn
    for (const auto& playerPtr : participants) {
        // get the territories owned by this player
        vector<Territory*> playerTerritories = playerPtr->getTerritories();
        int earnedUnits = (playerTerritories.size()) / 3;
        // implement the determining of bonus units awarded upon having all territories in a continent
        // for each pair in map<string, Continent*>, we only want Continent here.
        for (const auto& pair : continents) {
            Continent* continentPtr = pair.second;
            vector<Territory*> contTerritories = continentPtr->getTerritory();
            // We start by saying the player has the continent. If it is found that there is a missing
            // territory, we will say that the player doesn't have it.
            bool hasContinent = true;
            for (const auto& territoryPtr : contTerritories) {
                // use find to try and find the territory in the continent. This is done for every territory.
                auto it = find(playerTerritories.begin(), playerTerritories.end(), territoryPtr);
                // if it is found continue the loop
                if (it != playerTerritories.end()) {
                    hasContinent = true;
                    continue;
                }
                else { // if not found, the continent isn't claimed, so break the loop
                    hasContinent = false;
                    break;
                }
            }
            if (hasContinent) earnedUnits += continentPtr->getValue();
        }
        // adjust if this player has less than 3 units
        if (earnedUnits < 3) earnedUnits = 3;
        playerPtr->earnReinforcement(earnedUnits);
        cout << playerPtr->getName() << " has earned " << earnedUnits << " as a bonus!" << endl;
    }
}

void GameEngine::issueOrderPhase() {
    // Have each player issue their orders
    for (const auto& playerPtr : participants) {
        playerPtr->issueOrder(*this);
    }
}

void GameEngine::executeOrdersPhase() {
    for (const auto& playerPtr : participants) {
        OrdersList* list = playerPtr->getOrdersList();
        const vector<Orders*>& orders = list->getOrders();

        for (const auto& orderPtr : orders) {
            execOrder();
        }
    }
}

Map* GameEngine::getMap(){
    return gameMap;
}
vector<Player*> GameEngine::getPlayers(){
    return participants;
}
Deck* GameEngine::getDeck(){
    return gameDeck;
}
