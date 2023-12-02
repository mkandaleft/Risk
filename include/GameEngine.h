#pragma once

#include <iostream>
#include <vector>
#include "Map.h"
#include "Player.h"
#include "cards.h"
#include "CommandProcessing.h"

class Deck;
class Player;

using std::string;

class GameEngine : public Subject, public ILoggable {

private:
    string currentState;
    Map* gameMap;
    vector<Player*> participants;
    Deck* gameDeck;
    CommandProcessor processor;
    Player* neutralPlayer;


public:
    GameEngine(const string& state);
    ~GameEngine();
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
    void execOrder(Orders* order);
    void endExecOrders();
    void win();
    void end();
    void play();
    void startUpPhase();
    void mainGameLoop();
    void reinforcementPhase();
    void issueOrderPhase();
    void executeOrdersPhase();
    Player* getNeutralPlayer();

    //for testStartupPhase
    Map* getMap();
    vector<Player*> getPlayers();
    Deck* getDeck();

    string stringToLog() override;
};