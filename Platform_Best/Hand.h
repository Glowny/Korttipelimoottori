#pragma once
#include"Card.h"
#include <SFML/Network.hpp>
#include <iostream>

class Hand
{

friend sf::Packet& operator <<(sf::Packet& packet, const Hand& hand)
	{
		sf::Uint16 size = hand.hand.size();
		packet<<size;
		for(int i = 0; i < hand.hand.size(); i++)
		{
			packet<<hand.hand[i];
		}

		return packet;
	}

friend sf::Packet& operator >>(sf::Packet& packet, Hand& hand)
	{
		sf::Uint16 size;
		packet>>size;
		Card c;
		for(int i = 0; i<size; i++)
		{
			hand.hand.push_back(c);
		}
		for(int i = 0; i < hand.hand.size(); i++)
		{
			packet>>hand.hand[i];
		}

		return packet;
	}

public:
	Hand(){}
	/*~Hand(void);*/	

	std::vector<Card> hand;
};