#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Command {
public:
    string commandText;
    string effect;

    Command(string text) {
        commandText = text;
    }

    void saveEffect(string eff) {
        effect = eff;
    }
};

class CommandProcessor {
public:
    vector<Command*> commands;

    void readCommand() {
        string userInput;
        cout << "Enter a command: ";
        cin.ignore(); // Clear any previous newline characters
        getline(cin, userInput);
        saveCommand(userInput);
    }

    void getCommand() {
        readCommand();
    }

    void saveCommand(string s) {
        Command* newCommand = new Command(s);
        commands.push_back(newCommand);
    }

    void displayCommands() {
        for (Command* cmd : commands) {
            cout << "Command: " << cmd->commandText << ", Effect: " << cmd->effect << endl;
        }
    }
};

class FileLineReader {
public:
    ifstream file;

    FileLineReader(string filename) {
        file.open(filename);
    }

    string readLineFromFile() {
        string line;
        if (file.is_open()) {
            getline(file, line);
        }
        return line;
    }
};

class FileCommandProcessorAdapter {
public:
    FileLineReader flr;
    CommandProcessor& processor;

    FileCommandProcessorAdapter(string filename, CommandProcessor& processorRef) : flr(filename), processor(processorRef) {}

    void readCommand() {
        string command;
        while (!(command = flr.readLineFromFile()).empty()) {
            saveCommand(command);
        }
    }

    void saveCommand(string s) {
        Command* newCommand = new Command(s);
        processor.commands.push_back(newCommand);
    }
};

int main() {
    CommandProcessor processor;
    FileCommandProcessorAdapter fileAdapter("TestCommands/test1.txt", processor);

    while (true) {
        cout << "1. Read command from console" << endl;
        cout << "2. Read command from file" << endl;
        cout << "3. Display commands" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            processor.getCommand();
            break;
        case 2:
            fileAdapter.readCommand();
            break;
        case 3:
            processor.displayCommands();
            break;
        case 4:
            // Clean up memory
            for (Command* cmd : processor.commands) {
                delete cmd;
            }
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    }

    return 0;
}
