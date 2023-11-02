#include "../include/GameEngine.h"
#include <iostream>
#include "../include/AllHeaders.h"
#include "GameEngine.cpp"

using namespace std;

void testGameStates(){
    GameEngine engine("start");
    
    string command;
    bool exit = false;

    cout << "Welcome! Please enter a command to begin playing!" << endl;

    while (exit == false){
        cin >> command;
        //ex: loadmap Earth.map
        if (command.find("loadmap")){
            engine.loadMap(command);
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

/*
int main(){
    GameEngine engine("start");
    engine.loadMap("loadmap Map/Earth.map");
    //engine.validateMap();
    return 0;
}
*/

//
//int main() {
//    testGameStates();
//    return 0;
//}
//
