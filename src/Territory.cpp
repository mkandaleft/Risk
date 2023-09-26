
#include "../include/Territory.h"

using std::string;

Territory::Territory(const string& name) : name(name) {}

string Territory::getName() const {
    return name;
}