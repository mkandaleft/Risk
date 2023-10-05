#include "iostream"
#include <vector>
#include "../include/AllHeaders.h"

#include "MapDriver.cpp"

using std::string;
using std::vector;

int main() {
    //testPlayers(); // Call the testPlayer method in PlayerDriver.cpp

    Map myMap = testLoadMap("Map/Earth.map");
    myMap.display();
    myMap.validate();
    

    return 0;
}
