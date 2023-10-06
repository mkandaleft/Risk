/*
*   This is the player driver file. This file includes a method
*   for testing the functionalities of a Player object.
*
*   Written by: Mark Kandaleft
*   For COMP 345 
*/
#include "iostream"
#include <vector>
#include "../include/AllHeaders.h"
#include "Player.cpp"
//#include "Orders.cpp"

void testPlayers() {

    // Create some Territory instances
    Territory territory1("Territory 1");
    Territory territory2("Territory 2");

    // Create Player instances and add territories
    Player player1("Player 1");
    player1.addTerritory(territory1);

    Player player2("Player 2");
    player2.addTerritory(territory2);

    // Access territories for each player
    std::cout << player1.getName() << " can attack: ";
    for (const Territory* territory : player1.toAttack()) {
        std::cout << territory->getName() << " ";
    }
    std::cout << std::endl;

    std::cout << player2.getName() << " can defend: ";
    for (const Territory* territory : player2.toDefend()) {
        std::cout << territory->getName() << " ";
    }
    std::cout << std::endl;

}
