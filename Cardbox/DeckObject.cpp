#include "DeckObject.h"


DeckObject::DeckObject(std::vector<CardObject>&cards,int ensimmainen):cardVector(cards)
{
	first = ensimmainen;
	last = cardVector.size()-1;
}


void DeckObject::setPosition(sf::Vector2f position)
{
	for(int i = 0; i < cardVector.size();i++)
	{
		if(cardVector[i].getID()>=first &&  cardVector[i].getID()<=last)
		{
			if(!cardVector[i].getHanded())
			cardVector[i]._sprite.setPosition(position);
		}
	}
}

void DeckObject::shuffle(sf::Vector2f pos, unsigned int seed)
{
	std::srand(seed);

	std::vector<CardObject> tempVec;

	for(int i = 0; i < cardVector.size(); i++)
	{
		if(cardVector[i].getID()>=first &&  cardVector[i].getID()<=last)
		{
			if(!cardVector[i].getHanded())
			{
			tempVec.push_back(cardVector[i]);
			cardVector.erase(cardVector.begin()+i);
			}
		}
	}

	std::random_shuffle(tempVec.begin(),tempVec.end());

	for(int i = 0; i  < tempVec.size(); i++)
	{
		cardVector.insert(cardVector.begin(),tempVec[i]);
	}

	setPosition(pos);
}

DeckObject::~DeckObject(void)
{
}
