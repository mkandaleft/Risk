#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

#include "../include/CommandProcessing.h"
#include "../include/LoggingObserver.h"

using namespace std;

Command::Command(std::string text) : commandText(text) {
    _observers = new list<Observer*>;
    this->attach(logObserver);
}

void Command::saveEffect(std::string eff) {
    effect = eff;
    notify(this);
}

// log methods
string Command::stringToLog() {
    return "Command: " + commandText + ", Effect: " + effect;
}

CommandProcessor::CommandProcessor() {
    _observers = new list<Observer*>;
    this->attach(logObserver);
}

std::string CommandProcessor::readCommand() {
    std::string userInput;
    std::cout << "Enter a command: ";
    //std::cin.ignore(); // Clear any previous newline characters
    getline(cin, userInput);
    return userInput;
}

std::string CommandProcessor::getCommand() {
    std::string s = readCommand();
    Command* newCommand = new Command(s);
    saveCommand(newCommand);
    return s;
}

void CommandProcessor::saveCommand(Command* c) {
    commands.push_back(c);
    notify(this);
}

void CommandProcessor::displayCommands() {
    for (Command* cmd : commands) {
        std::cout << "Command: " << cmd->commandText << ", Effect: " << cmd->effect << std::endl;
    }
}

// logging methods
string CommandProcessor::stringToLog() {
    std::string logString = "Command Processor: ";
    logString += commands.back()->commandText; // Add the command text of the last command in the list
    return logString;
}

FileLineReader::FileLineReader(std::string filename) {
    file.open(filename);
}

std::string FileLineReader::readLineFromFile() {
    std::string line;
    if (file.is_open()) {
        std::getline(file, line);
    }
    return line;
}

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

//int main() {
//    CommandProcessor processor;
//    FileCommandProcessorAdapter fileAdapter("TestCommands/test1.txt", processor);
//
//    while (true) {
//        cout << "1. Read command from console" << endl;
//        cout << "2. Read command from file" << endl;
//        cout << "3. Display commands" << endl;
//        cout << "4. Exit" << endl;
//        int choice;
//        cout << "Enter your choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            processor.getCommand();
//            break;
//        case 2:
//            fileAdapter.readCommand();
//            break;
//        case 3:
//            processor.displayCommands();
//            break;
//        case 4:
//            // Clean up memory
//            for (Command* cmd : processor.commands) {
//                delete cmd;
//            }
//            return 0;
//        default:
//            cout << "Invalid choice. Try again." << endl;
//            break;
//        }
//    }
//
//    return 0;
//}

