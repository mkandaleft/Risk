#include "../include/GameEngine.h"
#include <iostream>

using namespace std;

int main() {
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

    return 0;
}
