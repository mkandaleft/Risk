#pragma once
#pragma once
#include <string>
#include <fstream>

class FileLineReader {
public:
    std::ifstream file;

    FileLineReader(std::string filename);
    std::string readLineFromFile();
};
