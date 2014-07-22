#pragma once
#include "CardObject.h"
#include <vector>
class DeckObject
{
public:
	DeckObject(std::vector<CardObject>&cards,int ensimmainen);
	~DeckObject(void);
	void setPosition(sf::Vector2f position);
	void shuffle(sf::Vector2f pos, unsigned int seed);
private:
	std::vector<CardObject>&cardVector;
	int first,last;
};

