#include "PlayArea.h"


PlayArea::PlayArea(void)
{
}


PlayArea::~PlayArea(void)
{
}

Card PlayArea::getTopCard()
{
	if(hand.hand.size() != 0)
		return hand.hand[hand.hand.size()-1];
	else
		std::cout<<"ERROR! NO CARDS IN AREA!"<<std::endl;
	return Card();
}

Hand PlayArea::getHand()
{
	return hand;
}

Hand PlayArea::getLastAdded()
{
	return lastAdded;
}

void PlayArea::setHand(Hand h)
{
	hand = h;
	lastAdded = h;
}

void PlayArea::addCards(Hand h)
{
	lastAdded.clear();

	for(int i = 0; i < h.hand.size(); i++)
	{
		hand.push_back(h.hand[i]);
		lastAdded.push_back(h.hand[i]);
	}
}

void PlayArea::removeCards(Hand h)
{
	bool erased;

	for(int i = 0; i < hand.hand.size();)
	{
		erased = false;
		for(int j = 0; j < h.hand.size();j++)
		{
			if(h.hand[j] == hand.hand[i])
			{
				hand.hand.erase(hand.hand.begin()+i);
				erased = true;
			}
		}
		if(!erased)
			i++;
	}
	lastAdded.clear();
}

void PlayArea::clear()
{
	hand.clear();
	lastAdded.clear();
}