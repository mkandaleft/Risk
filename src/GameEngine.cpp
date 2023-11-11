
#include "../include/GameEngine.h"
#include "../include/AllHeaders.h"
#include "cards.cpp"
#include "MapDriver.cpp"
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

GameEngine::GameEngine(const string &state) : currentState(state){
    currentState = "start";
    gameDeck = new Deck(100);

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

            //check for invalid map names
            Map temp = testLoadMap(map);//temporary, just to load the map in

            

            gameMap = new Map(temp);//game map needs to be dynamically stored in order to exist outside of this function
            //currentstate is always maploaded even if it doesnt work

            //stops state change if a bad map file is used
            if(gameMap->isMapConnected() && gameMap->areContinentsSubgraphs()){
                currentState = "maploaded";
            }

        cout <<"current state: "<< currentState << endl;
        }
        else{
            cout<<"No map file provided"<<endl;
        }
        
    } else {
        cout << "Unable to load state, must be at state 'start' or 'map loaded' to load" << endl;
    }
}

void GameEngine::validateMap() {
    if (currentState == "maploaded") {
        gameMap->validate();

        currentState = "mapvalidated";
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
            participants[i%participants.size()]->addTerritory(*(new Territory(*gameTerritories.back())));

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

Map* GameEngine::getMap(){
    return gameMap;
}
vector<Player*> GameEngine::getPlayers(){
    return participants;
}
Deck* GameEngine::getDeck(){
    return gameDeck;
}
