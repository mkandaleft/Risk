#include "iostream"
#include <vector>
#include "../include/AllHeaders.h"
//#include "MapDriver.cpp"
//#include "PlayerDriver.cpp"
#include "GameEngineDriver.cpp"
#include "CommandProcessingDriver.cpp"
#include "OrdersDriver.cpp"
#include "Cardsdriver.cpp"

using std::string;
using std::vector;


int main() {
    

    //Map myMap = testLoadMap("Map/Earth.map");
    //myMap.display();
    //myMap.validate();
    //testPlayers(); // Call the testPlayer method in PlayerDriver.cpp
    //testOrdersLists();
    //testCards();

        
    testCommandProcessing();
    testStartupPhase();

    return 0;
}

