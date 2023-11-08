#include <iostream>
#include "../include/AllHeaders.h"
#include "GameEngine.cpp"
#include "CommandProcessing.cpp"
#include "MapDriver.cpp"

using namespace std;

void testGameStates(){
    GameEngine engine("start");

    CommandProcessor processor;
    
    string command;
    bool exit = false;  
    Map myMap;

    cout << "Welcome! Please enter a command to begin playing!" << endl;

    while (exit == false){
        command = processor.getCommand();
        if (command == "loadmap"){
            //engine.loadMap();
            if (engine.getState() == "start" || engine.getState() == "map loaded") {
                myMap = testLoadMap("Map/Earth.map");
                engine.setState("maploaded");
                cout << engine.getState() << endl;
            }
            else {
                cout << "Unable to load state, must be at state 'start' or 'map loaded' to load" << endl;
            }
        } else if (command == "validatemap") {
            if (engine.getState() == "maploaded") {
                if (myMap.validate()) {
                    engine.setState("mapvalidated");
                }
                cout << engine.getState() << endl;
            }
            else {
                cout << "Unable to load state, must be at state 'map loaded' to load" << endl;
            }
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
        }else if (command == "exit") {
            exit = true;
        }
        else {
            cout << "Incorrect command. Please retry." << endl;
            cout << command<< endl;
        }
    }
}


int main() {
    testGameStates();
    return 0;
}

