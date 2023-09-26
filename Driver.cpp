#include "iostream"
#include <vector>
#include "include/AllHeaders.h"

using std::string;
using std::vector;

int main() {

    // Create some Territory instances
    Territory territory1("Territory 1");
    Territory territory2("Territory 2");

    // Create Player instances and add territories
    Player player1("Player 1");
    player1.addTerritory(territory1);

    Player player2("Player 2");
    player2.addTerritory(territory2);

    // Access territories for each player
    std::cout << player1.getName() << " owns: ";
    for (const Territory* territory : player1.toAttack()) {
        std::cout << territory->getName() << " ";
    }
    std::cout << std::endl;

    std::cout << player2.getName() << " owns: ";
    for (const Territory* territory : player2.toDefend()) {
        std::cout << territory->getName() << " ";
    }
    std::cout << std::endl;

    return 0;
}

//g++ -o myprogram Hand.cpp Hand.h Player.cpp Player.h PlayerDriver.cpp Territory.cpp Territory.h Driver.cpp Order.cpp Order.h OrderList.cpp OrderList.h
//./myprogram