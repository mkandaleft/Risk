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
        virtual void attach(Observer* o);
        virtual void detach(Observer* o);
        virtual void notify(ILoggable* loggable);
        Subject();
        virtual ~Subject();

    protected:
        list<Observer*> *_observers;
};

class LogObserver : public Observer {
    public:
        LogObserver();
        ~LogObserver();
        virtual void update(ILoggable* loggable);
};

extern LogObserver* logObserver;