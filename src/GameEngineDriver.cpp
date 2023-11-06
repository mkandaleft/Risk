#include "../include/GameEngine.h"
#include <iostream>
#include "../include/AllHeaders.h"
#include "GameEngine.cpp"
#include "Player.cpp"

using namespace std;

void testGameStates(){
    GameEngine engine("start");
    
    string command;
    bool exit = false;

    cout << "Welcome! Please enter a command to begin playing!" << endl;

    while (exit == false){
        cin >> command;
        //ex: loadmap Earth.map
        if (command=="loadmap"){
            engine.loadMap(command);
        } else if (command == "validatemap") {
            engine.validateMap();
        } else if (command == "addplayer") {
            engine.addPlayer("");
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

void testStartupPhase(){
    GameEngine engine("start");
    engine.startUpPhase();

    Map* world = engine.getMap();
    vector<Player*> contestants = engine.getPlayers();
    Deck* cards = engine.getDeck();

    world->display();

    cards->display();

    int playerCount = 1;

    for(Player* player: contestants){
        cout<<"\nPlayer "<<playerCount++<<endl;
        cout<<"Name: "<<player->getName()<<endl;
        cout<<"Territories: ";
        for(Territory* land: player->getTerritories()){
            cout<<land->getName()<<" ";
        }
        cout<<"\nHand: ";
        for(Card* card: player->getHand()->getHand()){
            cout<<card->getType().getName()<< " ";
        }
        cout<<"\n";

    }

    //prematurely calls end to delete dynamic objects
    engine.setState("win");
    engine.end();
}

int main(){
    testStartupPhase();
    return 0;
}

//
//int main() {
//    testGameStates();
//    return 0;
//}
//
