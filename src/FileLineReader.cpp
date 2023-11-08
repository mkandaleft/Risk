#include "FileLineReader.h"

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