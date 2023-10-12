#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Orders.h"

using namespace std;

class Hand;
class Deck;


class Card {
public:
	Card();

	Card(Orders& type);//string as a stand in for Order

	Card(const Card& other);//copy constructor

	void play(Deck& gameDeck, Hand& playerHand);

	Orders getType();

	int getId();
	void addId();

private:
	Orders* type;
	int id;
	static int idCounter;
};

class Deck {
public:
	Deck();
	Deck(int size);
	Deck(const Deck& other);

	void draw(Hand& hand);


	void display();
	vector<Card*> getDeck();

	void addCard(Card& added);

	int getMaxSize();
	int getSize();

private:
	vector<Card*> cards;
	int maxSize;

};

class Hand {
public:
	Hand();
	Hand(int max);
	Hand(const Hand& other);

	int getMax();
	int getSize();

	void display();
	vector<Card*> getHand();
	Card* getCard(int idx);

	void addCard(Card& add);
	void removeCard(Card removed);
private:
	vector<Card*> playerHand;
	int maxSize;
};

void testCards();
