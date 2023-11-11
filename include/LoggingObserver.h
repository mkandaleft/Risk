#pragma once
#include <iostream>
#include <list>

using namespace std;

class ILoggable {
    public:
        virtual string stringToLog() = 0;
};

class Observer {
    public:
        virtual ~Observer();
        virtual void update(ILoggable* loggable) = 0;

    protected:
        Observer();
};

class Subject {
    public:
        virtual void attach(Observer* o)=0;
        virtual void detach(Observer* o)=0;
        virtual void notify(ILoggable* loggable)=0;
        Subject() {};
        virtual ~Subject() {};  // fix empty brackets

    protected:
        list<Observer*> *_observers;
};

class LogObserver : public Observer {
    public:
        virtual void update(ILoggable* loggable) = 0;
};