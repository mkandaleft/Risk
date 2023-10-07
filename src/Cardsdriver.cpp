// Cardsdriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "../include/cards.h"
#include "cards.cpp"
#include "../include/AllHeaders.h"
using namespace std;

void testCards() {
	Deck deck(15);

	Hand myHand(5);

	cout << "Deck\n";
	deck.display();

	cout << "\nDrawing...\n";
	deck.draw(myHand);
	deck.draw(myHand);
	deck.draw(myHand);
	deck.draw(myHand);
	deck.draw(myHand);
	deck.draw(myHand);


	cout << "\nHand after drawing\n";
	myHand.display();

	cout << "\nDeck after drawing\n";
	deck.display();

	cout << "\nPlay the whole hand" << endl;

	for (int i = 0; i < myHand.getMax(); i++) {
		myHand.getCard(0)->play(deck,myHand);
	}

	cout << "Deck again\n";
	deck.display();
	cout << "\nHand again\n";
	myHand.display();

}


//int main()
//{
//	testCards();
//}