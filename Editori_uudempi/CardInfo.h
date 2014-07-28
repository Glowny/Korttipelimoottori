#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
class CardInfo
{
public:
	CardInfo(std::string name, float cardWidth,float cardHeight, int cardAmount, int cards[]);
	CardInfo(std::string filename);
	~CardInfo(void);
	void save();
	int getCardAmount();
	void print();
	int* getCards();
	std::string getName();
private:
	std::string _name;
	int _cardWidth;
	int _cardHeight;
	int _cardAmount;
	int* _cards;
};

