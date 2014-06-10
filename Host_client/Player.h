#pragma once
#include "Kortti.h"
#include <vector>
class Player
{
public:
	Player(int n);
	void addCard(Kortti k);
	std::vector<Kortti> getDeck();
	int getPNumber();
	~Player(void);


private:
	std::vector<Kortti> deck;
	int playerNumber;
};

