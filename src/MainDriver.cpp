#include "iostream"
#include <vector>

//#include "MapDriver.cpp"
#include "PlayerDriver.cpp"
#include "GameEngineDriver.cpp"
#include "CommandProcessingDriver.cpp"
#include "OrdersDriver.cpp"
#include "Cardsdriver.cpp"

using std::string;
using std::vector;


int main() {
    //compile using
    //g++ Orders.cpp cards.cpp Map.cpp Territory.cpp Player.cpp CommandProcessing.cpp GameEngine.cpp MainDriver.cpp -o mainDriver 
    
    //run using ./mainDriver

    /*
    Assignment 1
    Map myMap = testLoadMap("Map/Earth.map");
    myMap.display();
    myMap.validate();
    testPlayers(); // Call the testPlayer method in PlayerDriver.cpp
    testOrdersLists();

    */
       testCards();


    /*
    Assignment 2
    */
    //testCommandProcessing();
    //testStartupPhase();

    

    return 0;
}

