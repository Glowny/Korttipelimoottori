#pragma once
#include "Kortti.h"
#include <vector>
class Player
{
public:
	Player(int n, std::string na);
	void addCard(Kortti k);
	std::vector<Kortti> getDeck();
	int getPNumber();
	~Player(void);


private:
	std::vector<Kortti> deck;
	int playerNumber;
	std::string name;
};

