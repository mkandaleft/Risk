#include <iostream>
#include "../include/AllHeaders.h"
#include "../include/GameEngine.h"
// #include "CommandProcessing.cpp"
#include "MapDriver.cpp"
#include "../include/Player.h"


using namespace std;

void testMainGameLoop(){
    GameEngine engine("start");
    CommandProcessor processor;

    engine.mainGameLoop();
}

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
        }else if (command == "exit") {
            exit = true;
        }
        else {
            cout << "Incorrect command. Please retry." << endl;
            cout << command<< endl;
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

//int main(){
  //  testStartupPhase();
 //   return 0;
//}

//
//int main() {
//    testGameStates();
//    return 0;
//}
//
