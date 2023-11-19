#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "..\include\cards.h"
#include "..\include\Orders.h"
//#include "Orders.cpp"
using namespace std;


int Card::idCounter;

Card::Card() {
	Orders* ord = new Orders();
	type = ord;
	id = 0;
}

Card::Card(Orders& order) {
	type = &order;
	id = 0;
}

//copy constructor
Card::Card(const Card& other) {
	type = other.type;
	id = other.id;
}

Orders Card::getType() {
	return *type;
}

int Card::getId() {
	return id;
}

void Card::addId() {
	id = ++(idCounter);
}

void Card::play(Deck& deck, Hand& hand) {
	(*type).execute(); //calls execute for the card type

	if (deck.getSize() > deck.getMaxSize()) {//stops user from adding card to a full deck
		cout << "The deck is full, where did you get that";
	}
	else {

		deck.addCard(*this);//add card to random index

		//remove card from hand
		hand.removeCard(*this);
	}

	id = 0; //removes id from card since it's no longer in hand
}

Deck::Deck() {
	maxSize = 0;
}

Deck::Deck(const Deck& deck) {
	maxSize = deck.maxSize;
	cards = deck.cards;
}

Deck::Deck(int numCards) {

	//limits the deck
	maxSize = numCards;

	//adds cards to the array
	srand((unsigned int)time(NULL) * (unsigned int)time(NULL));//generate random seed
	int index = 0;
	int cardType = 0;
	int numCardTypes = 5;
	for (int i = 0; i < numCards; i++) {
		//generate random index to insert card at
		index = rand() % (cards.size() + 1);


		cardType = i % numCardTypes;//alternates between different number of cards, for an equal amount (if the deck is a multiple of 5)
		if (cardType == 0) {
			Bomb* kaboom = new Bomb(1);

			//use insert instead of push_back so that the deck is randomized to begin with
			cards.insert(cards.begin() + index, new Card(*kaboom));
		}
		else if (cardType == 1) {
			Advance* reinforce = new Advance(1);
			cards.insert(cards.begin() + index, new Card(*reinforce));
		}
		else if (cardType == 2) {

			Blockade* block = new Blockade(1);
			cards.insert(cards.begin() + index, new Card(*block));
		}
		else if (cardType == 3) {
			Airlift* air = new Airlift(1);
			cards.insert(cards.begin() + index, new Card(*air));
		}
		else if (cardType == 4) {
			Negotiate* diplomacy = new Negotiate(1);
			cards.insert(cards.begin() + index, new Card(*diplomacy));
		}
	}
}

Card& Deck::draw() {
	if (cards.size() <= 0) {
		throw runtime_error("No more cards");
	}

	srand((unsigned int)time(NULL) * (unsigned int)time(NULL));//random seed based on time
	int index = rand() % cards.size(); //index where the card will be randomly inserted

	Card* drawn = cards[index]; // get random card to be inserted to hand later
	drawn->addId();//gives ids to cards so that they can be found in the hand later

	//remove card from hand
	cards.erase(cards.begin() + index);
	
	return *drawn;

}


void Deck::display() {
	for (int i = 0; i < cards.size(); i++) {
		cout << cards[i]->getType().getName() << endl;
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

	cards.insert(cards.begin() + index, &added);
}

Hand::Hand() {
	maxSize = 10;
}

Hand::Hand(int max) {
	maxSize = max;
}

Hand::Hand(const Hand& other) {
	maxSize = other.maxSize;
	playerHand = other.playerHand;
}

void Hand::display() {
	for (int i = 0; i < playerHand.size(); i++) {
		cout << playerHand[i]->getType().getName() << endl;
	}
	cout << "\n";
}

vector<Card*> Hand::getHand() {
	return playerHand;
}

Card* Hand::getCard(int index) {
	if (index > playerHand.size()) {
		cout << "You don't have that many cards";
		return nullptr;
	}
	return playerHand[index];
}

void Hand::addCard(Card& card) {
	playerHand.push_back(&card);
}

void Hand::removeCard(Card remove) {
	for (size_t i = 0; i < playerHand.size(); ++i) {
		if (playerHand[i]->getId() == remove.getId()) {//matches id
			playerHand.erase(playerHand.begin() + i);//once found, it's removed
			break;  //exit the loop because object was found
		}
	}
	//Card does not exist
}

int Hand::getMax() {
	return maxSize;
}

int Hand::getSize() {
	return playerHand.size();
}
