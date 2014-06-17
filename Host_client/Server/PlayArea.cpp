#include "PlayArea.h"


PlayArea::PlayArea(void)
{
}


PlayArea::~PlayArea(void)
{
}

Hand PlayArea::getHand()
{
	return hand;
}

void PlayArea::setHand(std::vector<Card> h)
{
	hand.setHand(h);
}

void PlayArea::addCards(Hand h)
{
	for(int i = 0; i < h.hand.size(); i++)
	{
		hand.add(h.hand[i]);
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
}