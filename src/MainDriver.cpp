#include "iostream"
#include <vector>
#include "../include/AllHeaders.h"
//#include "MapDriver.cpp"
#include "PlayerDriver.cpp"
#include "GameEngineDriver.cpp"
#include "OrdersDriver.cpp"
#include "cardsDriver.cpp"
//#include "../include/testing/MapDriver.h"

using std::string;
using std::vector;


int main() {
    

    Map myMap = testLoadMap("Map/Earth.map");
    //myMap.display();
    myMap.validate();

    testPlayers(); // Call the testPlayer method in PlayerDriver.cpp
    testOrdersLists();
    testCards();
    //testGameStates();
    testStartupPhase();

    return 0;
}

