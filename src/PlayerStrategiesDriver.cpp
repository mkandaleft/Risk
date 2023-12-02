#include "../include/PlayerStrategies.h"

void testPlayerStrategies() {
    GameEngine warzone("start");

    warzone.loadMap("loadmap src/Map/Earth.map");

    warzone.validateMap();

    //players are neutral by default
    warzone.addPlayer("addplayer Human");
    warzone.addPlayer("addplayer Aggressive");
    /*
    warzone.addPlayer("addplayer Benevolence");
    warzone.addPlayer("addplayer Neutral");
    warzone.addPlayer("addplayer Cheater");
    */

    vector<Player*> gamers = warzone.getPlayers();


    gamers[0]->setStrategy(new Benevolent());
    gamers[1]->setStrategy(new Aggressive());


    warzone.gameStart();

    warzone.mainGameLoop();
}
