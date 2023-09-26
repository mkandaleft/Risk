
#pragma once

#include <iostream>
using std::string;

class  Territory {
    
    private:
    string name;

    public:
    Territory(const string& name);

    string getName() const;
};
