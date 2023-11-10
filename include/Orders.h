#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using std::string;
using std::vector;

class  Orders {
private:
    string name;
    string description;
    string result;

public:
    Orders();
    Orders(const string& name);


    //will use the proper one from the subclasses
    virtual bool validate() =0;
    virtual void execute() =0;
    virtual ~Orders();

    string getName() const;
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
    bool validate();
    void execute();
};

class Advance : public Orders {
private:
    int units;
    Territory* source;
    Territory* target;
    Player* issuingPlayer;
    void Battle(Territory* source, Territory* target);
    bool isAlly(Player* player1, Player* player2);

public:
    Advance(int units, Territory* source, Territory* target, Player* issuingPlayer);
    bool validate();
    void execute();
};

class Bomb : public Orders {
private:
    Territory* target;
    Player* issuingPlayer;

public:
    Bomb(Territory* target, Player* issuingPlayer);
    bool validate();
    void execute();
};

class Blockade : public Orders {
private:
    Territory* target;
    Player* issuingPlayer;

public:
    Blockade(Territory* target, Player* issuingPlayer);
    bool validate();
    void execute();
};

class Airlift : public Orders {
private:
    int units;
    Territory* source;
    Territory* target;
    Player* issuingPlayer;

public:
    Airlift(int units, Territory* source, Territory* target, Player* issuingPlayer);
    bool validate();
    void execute();
};

class Negotiate : public Orders {
private:
    Player* issuingPlayer;
    Player* target;

public:
    Negotiate(Player* target, Player* issuingPlayer);
    bool validate();
    void execute();
};

class  OrdersList {
private:
    vector<Orders> ordersList;

public:
    void addOrder(Orders& order);
    void remove(int position);
    void move(int oldPosition, int newPosition);
    void printOrders();

    const vector<Orders>& getOrders() const;
};