#pragma once
#include "Hand.h"
#include <ctime>
class Dealer
{
public:
	Dealer(void);
	~Dealer(void);
	Hand deal(int i);
	void initialize();
	void shuffle();

	Hand deck;
};