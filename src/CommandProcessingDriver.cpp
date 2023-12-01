
#include "../include/GameEngine.h"
#include "../include/CommandProcessing.h"

//#include "CommandProcessing.cpp"
//#include "GameEngineDriver.cpp"

void ExecuteCommand(string command, GameEngine* engine) {


    if (command.find("loadmap",0)== 0) {
       engine->loadMap(command);
    }
    else if (command.find("loadmap", 0) == 0) {
        engine->loadMap(command);
    }
    else if (command == "validatemap") {
        engine->validateMap();
    }
    else if (command.find("addplayer", 0) == 0) {
        engine->addPlayer(command);
    }
    else if(command=="gamestart"){
        engine->gameStart();
    }
    else if (command == "assigncountries") {
        engine->assignCountries();
    }
    else if (command == "issueorder") {
        engine->issueOrder();
    }
    else if (command == "endissueorders") {
        engine->endIssueOrders();
    }
    else if (command == "execorder") {
        // execorder cant be called here, as it need an order to be passed. This is fine because it is only ever called form the executeOrdersPhase()
        //engine->execOrder();
    }
    else if (command == "endexecorders") {
        engine->endExecOrders();
    }
    else if (command == "win") {
        engine->win();
    }
    else if (command == "end") {
        engine->end();
    }
    else if (command == "play") {
        engine->play();
    }
    else if (command == "exit") {
        engine->setState("start");
        return;
    }
    else {
        cout << "Incorrect command. Please retry." << endl;
        cout << command << endl;
    }

}

int testCommandProcessing() {
    
    GameEngine engine("start");
    CommandProcessor processor;
    FileCommandProcessorAdapter fileAdapter("TestCommands/test1.txt", processor);
    
    
    while (true) {
        cout << "1. Read commands from console" << endl;
        cout << "2. Read commands from file" << endl;
        cout << "3. Display commands" << endl;
        cout << "4. Exit" << endl;
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        std::cin.ignore();
        string s;

        switch (choice) {
            case 1: //enter command by hand
                while (true) {
                    s = processor.getCommand();
                    if(s=="exit"||s=="quit") break;
                    ExecuteCommand(s, &engine);
                    //to do: find a better way to save effect
                    for (Command* cmd : processor.commands) {
                        if (cmd->commandText.find(s,0)==0) {
                            cmd->saveEffect(engine.getState());
                        }
                    }
                }
                break;
            case 2: //read commands from a text file
                fileAdapter.readCommand();  
                for (Command* cmd : processor.commands)
                {
                    ExecuteCommand(cmd->commandText, &engine);
                    cmd->saveEffect(engine.getState());
                }
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
