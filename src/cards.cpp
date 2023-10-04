#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../include/cards.h"
using namespace std;


int Card::idCounter;

Card::Card() {
	//type = random type
}

Card::Card(string _type) {
	type = _type;
}
//Card:: Card(Order type){}

//copy constructor
Card::Card(const Card& other) {
	type = other.type;
	id = other.id;
}

string Card::getType() {
	return type;
}

int Card::getId() {
	return id;
}

void Card::addId() {
	id = ++(idCounter);
}

void Card::play(Deck& deck, Hand& hand) {
	//type.execute()
	//cout << "Execute " << type <<"\n";

	if (deck.getSize() > deck.getMaxSize()) {//stops user from adding card to a full deck
		cout << "The deck is full, where did you get that";
	}
	else {
		
		deck.addCard(*this);//add card to random index

		//remove card from hand
		hand.removeCard(*this);
	}
}

Deck::Deck() {
	maxSize = 0;
}

Deck::Deck(int numCards) {

	//limits the deck
	maxSize = numCards;

	//adds cards to the array
	srand((unsigned int)time(NULL) * (unsigned int)time(NULL));
	int index = 0;
	for (int i = 0; i < numCards; i++) {
		index = rand() % (cards.size()+1);
		cards.insert(cards.begin()+index, new Card(cardTypes[i % 5]));
	}
}

void Deck::draw(Hand& hand) {
	if (cards.size()<=0) {
		cout << "No more cards\n";
		return;
	}

	if (hand.getSize() >= hand.getMax()) {
		cout << "You have too many cards already\n";
		return;
	}


	srand((unsigned int)time(NULL)* (unsigned int)time(NULL));
	int index = rand() % cards.size(); //index where the card will be randomly inserted


	Card* drawn = cards[index]; // get random card to be inserted to hand later
	drawn->addId();


	//add card to hand
	hand.addCard(*drawn);

	//remove card from hand
	cards.erase(cards.begin() + index);

}


void Deck::display() {
	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getType() << " ";
	}
	cout << "\n";
}


vector<Card*> Deck::getDeck() {
	return cards;
}

int Deck::getMaxSize() {
	return maxSize;
}

int Deck::getSize() {
	return cards.size();
}


void Deck::addCard(Card& added) {
	if (cards.size() >= maxSize) {
		cout << "Deck is full, what are you adding";
		return;
	}


	srand((unsigned int)time(NULL) * (unsigned int)time(NULL));
	int index = rand() % cards.size(); //index where the card will be randomly inserted

	cards.insert(cards.begin()+index, &added);
}


Hand::Hand(int max) {
	maxSize = max;
}

void Hand::display() {
	for (int i = 0; i < playerHand.size(); i++) {
		cout << playerHand[i]->getType() << " ";
	}
	cout << "\n";
}

vector<Card*> Hand::getHand() {
	return playerHand;
}

Card* Hand::getCard(int index) {
	return playerHand[index];
}

void Hand::addCard(Card& card) {
	playerHand.push_back(&card);
}

void Hand::removeCard(Card remove) {
	for (size_t i = 0; i < playerHand.size(); ++i) {
		if (playerHand[i]->getId() == remove.getId()) {
			playerHand.erase(playerHand.begin() + i);
			break;  //exit the loop because object was found
		}
	}
	//throw something to tell system it doesn't exist
}

int Hand::getMax() {
	return maxSize;
}

int Hand::getSize() {
	return playerHand.size();
}
