#pragma once
#include "Hand.h"
class PlayArea
{
public:
	PlayArea(void);
	void setHand(std::vector<Card> h);
	Hand getHand();
	Card getTopCard();
	void addCards(Hand h);
	void removeCards(Hand h);
	~PlayArea(void);
private:
	Hand hand;
};