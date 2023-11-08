#pragma once

#include <string>

class Command {
public:
    std::string commandText;
    std::string effect;

    Command(std::string text);
    void saveEffect(std::string eff);
};