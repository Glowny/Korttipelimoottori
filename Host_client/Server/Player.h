#pragma once
#include "Hand.h"
#include <vector>
#include <string>

class Player
{
public:
	Player(std::string i);
	void setHand(std::vector<Card> h);
	Hand getHand();
	void addCard(Card c);
	std::string getID();
	~Player(void);


private:
	Hand hand;
	std::string id;
};