
#include "../include/Order.h"

using std::string;

Order::Order(const string& name) : name(name) {}

string Order::getName() const {
    return name;
}