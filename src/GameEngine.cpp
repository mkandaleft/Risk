
#include "../include/GameEngine.h"
#include <cstdlib>

using namespace std;

GameEngine::GameEngine(const string &state) : currentState(state) {
    currentState = "start";
}

string GameEngine::getState() const{
    return currentState;
}

void GameEngine::setState(string state) {
    currentState = state;
}

void GameEngine::loadMap() {
    if (currentState == "start" || currentState == "map loaded") {
        currentState = "map loaded";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'start' or 'map loaded' to load" << endl;
    }
}

void GameEngine::validateMap() {
    if (currentState == "map loaded") {
        currentState = "map validated";
        cout << currentState << endl;
    } else {
        cout << "Unable to load state, must be at state 'map loaded' to load" << endl;
    }
}

void GameEngine::addPlayer() {
    if (currentState == "map validated" || currentState == "players added" ) {
        currentState = "players added";
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

void testGameStates(){
    GameEngine engine("start");
    
    string command;
    bool exit = false;

    cout << "Welcome! Please enter a command to begin playing!" << endl;

    while (exit == false){
        cin >> command;
        if (command == "loadmap"){
            engine.loadMap();
        } else if (command == "validatemap") {
            engine.validateMap();
        } else if (command == "addplayer") {
            engine.addPlayer();
        } else if (command == "assigncountries") {
            engine.assignCountries();
        } else if (command == "issueorder") {
            engine.issueOrder();
        } else if (command == "endissueorders") {
            engine.endIssueOrders();
        } else if (command == "execorder") {
           engine.execOrder();
        } else if (command == "endexecorders") {
            engine.endExecOrders();
        } else if (command == "win") {
            engine.win();
        } else if (command == "end") {
            engine.end();
        } else if (command == "play") {
            engine.play();
        } else {
            cout << "Incorrect command. Please retry." << endl;
        }
    }
}