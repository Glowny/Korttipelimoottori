#pragma once
#include "Hand.h"
class PlayArea
{
public:
	PlayArea(void);
	void setHand(std::vector<Card> h);
	Hand getHand();
	void addCards(Hand h);
	void removeCards(Hand h);
	~PlayArea(void);
private:
	Hand hand;
};