#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "LoggingObserver.h"

class Command: public Subject, public ILoggable {
public:
    std::string commandText;
    std::string effect;

    Command(std::string text);
    void saveEffect(std::string eff);

    //observer methods
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notify(ILoggable* loggable) override;
    string stringToLog() override;
};

class CommandProcessor: public Subject, public ILoggable  {
public:
    std::vector<Command*> commands;

    std::string readCommand();
    std::string getCommand();
    void saveCommand(Command* c);
    void displayCommands();

    //observer methods
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notify(ILoggable* loggable) override;
    string stringToLog() override;
};

class FileLineReader {
public:
    std::ifstream file;

    FileLineReader(std::string filename);
    std::string readLineFromFile();
};

class FileCommandProcessorAdapter {
public:
    FileLineReader flr;
    CommandProcessor& processor;

    FileCommandProcessorAdapter(std::string filename, CommandProcessor& processorRef);
    void readCommand();
    void saveCommand(std::string s);
};
