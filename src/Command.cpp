#include "Command.h"

Command::Command(std::string text) : commandText(text) {}

void Command::saveEffect(std::string eff) {
    effect = eff;
}