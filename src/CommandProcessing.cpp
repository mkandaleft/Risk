#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include "../include/AllHeaders.h"

using namespace std;

Command::Command(std::string text) : commandText(text) {}

void Command::saveEffect(std::string eff) {
    effect = eff;
    notify(this);
}

// Observer methods
void Command::attach(Observer* o) {
    _observers->push_back(o);
}

void Command::detach(Observer* o) {
    _observers->remove(o);
}

void Command::notify(ILoggable* loggable) {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->update(loggable);
}

string Command::stringToLog() {
    return "Command: " + commandText + ", Effect: " + effect;
}


std::string CommandProcessor::readCommand() {
    std::string userInput;
    std::cout << "Enter a command: ";
    //std::cin.ignore(); // Clear any previous newline characters
    cin >> userInput;
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

// Observer methods
void CommandProcessor::attach(Observer* o) {
    _observers->push_back(o);
}

void CommandProcessor::detach(Observer* o) {
    _observers->remove(o);
}

void CommandProcessor::notify(ILoggable* loggable) {
    list<Observer*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->update(loggable);
}

string CommandProcessor::stringToLog() {
    std::string logString = "Command Processor: ";
    for (Command* cmd : commands) {
        logString += cmd->stringToLog() + ", ";
    }
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
