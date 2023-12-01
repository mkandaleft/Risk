#include "../include/PlayerStrategies.h"

void testPlayerStrategies(){
    GameEngine warzone("start");

    warzone.loadMap("loadmap Map/Earth.map");

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


    for(Player* player: gamers){
        player->setStrategy(new Benevolent());
    }
    

    warzone.gameStart();

    warzone.mainGameLoop();
}
