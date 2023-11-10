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
Deploy::Deploy(int unitsIn, Territory* targetIn, Player* issuingPlayerIn) {
    setName("Deploy");
    this->units = unitsIn;
    this->target = *targetIn;
    this->issuingPlayer = *issuingPlayerIn;
   
    setDescription("put a certain number of army units on a target territory");
    setResult("Units have been deployed.");
}

bool Deploy::validate() override {
    boolean valid = false;
    std::cout << "Validating deploy action" << std::endl;
    //if element found, deploy is valid
//should I be checking reinforcement pool as well?
    if((this->issuingPlayer->getName().compare(this->target->getOwner()))==0){
        valid = true;
    }

    return valid;
}

void Deploy::execute() override{
    if (Orders::validate()) {
        this->target.setUnits((this->target->getUnits() + this->units);
        std::cout << getResult() << std::endl;
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
    this->source = *sourceIn;
    this->target = *targetIn;
    units = unitsIn;
    this->issuingPlayer = *issuingPlayerIn;
}

bool Advance::validate() override{
    std::cout << "Validating advance action" << std::endl;
    bool valid = false;
    //source not owned by issuer OR target not adjacent
    Territory* p = find(this->source->getAdjacent().begin(), this->source->getAdjacent().end(), this->target);
    if ((this->source->getOwner()->getName().compare(this->issuingPlayer->getName()) == 0) || (*p!= this->source->getAdjacent().end())) {
        valid = true;
    }
    return valid;
}

void Advance::execute() override{
 
    if (Orders::validate()) {
        if ((this->target->getOwner()->getName().compare(this->issuingPlayer->getName())) == 0) {
            this->target->setUnits(this->target.getUnits() + this.units);
            this->source->setUnits(this->source.getUnits() - this.units);
        }
    }
    else if(Order::validate() && !isAlly(*source->getOwner(), *target->getOwner()){
            battle(this->source, this->target);
        }
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not move army units." << std::endl;
    }
}

bool isAlly(Player* player1, Player* player2) {
    bool isAlly = false;
 
    for each (Player * players1 in *player1.getAlliances()) {
        for each (Player * players2 in *player2.getAlliances) {
            if (*players1.getName().compare(*players2.getName()) == 0) {
                isAlly = true;
            }
        }
    }
    return isAlly;
}

Advance::Battle(Territory* source, Territory* target)
{
    srand(time(NULL));
    while (*source->getUnits() > 0 || *target->getUnits() > 0) {
        if (rand() % 100 + 1 <= 60) {
            *target->setUnits((*target->getUnits()) - 1);
        }
        if (rand(% 100 + 1 <= 70) {
            *source->setUnits((*source->getUnits())-1);
        }
    }
    if (*target->getUnits() == 0) {
        Territory toRemove = find(*target->getOwner()->getTerritories().begin(), *target->getOwner()->getTerritories().end(), *target);
        *target->getOwner()->getTerritories.erase(toRemove);
        *target->setOwner(this->issuingPlayer);
        this->issuingPlayer->addTerritory(target);
        *target->setUnits(*source->getUnits());
        *source->setUnits(0);
            //remove?
        this->issuingPlayer->getHand()->addCard(Deck::draw());
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

bool Bomb::validate() override{
    bool valid = false;
    bool isAdjacent = false;
    bool isAlly = false;
    for each (Territory* territory in this->target->getAdjacent())
    {
        if ((territory->getOwner().compare(this->issuingPlayer->getName())) == 0) {
            isAdjacent = true;
        }
    }
    for each (Player* player1 in this->issuingPlayer.getAlliances()) {
        for each (Player * player2 in GameEngine::getPlayers()) {
            if (*player1.getName().compare(*player2.getName()) == 0) {
                isAlly = true;
            }
        }
    }
    std::cout << "Validating bomb action" << std::endl;
    if (((this->target->getOwner()->getName().compare(this->issuingPlayer->getName()))!=0) && isAdjacent && !isAlly) {
        valid = true;
    }
    
    return valid;
}

void Bomb::execute() override{
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
        this->target->setUnits((this->target->getUnits()) / 2);
    }
    else {
        std::cout << "Could not detonate bomb." << std::endl;
    }
}

//BLOCKADE
Blockade::Blockade(Territory* targetIn, Player* issuingPlayerIn) {
    setName("Blockade");
    this->target = *targetIn;
    this->issuingPlayer = *issuingPlayerIn;
    setDescription("Triple the number of army units on a target territory and make it a neutral territory.");
    setResult("Blockade has been created. Army units have tripled.");
}

bool Blockade::validate() override{
    bool valid = false;
    if ((this->target->getOwner->getName().compare(this->issuingPlayer->getName())) == 0) {
        valid = true;
    }
    std::cout << "Validating bomb action" << std::endl;
    //No way of validating yet.
    return valid;
}

void Blockade::execute() override {
    if (Orders::validate()) {
        this->target->setUnits((this->target->getUnits()) * 2);
        this->target->setOwner(GameEngine::getNeutralPlayer());
        *GameEngine::getNeutralPlayer->addTerritory(this.target);
        std::cout << getResult() << std::endl;
    }
    else {
        std::cout << "Could not create blockade." << std::endl;
    }
}

//AIRLIFT
Airlift::Airlift(int unitsIn, Territory* sourceIn, Territory* targetIn, Player* issuingPlayerIn) {
    setName("Airlift");
    units = unitsIn;
    this->source = *sourceIn;
    this->target = *targetIn;
    this->issuingPlayer = *issuingPlayerIn;

    setDescription("advance a certain number of army units from one from one territory to another.");
    setResult("Airlift successful. Army units have moved.");
}

bool Airlift::validate() override{
    bool valid = false;
    std::cout << "Validating airlift action" << std::endl;
    //target and source territories have same owner
    if ((this->source->getOwner()->getName().compare(this->target->getOwner()->getName())==0) {
        valid = true;
    }
    return valid;
}

void Airlift::execute() override{
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
        this->target->setUnits(this->target.getUnits() + this.units);
        this->source->setUnits(this->source.getUnits() - this.units);
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

bool Negotiate::validate() override{
    bool valid = false;
    if ((this->issuingPlayer->getName().compare(this->target->getName())) != 0) {
        valid = true;
    }
    std::cout << "Validating negotiate action" << std::endl;
    
    return valid;
}

void Negotiate::execute() override{
    if (Orders::validate()) {
        std::cout << getResult() << std::endl;
        this->target.addAlliance(this.issuingPlayer);
        this->issuingPlayer.addAlliance(this.target);
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