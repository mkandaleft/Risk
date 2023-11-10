#include "../include/AllHeaders.h"
#include "CommandProcessing.cpp"

int testCommandProcessing() {
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
}

//int main() {
//    testCommandProcessing();
//    return 0;
//}
