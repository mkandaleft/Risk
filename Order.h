#pragma once

#include <iostream>
using std::string;

class  Order {
    
    private:
    string name;

    public:
    Order(const string& name);

    string getName() const;
};
