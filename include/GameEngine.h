#pragma once

#include <iostream>
#include <vector>
#include "AllHeaders.h"
#include "Map.h"

using std::string;

class GameEngine {

    private:
    string currentState;
    Map* gameMap;
    vector<Player*> participants;
    Deck* gameDeck;
    Player* neutralPlayer = new Player("neutralPlayer");

    

    public:
    GameEngine(const string& state);
    string getState() const;
    void setState(string state);
    void loadMap(string map);
    void validateMap();
    void addPlayer(string name);
    void assignCountries();
    void gameStart();
    void issueOrder();
    void endIssueOrders();
    void execOrder();
    void endExecOrders();
    void win();
    void end();
    void play();
    void startUpPhase();
    static Player* getNeutralPlayer();

    //for testStartupPhase
    Map* getMap();
    vector<Player*> getPlayers();
    Deck* getDeck();
};