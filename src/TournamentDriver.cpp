#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <random>
#include <sstream>

using namespace std;

vector<string> splitArguments(const string& input);

int main() {
    vector<string> mapFiles;
    vector<string> playerStrategies;
    int numGames = 0;
    int maxTurns = 0;

    // Read all arguments in one line
    cout << "Enter arguments in one line (e.g., -M map1.txt map2.txt -P strategy1 strategy2 -G 5 -D 20): ";
    string inputLine;
    getline(cin, inputLine);

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

    // Print parsed values
    cout << "Map Files: ";
    for (const string& mapFile : mapFiles) {
        cout << mapFile << " ";
    }
    cout << endl;

    cout << "Player Strategies: ";
    for (const string& strategy : playerStrategies) {
        cout << strategy << " ";
    }
    cout << endl;

    cout << "Number of Games: " << numGames << endl;
    cout << "Maximum Turns: " << maxTurns << endl;

    // Perform the tournament logic here
    // ...
    cout << "Tournament ongoing.." << endl;

    // Result:
    cout << "Result:" << endl;
    // Display winner (placeholder - display random)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, playerStrategies.size() - 1);
    int randomIndex;
    for (const string& mapFile : mapFiles) {
        cout << mapFile << ":" << endl;
        for (int i = 0; i < numGames; i++) {
            randomIndex = dist(gen);
            cout << "Game " << i + 1 << ": " << playerStrategies[randomIndex] << "; ";
        }
        cout << endl;
    }

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
