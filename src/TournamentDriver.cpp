#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <sstream>
#include <fstream>

#include "../include/GameEngine.h"
#include "../include/CommandProcessing.h"
using namespace std;

vector<string> splitArguments(const string& input);

int testTournament() {

    vector<string> mapFiles;
    vector<string> playerStrategies;
    int numGames = 0;
    int maxTurns = 0;

    GameEngine warzone("start");
    CommandProcessor processor;

    // Read all arguments in one line
    cout << "Enter arguments in one line (e.g., -M map1.txt map2.txt -P strategy1 strategy2 -G 5 -D 20): ";
    string inputLine = processor.readCommand();

    // Split the input line into individual arguments
    vector<string> arguments = splitArguments(inputLine);

    // Parse the arguments
    int i = 0;
    while (i < arguments.size()) {
        if (arguments[i] == "-M") {
            // Parse map files
            i++;
            while (i < arguments.size() && arguments[i][0] != '-') {
                mapFiles.push_back(arguments[i]);
                i++;
            }
        }
        else if (arguments[i] == "-P") {
            // Parse player strategies
            i++;
            while (i < arguments.size() && arguments[i][0] != '-') {
                playerStrategies.push_back(arguments[i]);
                i++;
            }
        }
        else if (arguments[i] == "-G") {
            // Parse number of games
            i++;
            if (i < arguments.size()) {
                numGames = atoi(arguments[i].c_str());
                i++;
            }
        }
        else if (arguments[i] == "-D") {
            // Parse maximum number of turns
            i++;
            if (i < arguments.size()) {
                maxTurns = atoi(arguments[i].c_str());
                i++;
            }
        }
        else {
            cerr << "Invalid argument: " << arguments[i] << endl;
            return 1;
        }
    }



    // Validate input
    if (mapFiles.empty() || playerStrategies.empty() || numGames < 1 || maxTurns < 10 || maxTurns > 50) {
        cerr << "Invalid input. Please provide valid arguments." << endl;
        return 1;
    }

    // Redirect the output stream to a file
    ofstream outputFile("game_result.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }

    // Use the outputFile instead of cout for output
    outputFile << "Map Files: ";
    for (const string& mapFile : mapFiles) {
        outputFile << mapFile << " ";
        warzone.loadMap("loadmap Map/" + mapFile);
    }
    outputFile << endl;

    outputFile << "Player Strategies: ";
    for (const string& strategy : playerStrategies) {
        outputFile << strategy << " ";
    }
    outputFile << endl;

    outputFile << "Number of Games: " << numGames << endl;
    outputFile << "Maximum Turns: " << maxTurns << endl;

    // ...

    // Redirect output to outputFile
    outputFile << "Tournament ongoing.." << endl;

    // Result:
    outputFile << "Result:" << endl;

    // Redirect output to outputFile
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, playerStrategies.size() - 1);
    int randomIndex;
    for (const string& mapFile : mapFiles) {
        outputFile << mapFile << ":" << endl;
        for (int i = 0; i < numGames; i++) {
            randomIndex = dist(gen);
            outputFile << "Game " << i + 1 << ": " << playerStrategies[randomIndex] << "; ";
        }
        outputFile << endl;
    }

    // Close the outputFile when you're done
    outputFile.close();

    return 0;

    return 0;
}

vector<string> splitArguments(const string& input) {
    vector<string> arguments;
    istringstream iss(input);
    string argument;
    while (iss >> argument) {
        arguments.push_back(argument);
    }
    return arguments;
}
