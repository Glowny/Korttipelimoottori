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
	deck.hand.clear();

	for(int i = 1; i < 13; i++)
	{
		Card h(i, Hearts, false);
		Card d(i, Diamonds);
		Card c(i, Clubs);
		Card s(i, Spades);

		deck.hand.push_back(h);
		deck.hand.push_back(d);
		deck.hand.push_back(c);
		deck.hand.push_back(s);
	}
}

void Dealer::shuffle()
{
	std::random_shuffle(deck.hand.begin(), deck.hand.end());
}

Hand Dealer::deal(int i)
{
	Hand temp;
	if(deck.hand.size() > 0)
	{
		for(int j = 0; j < i; j++)
		{
			temp.hand.push_back(deck.hand[0]);
			deck.hand.erase(deck.hand.begin());
		}
	}
	else
		std::cout<<"Deck is empty"<<std::endl;

	return temp;
}