#pragma once
#include <vector>
#include "Command.h"

class CommandProcessor {
public:
    std::vector<Command*> commands;

    std::string readCommand();
    void getCommand();
    void saveCommand(Command* c);
    void displayCommands();
}; 
