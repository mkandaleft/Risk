#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <getopt.h>

using namespace std;

vector<string> splitArguments(const string& input);

int main(int argc, char* argv[]) {


    vector<string> mapFiles;
    vector<string> playerStrategies;
    int numGames = 0;
    int maxTurns = 0;

    int opt;
    while ((opt = getopt(argc, argv, "M:P:G:D:")) != -1) {
        switch (opt) {
        case 'M':
            // Parse map files
            mapFiles = splitArguments(optarg);
            break;
        case 'P':
            // Parse player strategies
            playerStrategies = splitArguments(optarg);
            break;
        case 'G':
            // Parse number of games
            numGames = atoi(optarg);
            break;
        case 'D':
            // Parse maximum number of turns
            maxTurns = atoi(optarg);
            break;
        default:
            cerr << "Usage: " << argv[0] << " -M <mapfiles> -P <playerstrategies> -G <numgames> -D <maxturns>" << endl;
            return 1;
        }
    }

    // Validate input
    if (mapFiles.empty() || playerStrategies.empty() || numGames < 1 || maxTurns < 10 || maxTurns > 50) {
        cerr << "Invalid command. Please provide valid arguments." << endl;
        cerr << "Usage: " << argv[0] << " -M <mapfiles> -P <playerstrategies> -G <numgames> -D <maxturns>" << endl;
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

    return 0;
}

vector<string> splitArguments(const string& input) {
    vector<string> arguments;
    bool inQuotes = false;
    string argument;

    for (char c : input) {
        if (c == '"') {
            inQuotes = !inQuotes;
        }
        else if (c == ' ' && !inQuotes) {
            arguments.push_back(argument);
            argument.clear();
        }
        else {
            argument += c;
        }
    }

    if (!argument.empty()) {
        arguments.push_back(argument);
    }
    return arguments;
}
