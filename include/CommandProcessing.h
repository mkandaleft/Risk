#pragma once
#include <vector>
#include <string>
#include <fstream>

class Command {
public:
    std::string commandText;
    std::string effect;

    Command(std::string text);
    void saveEffect(std::string eff);
};

class CommandProcessor {
public:
    std::vector<Command*> commands;

    std::string readCommand();
    void getCommand();
    void saveCommand(Command* c);
    void displayCommands();
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
