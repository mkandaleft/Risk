#pragma once

#include <iostream>
#include <vector>
#include "LoggingObserver.h"
using std::string;
using std::vector;

class  Orders: public Subject, public ILoggable {
private:
    string name;
    string description;
    string result;

public:
    Orders();
    Orders(const string& name);


    //will use the proper one from the subclasses
    virtual bool validate();
    virtual void execute();
    virtual ~Orders();

    string getName() const;
    string getDescription();
    string getResult();
    void setName(string s);
    void setDescription(string s);
    void setResult(string s);

    string stringToLog() override;
};

class Deploy : public Orders {
private:

public:
    Deploy(int i);
    bool validate();
    void execute();
};

class Advance : public Orders {
private:

public:
    Advance(int i);
    bool validate();
    void execute();
};

class Bomb : public Orders {
private:

public:
    Bomb(int i);
    bool validate();
    void execute();
};

class Blockade : public Orders {
private:

public:
    Blockade(int i);
    bool validate();
    void execute();
};

class Airlift : public Orders {
private:

public:
    Airlift(int i);
    bool validate();
    void execute();
};

class Negotiate : public Orders {
private:

public:
    Negotiate(int i);
    bool validate();
    void execute();
};

class  OrdersList: public Subject, public ILoggable {
private:
    vector<Orders> ordersList;

public:
    void addOrder(Orders& order);
    void remove(int position);
    void move(int oldPosition, int newPosition);
    void printOrders();

    const vector<Orders>& getOrders() const;

    string stringToLog() override;
};