#include "../include/Orders.h"
#include "../include/Player.h"
#include "../include/Territory.h"
#include "../include/cards.h"
#include "../include/Map.h"
#include "../include/GameEngine.h"
#include <string>
#include <algorithm>

using std::string;

//ORDERS
//default order constructor
Orders::Orders() {
    name = "default order name";
    description = "default order description";
    result = "default order result";
    _observers = new list<Observer*>;
    this->attach(logObserver);
}

//parameterized constructor
Orders::Orders(string& name) : name(name) {
    _observers = new list<Observer*>;
    this->attach(logObserver);
}
/*
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
    notify(this);
}
*/
Orders::~Orders()
{
}

//getters
string Orders::getName() {
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

//write to log
string Orders::stringToLog() {
    return "Order Name: " + getName() + ", Description: " + getDescription() + ", Result: " + getResult();
}

//DEPLOY
Deploy::Deploy(int unitsIn, Territory* targetIn, Player* issuingPlayerIn) {
    setName("Deploy");
    this->units = unitsIn;
    this->target = targetIn;
    this->issuingPlayer = issuingPlayerIn;

    setDescription("put a certain number of army units on a target territory");
    setResult("Units have been deployed.");
}

string Deploy::getName() {
    return "Deploy";
}


bool Deploy::validate(GameEngine* gameEngine) {
    bool valid = true;
    std::cout << "Validating deploy action" << std::endl;
    //if element found, deploy is valid
//should I be checking reinforcement pool as well?
    std::string issuingName = this->issuingPlayer->getName();
    std::string ownerName = this->target->getOwner()->getName();

    bool samePlayer = issuingName.compare(ownerName) == 0;
    valid &= samePlayer;

    int issuingReinforcementCount = this->issuingPlayer->getReinforcement();
    bool hasEnoughUnits = issuingReinforcementCount >= this->units;
    valid &= hasEnoughUnits;

    return valid;
}

void Deploy::execute(GameEngine* gameEngine) {
    if (validate(gameEngine)) {
        this->target->setUnits(this->target->getUnits() + this->units);
        this->issuingPlayer->useReinforcement(this->units);
        std::cout << getResult() << std::endl;
        notify(this);
    }
    else {
        std::cout << "Could not deploy army units." << std::endl;
    }
}


//ADVANCE
Advance::Advance(int unitsIn, Territory* sourceIn, Territory* targetIn, Player* issuingPlayerIn) {
    setName("Advance");
    setDescription("move a certain number of army units from one territory to another territory");
    setResult("Units have been moved.");
    this->source = sourceIn;
    this->target = targetIn;

    units = unitsIn;
    this->issuingPlayer = issuingPlayerIn;
}

string Advance::getName() {
    return "Advance";
}

bool Advance::validate(GameEngine* gameEngine) {
    std::cout << "Validating advance action" << std::endl;
    bool valid = false;
    //source not owned by issuer OR target not adjacent
    Territory* p = *find(this->source->getAdjacents().begin(), this->source->getAdjacents().end(), this->target);
    if ((this->source->getOwner()->getName().compare(this->issuingPlayer->getName()) == 0) || (p != *this->source->getAdjacents().end())) {
        valid = true;
    }
    return valid;
}

void Advance::execute(GameEngine* gameEngine) {

    if (validate(gameEngine)) {
        if ((this->target->getOwner()->getName().compare(this->issuingPlayer->getName())) == 0) {
            this->target->setUnits(this->target->getUnits() + this->units);
            this->source->setUnits(this->source->getUnits() - this->units);
            std::cout << getResult() << std::endl;
            notify(this);
        }
    }
    else if (validate(gameEngine) && !isAlly(source->getOwner(), target->getOwner())) {
        Battle(this->source, this->target, this->issuingPlayer);
        std::cout << getResult() << std::endl;
        notify(this);
    }

    else {
        std::cout << "Could not move army units." << std::endl;
    }
}

bool Advance::isAlly(Player* player1, Player* player2) {
    bool isAlly = false;

    for (Player* players1 : player1->getAlliances()) {
        for (Player* players2 : player2->getAlliances()) {
            if (players1->getName().compare(players2->getName()) == 0) {
                isAlly = true;
            }
        }
    }
    return isAlly;
}

void Advance::Battle(Territory* source, Territory* target, Player* issuingPlayer)
{
    srand(time(NULL));
    while (source->getUnits() > 0 || target->getUnits() > 0) {
        if (rand() % 100 + 1 <= 60) {
            target->setUnits((target->getUnits()) - 1);
        }
        if (rand() % 100 + 1 <= 70) {
            source->setUnits((source->getUnits()) - 1);
        }
    }
    if (target->getUnits() == 0) {
        target->getOwner()->getTerritories().erase(find(target->getOwner()->getTerritories().begin(), target->getOwner()->getTerritories().end(), target));
        target->setOwner(this->issuingPlayer);
        this->issuingPlayer->addTerritory(*target);
        target->setUnits(source->getUnits());
        source->setUnits(0);
        //remove?
   // this->issuingPlayer->getHand()->addCard(Deck::draw());
    }
}

//BOMB
Bomb::Bomb(Territory* targetIn, Player* issuingPlayerIn) {
    setName("Bomb");
    this->target = targetIn;
    this->issuingPlayer = issuingPlayerIn;

    setDescription("destroy half of the army units located on a target territory.");
    setResult("Bomb has detonated. Half of the units have been destroyed.");
}

string Bomb::getName() {
    return "Bomb";
}

bool Bomb::validate(GameEngine* gameEngine) {
    bool valid = false;
    bool isAdjacent = false;
    bool isAlly = false;
    bool hasCard = false;
    for (Territory* territory : this->target->getAdjacents())
    {
        if ((territory->getOwner()->getName().compare(this->issuingPlayer->getName())) == 0) {
            isAdjacent = true;
        }
    }
    for (Player* player1 : this->issuingPlayer->getAlliances()) {
        for (Player* player2 : gameEngine->getPlayers()) {
            if (player1->getName().compare(player2->getName()) == 0) {
                isAlly = true;
            }
        }
    }
    for (Card* card : this->issuingPlayer->getHand()->getHand()) {
        if (card->getType()->getName().compare(this->getName())) {
            hasCard = true;
        }
    }
    std::cout << "Validating bomb action" << std::endl;
    if (((this->target->getOwner()->getName().compare(this->issuingPlayer->getName())) != 0) && isAdjacent && !isAlly && hasCard) {
        valid = true;
    }

    return valid;
}

void Bomb::execute(GameEngine* gameEngine) {
    if (validate(gameEngine)) {
        std::cout << getResult() << std::endl;
        this->target->setUnits((this->target->getUnits()) / 2);
        notify(this);
    }
    else {
        std::cout << "Could not detonate bomb." << std::endl;
    }
}

//BLOCKADE
Blockade::Blockade(Territory* targetIn, Player* issuingPlayerIn) {
    setName("Blockade");
    this->target = targetIn;
    this->issuingPlayer = issuingPlayerIn;
    setDescription("Triple the number of army units on a target territory and make it a territory.");
    setResult("Blockade has been created. Army units have tripled.");
}

string Blockade::getName() {
    return "Blockade";
}

bool Blockade::validate(GameEngine* gameEngine) {
    bool valid = false;
    bool hasCard = false;
    for (Card* card : this->issuingPlayer->getHand()->getHand()) {
        if (card->getType()->getName().compare(this->getName())) {
            hasCard = true;
        }
    }
    if (((this->target->getOwner()->getName().compare(this->issuingPlayer->getName())) == 0) && hasCard) {
        valid = true;
    }
    std::cout << "Validating blockade action" << std::endl;
    return valid;
}

void Blockade::execute(GameEngine* gameEngine) {
    if (validate(gameEngine)) {
        this->target->setUnits((this->target->getUnits()) * 2);
        this->target->setOwner(gameEngine->getNeutralPlayer());
        gameEngine->getNeutralPlayer()->addTerritory(*this->target);
        std::cout << getResult() << std::endl;
        notify(this);
    }
    else {
        std::cout << "Could not create blockade." << std::endl;
    }
}

//AIRLIFT
Airlift::Airlift(int unitsIn, Territory* sourceIn, Territory* targetIn, Player* issuingPlayerIn) {
    setName("Airlift");
    units = unitsIn;
    this->source = sourceIn;
    this->target = targetIn;
    this->issuingPlayer = issuingPlayerIn;

    setDescription("advance a certain number of army units from one from one territory to another.");
    setResult("Airlift successful. Army units have moved.");
}

string Airlift::getName() {
    return "Airlift";
}

bool Airlift::validate(GameEngine* gameEngine) {
    bool valid = false;
    bool hasCard = false;
    std::cout << "Validating airlift action" << std::endl;
    for (Card* card : this->issuingPlayer->getHand()->getHand()) {
        if (card->getType()->getName().compare(this->getName())) {
            hasCard = true;
        }
    }
    //target and source territories have same owner
    if ((this->source->getOwner()->getName().compare(this->target->getOwner()->getName())) == 0 && hasCard) {
        valid = true;
    }
    return valid;
}

void Airlift::execute(GameEngine* gameEngine) {
    if (validate(gameEngine)) {
        std::cout << getResult() << std::endl;
        this->target->setUnits(this->target->getUnits() + this->units);
        this->source->setUnits(this->source->getUnits() - this->units);
        notify(this);
    }
    else {
        std::cout << "Could not airlift." << std::endl;
    }
}

//NEGOTIATE
Negotiate::Negotiate(Player* targetIn, Player* issuingPlayerIn) {
    setName("Negotiate");
    this->issuingPlayer = issuingPlayerIn;
    this->target = targetIn;
    setDescription("prevent attacks between the current player and another target player until the end of the turn.");
    setResult("Attacks have been prevented.");
}

string Negotiate::getName() {
    return "Negotiate";
}

bool Negotiate::validate(GameEngine* gameEngine) {
    bool valid = false;
    bool hasCard = false;
    for (Card* card : this->issuingPlayer->getHand()->getHand()) {
        if (card->getType()->getName().compare(this->getName())) {
            hasCard = true;
        }
    }
    if ((this->issuingPlayer->getName().compare(this->target->getName())) != 0 && hasCard) {
        valid = true;
    }
    std::cout << "Validating negotiate action" << std::endl;

    return valid;
}

void Negotiate::execute(GameEngine* gameEngine) {
    if (validate(gameEngine)) {
        std::cout << getResult() << std::endl;
        this->target->addAlliance(this->issuingPlayer);
        this->issuingPlayer->addAlliance(this->target);
        notify(this);
    }
    else {
        std::cout << "Could not negotiate." << std::endl;
    }
}

//ORDER LIST

OrdersList::OrdersList() {
    _observers = new list<Observer*>;
    this->attach(logObserver);
}

void OrdersList::addOrder(Orders* order) {
    //benevolent player can't push back order
    ordersList.push_back(order);
    notify(this);
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
        std::swap((&ordersList)[oldPosition], (&ordersList)[newPosition]);
        std::cout << "Order at position " << oldPosition << "successfully moved to position " << newPosition << "!" << std::endl;
    }
}

void OrdersList::printOrders()
{
    for (Orders* order : ordersList)
    {
        std::cout << order->getName() << std::endl;
    }
}

vector<Orders*> OrdersList::getOrders() {
    return ordersList;
}

void OrdersList::clearOrders() {
    ordersList.clear();
}

//Log method
string OrdersList::stringToLog() {
    std::string logString = "Orders List: ";
    logString += ordersList.back()->getName(); // Add the order type of the last order in the list
    return logString;
}