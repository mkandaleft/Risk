#include "iostream"
#include <vector>

//#include "MapDriver.cpp"
#include "PlayerDriver.cpp"
#include "GameEngineDriver.cpp"
#include "CommandProcessingDriver.cpp"
#include "OrdersDriver.cpp"
#include "Cardsdriver.cpp"
#include "LoggingObserverDriver.cpp"
#include "PlayerStrategiesDriver.cpp"
#include "TournamentDriver.cpp"

using std::string;
using std::vector;


int main() {

    std::ofstream file("gamelog.txt", std::ofstream::out | std::ofstream::trunc); // delete the content of the log file each time the program is run

    // Check if the file is successfully opened
    if (file.is_open()) {
        // Erase the content of the file
        file.close();
    } else {
        // Handle error if the file cannot be opened
        std::cout << "Error opening the file." << std::endl;
        return 1;
    }
    
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
    testCards();

    */


    /*
    Assignment 2
    */
    //testCommandProcessing();
    //testStartupPhase();
    //testLoggingObserver();
    /*
    Assignment 3
    */

    testTournament();

    testPlayerStrategies();
    

    return 0;
}