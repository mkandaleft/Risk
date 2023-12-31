#include "../include/LoggingObserver.h"
#include <iostream>
#include <fstream>

Observer::Observer() {}
Observer::~Observer() {}

Subject::Subject() {
    _observers = new list<Observer*>;
}

Subject::~Subject() {
    delete _observers;
}

void Subject::attach(Observer* o) {
    _observers->push_back(o);
}

void Subject::detach(Observer* o) {
    _observers->remove(o);
}

void Subject::notify(ILoggable* loggable) {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->update(loggable);
}

LogObserver::LogObserver() {}

LogObserver::~LogObserver() {}

void LogObserver::update(ILoggable* loggable) {
    std::ofstream logFile("gamelog.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << loggable->stringToLog() << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file" << std::endl;
    }
}

LogObserver* logObserver = new LogObserver;