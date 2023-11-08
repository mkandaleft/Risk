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
        virtual void attach(Observer* o);
        virtual void detach(Observer* o);
        virtual void notify();
        Subject();
        ~Subject();

    private:
        list<Observer*> *_observers;
};

class ILoggable {
    public:
        virtual void stringToLog(string message) = 0;
};
