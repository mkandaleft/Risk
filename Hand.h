
#pragma once

#include <iostream>
using std::string;

class  Hand {
    
    private:
    string cards;

    public:
    Hand(const string& cards);

    string getCards() const;
};
