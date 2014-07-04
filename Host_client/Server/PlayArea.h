#pragma once
#include "Hand.h"
class PlayArea
{
public:
	PlayArea(void);
	void setHand(Hand h);
	Hand getHand();
	Hand getLastAdded();
	Card getTopCard();
	void addCards(Hand h);
	void removeCards(Hand h);
	void clear();
	~PlayArea(void);
private:
	Hand hand, lastAdded;
};