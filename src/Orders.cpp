#include "../include/Orders.h"
#include <string>

using std::string;

//ORDERS
//default order constructor
Orders::Orders() {
    name = "default order name";
    description = "default order description";
    result = "default order result";
}

//parameterized constructor
Orders::Orders(const string& name) : name(name) {}

bool Orders::validate()
{
    return false;
}

void Orders::execute()
{
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not perform default action." << std::endl;
    }
}

Orders::~Orders()
{
}

//getters
string Orders::getName() const {
    return name;
}
string Orders::getDescription() {
    return description;
}
string Orders::getResult() {
    return result;
}
//setters
void Orders::setName(string s) {
    name = s;
}
void Orders::setDescription(string s) {
    description = s;
}
void Orders::setResult(string s) {
    result = s;
}

//DEPLOY
Deploy::Deploy(int i) {
    setName("Deploy");
    setDescription("put a certain number of army units on a target territory");
    setResult("Units have been deployed.");
}

bool Deploy::validate() {
    std::cout << "Validating deploy action" << std::endl;
    //No way of validating yet.
    return true;
}

void Deploy::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not deploy army units." << std::endl;
    }
}

//ADVANCE
Advance::Advance(int i) {
    setName("Advance");
    setDescription("move a certain number of army units from one territory to another territory");
    setResult("Units have been moved.");
}

bool Advance::validate() {
    std::cout << "Validating advance action" << std::endl;
    //No way of validating yet.
    return true;
}

void Advance::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not move army units." << std::endl;
    }
}

//BOMB
Bomb::Bomb(int i) {
    setName("Bomb");
    setDescription("destroy half of the army units located on a target territory.");
    setResult("Bomb has detonated. Half of the units have been destroyed.");
}

bool Bomb::validate() {
    std::cout << "Validating bomb action" << std::endl;
    //No way of validating yet.
    return true;
}

void Bomb::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not detonate bomb." << std::endl;
    }
}

//BLOCKADE
Blockade::Blockade(int i) {
    setName("Blockade");
    setDescription("Triple the number of army units on a target territory and make it a neutral territory.");
    setResult("Blockade has been created. Army units have tripled.");
}

bool Blockade::validate() {
    std::cout << "Validating bomb action" << std::endl;
    //No way of validating yet.
    return true;
}

void Blockade::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not create blockade." << std::endl;
    }
}

//AIRLIFT
Airlift::Airlift(int i) {
    setName("Airlift");
    setDescription("advance a certain number of army units from one from one territory to another.");
    setResult("Airlift successful. Army units have moved.");
}

bool Airlift::validate() {
    std::cout << "Validating airlift action" << std::endl;
    //No way of validating yet.
    return true;
}

void Airlift::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not airlift." << std::endl;
    }
}

//NEGOTIATE
Negotiate::Negotiate(int i) {
    setName("Negotiate");
    setDescription("prevent attacks between the current player and another target player until the end of the turn.");
    setResult("Attacks have been prevented.");
}

bool Negotiate::validate() {
    std::cout << "Validating negotiate action" << std::endl;
    //No way of validating yet.
    return true;
}

void Negotiate::execute() {
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not negotiate." << std::endl;
    }
}

//ORDER LIST

void OrdersList::addOrder(Orders& order) {
    ordersList.push_back(order);
}



void OrdersList::remove(int position) {
    int listLength = ordersList.size();

    if (listLength == 0) {
        std::cout << "List is empty" << std::endl;
    }
    else if (position > listLength || position < 1) // Bounds check.
        std::cout << "Please select a valid position!" << std::endl;
    else
    {
        ordersList.erase(ordersList.begin() + position);
        std::cout << "Erase at position " << position << " successful!" << std::endl;
    }
}

void OrdersList::move(int oldPosition, int newPosition) {
    int listLength = ordersList.size();

    if (listLength == 0) {
        std::cout << "List is empty" << std::endl;
    }
    else if (oldPosition > listLength || oldPosition < 1 || newPosition > listLength || newPosition < 1) // Bounds check.
        std::cout << "Please select valid positions!" << std::endl;
    else
    {
        std::swap(ordersList[oldPosition], ordersList[newPosition]);
        std::cout << "Order at position " << oldPosition << "successfully moved to position " << newPosition << "!" << std::endl;
    }
}

void OrdersList::printOrders()
{
    for (Orders& order : ordersList)
    {
        std::cout << order.getName() << std::endl;
    }
}

const vector<Orders>& OrdersList::getOrders() const {
    return ordersList;
}