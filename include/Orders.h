#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>


using std::string;
using std::vector;
class Territory;
class Player;
class Hand;
class GameEngine;

class  Orders {
private:
    string name;
    string description;
    string result;

public:
    Orders();
    Orders(string& name);


    //will use the proper one from the subclasses
    virtual bool validate(GameEngine* gameEngine) = 0;
    virtual void execute(GameEngine* gameEngine) = 0;
    virtual ~Orders();

    string getName();
    string getDescription();
    string getResult();
    void setName(string s);
    void setDescription(string s);
    void setResult(string s);
};

class Deploy : public Orders {
private:
    int units;
    Territory* target;
    Player* issuingPlayer;

public:
    Deploy(int units, Territory* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine)override;
};

class Advance : public Orders {
private:
    int units;
    Territory* source;
    Territory* target;
    Player* issuingPlayer;
    void Battle(Territory* source, Territory* target, Player* issuingPlayer);
    bool isAlly(Player* player1, Player* player2);

public:
    Advance(int units, Territory* source, Territory* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine) override;
};

class Bomb : public Orders {
private:
    Territory* target;
    Player* issuingPlayer;

public:
    Bomb(Territory* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine) override;
};

class Blockade : public Orders {
private:
    Territory* target;
    Player* issuingPlayer;

public:
    Blockade(Territory* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine) override;
};

class Airlift : public Orders {
private:
    int units;
    Territory* source;
    Territory* target;
    Player* issuingPlayer;

public:
    Airlift(int units, Territory* source, Territory* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine) override;
};

class Negotiate : public Orders {
private:
    Player* issuingPlayer;
    Player* target;

public:
    Negotiate(Player* target, Player* issuingPlayer);
    bool validate(GameEngine* gameEngine) override;
    void execute(GameEngine* gameEngine) override;
};

class  OrdersList {
private:
    vector<Orders*> ordersList;

public:
    void addOrder(Orders* order);
    void remove(int position);
    void move(int oldPosition, int newPosition);
    void printOrders();

    vector<Orders*> getOrders();
};