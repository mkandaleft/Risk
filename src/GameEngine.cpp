
#include "../include/GameEngine.h"
#include "../include/AllHeaders.h"
#include "MapDriver.cpp"
#include <cstdlib>

using namespace std;

GameEngine::GameEngine(const string &state) : currentState(state){//},participants(),cards() {
    currentState = "start";    
}

string GameEngine::getState() const{
    return currentState;
}

void GameEngine::setState(string state) {
    currentState = state;
}

void GameEngine::loadMap(string map) {
    if (currentState == "start" || currentState == "map loaded") {
        
        //command is called as: loadmap mapname.map
        int fileStart = map.find(' ');
        //uses space to just get the second half containing file name
        if(fileStart < (map.length())){
            string fileName = map.substr(fileStart+1);
            Map temp = testLoadMap(fileName);//temporary, just to load the map in
            gameMap = &temp;
            currentState = "map loaded";
        }

        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'start' or 'map loaded' to load" << endl;
    }
}

void GameEngine::validateMap() {
    if (currentState == "map loaded") {
        cout<<"we in";
        gameMap->validate();

        currentState = "map validated";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'map loaded' to load" << endl;
    }
}

void GameEngine::addPlayer() {
    string name = "";
    if (currentState == "map validated" || currentState == "players added" ) {
        cout<<"What's your name, player? ";
        cin>>name;
        Player* gamer = new Player(name);
        participants.push_back(gamer);
        currentState = "player added";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'map validated' or 'players added' to load" << endl;
    }
}

void GameEngine::assignCountries(){
    if (currentState == "players added"){
        currentState = "assign reinforcement";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'players added' to load" << endl;
    }
}

void GameEngine::issueOrder(){
    if (currentState == "assign reinforcement" || currentState == "issue orders"){
        currentState = "issue orders";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'assign reinforcement' or 'issue orders' to load" << endl;
    }
}

void GameEngine::endIssueOrders(){
    if (currentState == "issue orders") {
        currentState = "execute orders";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'issue orders' to load" << endl;
    }
}

void GameEngine::execOrder() {
    if (currentState == "execute orders"){
        currentState = "execute orders";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::endExecOrders() {
    if (currentState == "execute orders"){
        currentState = "assign reinforcement";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::win() {
    if (currentState == "execute orders"){
        currentState = "win";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'execute orders' to load" << endl;
    }
}

void GameEngine::end() {
    if (currentState == "win"){
        cout << "Game Over. Thanks for playing!" << endl;
        abort();
    } else {
        cout << "Unable to load state, must be at state 'win' to load" << endl;
    }
}

void GameEngine::play() {
    if (currentState == "win"){
        currentState = "start";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'win' to load" << endl;
    }
}

void GameEngine::startUpPhase(){

    string command ="";

    bool startingUp = true;
    int numPlayers = 0;

    cin >> command;

    while(startingUp || (participants.size() < 2)){
        if (command.find("loadmap")){
            this->loadMap(command);
        } else if (command == "validatemap") {
            this->validateMap();
        } else if (command == "addplayer") {
            if(participants.size() < 6){
                cout<<"how many players would you like to add? ";
                cin>>numPlayers;
                for(int i =0;i<numPlayers;i++){
                    this->addPlayer();
                }
            }else{
                cout<<"Maximum number of players reached";
            }
        } else if (command == "assigncountries") {
            this->assignCountries();
        }
    }
     
}