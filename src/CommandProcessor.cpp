#include "CommandProcessor.h"
#include <iostream>

std::string CommandProcessor::readCommand() {
    std::string userInput;
    std::cout << "Enter a command: ";
    std::cin.ignore(); // Clear any previous newline characters
    std::getline(std::cin, userInput);
    return userInput;
}

void CommandProcessor::getCommand() {
    std::string s = readCommand();
    Command* newCommand = new Command(s);
    saveCommand(newCommand);
}

void CommandProcessor::saveCommand(Command* c) {
    commands.push_back(c);
}

void CommandProcessor::displayCommands() {
    for (Command* cmd : commands) {
        std::cout << "Command: " << cmd->commandText << ", Effect: " << cmd->effect << std::endl;
    }
}