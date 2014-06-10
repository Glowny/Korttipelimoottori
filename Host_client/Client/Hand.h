#pragma once
#include"Card.h"
#include <SFML/Network.hpp>
#include <iostream>

class Hand
{

friend sf::Packet& operator <<(sf::Packet& packet, const Hand& hand)
	{
		for(int i = 0; i < hand.hand.size(); i++)
		{
			packet<<hand.hand[i];
		}

		return packet;
	}

friend sf::Packet& operator >>(sf::Packet& packet, Hand& hand)
	{
		for(int i = 0; i < hand.hand.size(); i++)
		{
			packet>>hand.hand[i];
		}

		return packet;
	}

public:
	Hand(){}
	~Hand(void);

	void setHand(std::vector<Card> h){hand = h;}
	void add(Card c){hand.push_back(c);}

	

	std::vector<Card> hand;
};