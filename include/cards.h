#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>

#include "GameEngine.h"
#include "Orders.h"
#include "Player.h"

using namespace std;

class Hand;
class Deck;


class Card {
public:
	Card();

	Card(Orders& type);

	Card(const Card& other);

	void play(Deck& gameDeck, Hand& playerHand);

	Orders* getType();

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
	Card& draw();


	void display();
	vector<Card*> getDeck();

	void addCard(Card& added);
	void removeCard(Card drawn);

	int getMaxSize();
	int getSize();

	GameEngine* getGame();

	//void shuffle();
private:
	vector<Card*> cards;
	int maxSize;
	GameEngine* game;

};

class Hand {
public:
	Hand();
	Hand(int max);
	Hand(Player* player);
	Hand(int max, Player* player);
	Hand(const Hand& other);

	int getMax();
	int getSize();

	void display();
	vector<Card*> getHand();
	Card* getCard(int idx);

	void addCard(Card& add);
	void removeCard(Card removed);

	Player* getOwner();

private:
	vector<Card*> playerHand;
	int maxSize;
	Player* owner;
};

void testCards();