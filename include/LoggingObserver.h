#pragma once
#include <iostream>
#include <list>

using namespace std;

class Observer {
    public:
        ~Observer();
        virtual void update() = 0;

    protected:
        Observer();
};

class Subject {
    public:
        virtual void attach(Observer* o)=0;
        virtual void detach(Observer* o)=0;
        virtual void notify()=0;
        Subject() {};
        ~Subject() {};  // EMPTY BRACKETS SHOULDN'T BE EMPTY ):<

    protected:
        list<Observer*> *_observers;
};

class ILoggable {
    public:
        virtual void stringToLog(string message) = 0;
};
