#include "../include/PlayerStrategies.h"

void testPlayerStrategies(){
    GameEngine warzone("start");

    warzone.loadMap("loadmap Map/Earth/map");

    warzone.validateMap();

    warzone.addPlayer("addplayer Human");
    warzone.addPlayer("addplayer Aggressive");
    warzone.addPlayer("addplayer Benevolence");
    warzone.addPlayer("addplayer Neutral");
    warzone.addPlayer("addplayer Cheater");

    warzone.gameStart();

    
}