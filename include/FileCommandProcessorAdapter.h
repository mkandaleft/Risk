#pragma once
#include "FileLineReader.h"
#include "CommandProcessor.h"

class FileCommandProcessorAdapter {
public:
    FileLineReader flr;
    CommandProcessor& processor;

    FileCommandProcessorAdapter(std::string filename, CommandProcessor& processorRef);
    void readCommand();
    void saveCommand(std::string s);
};