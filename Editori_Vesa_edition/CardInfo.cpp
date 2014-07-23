#include "CardInfo.h"


CardInfo::CardInfo(float cW, float cH, int amount)
{
	cardWidth = cW;
	cardHeight = cH;
	cardAmount = amount;
	cards[cardAmount];
}

void CardInfo::setCardAmount(int c[])
{
	for(int i = 0; i <cardAmount; i++)
	{
		cards[i] = c[i];
	}
}
CardInfo::~CardInfo(void)
{
}

	float CardInfo::getCardWidth()
	{
		return cardWidth;
	}
	float CardInfo::getCardHeight()
	{
		return cardHeight;
	}
	int CardInfo::getCardAmount()
	{
		return cardAmount;
	}
	int* CardInfo::getCards()
	{
		return cards;
	}