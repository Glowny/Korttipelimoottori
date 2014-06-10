#include "Dealer.h"


Dealer::Dealer(void)
{
	std::srand(unsigned(std::time(NULL)));
	initialize();
}


Dealer::~Dealer(void)
{
}

void Dealer::initialize()
{
	deck.clear();

	for (int i = 1; i < 13; i++)
	{
		Card h(i, Hearts);
		Card d(i, Diamonds);
		Card c(i, Clubs);
		Card s(i, Spades);

		deck.push_back(h);
		deck.push_back(d);
		deck.push_back(c);
		deck.push_back(s);
	}
}

void Dealer::shuffle()
{
	std::random_shuffle(deck.begin(), deck.end());
}

std::vector<Card> Dealer::deal(int i)
{
	std::vector<Card> hand;
	for(int j = 0; j < i; j++)
	{
		hand.push_back(deck[0]);
		deck.erase(deck.begin());
	}
	return hand;
}