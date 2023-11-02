#pragma once

#include <iostream>
#include <vector>
#include "AllHeaders.h"
#include "Map.h"

using std::string;

class GameEngine {

    private:
    string currentState;
    vector<Player*> participants;
    Map* gameMap;
    //Deck* cards;

    

    public:
    GameEngine(const string& state);
    string getState() const;
    void setState(string state);
    void loadMap(string map);
    void validateMap();
    void addPlayer();
    void assignCountries();
    void issueOrder();
    void endIssueOrders();
    void execOrder();
    void endExecOrders();
    void win();
    void end();
    void play();
    void startUpPhase();
};