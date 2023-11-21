#pragma once

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "cards.h"
#include "CommandProcessing.h"

using std::string;

class GameEngine {

    private:
    string currentState;
    Map* gameMap;
    vector<Player*> participants;
    Deck* gameDeck;
    CommandProcessor processor;
    

    public:
    GameEngine(const string& state);
    string getState() const;
    void setState(string state);
    void loadMap(string map);
    void validateMap();
    void addPlayer(string name);
    void addPlayerObject(Player* player);
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

    //for testStartupPhase
    Map* getMap();
    vector<Player*> getPlayers();
    Deck* getDeck();
};