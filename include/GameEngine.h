#pragma once

#include <iostream>
using std::string;

class GameEngine {

    private:
    string currentState;

    public:
    GameEngine(const string& state);
    string getState() const;
    void setState(string state);
    void loadMap();
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
};

void testGameStates();