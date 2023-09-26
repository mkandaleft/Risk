
#include "Hand.h"

using std::string;

Hand::Hand(const string& cards) : cards(cards) {}

string Hand::getCards() const {
    return cards;
}