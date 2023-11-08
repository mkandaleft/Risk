#include "FileCommandProcessorAdapter.h"

FileCommandProcessorAdapter::FileCommandProcessorAdapter(std::string filename, CommandProcessor& processorRef) : flr(filename), processor(processorRef) {}

void FileCommandProcessorAdapter::readCommand() {
    std::string command;
    while (!(command = flr.readLineFromFile()).empty()) {
        saveCommand(command);
    }
}

void FileCommandProcessorAdapter::saveCommand(std::string s) {
    Command* newCommand = new Command(s);
    processor.commands.push_back(newCommand);
}