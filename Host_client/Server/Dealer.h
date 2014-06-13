#pragma once
#include "Card.h"
#include <vector>
#include <ctime>
class Dealer
{
public:
	Dealer(void);
	~Dealer(void);
	void shuffle();
	std::vector<Card> deal(int i);
	void initialize();
	
private:
	std::vector<Card> deck;
	
};