#pragma once
#include <SFML/Network.hpp>
#include <iostream>
enum Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};

class Card
{

friend sf::Packet& operator <<(sf::Packet& packet, const Card& Card)
{
    return packet << Card.value << Card.suit;
}

friend sf::Packet& operator >>(sf::Packet& packet, Card& Card)
{
    return packet >> Card.value >> Card.suit;
}

friend bool operator ==(Card &card1, Card &card2)
{
	if(card1.suit == card2.suit && card1.value == card2.value)
		return true;
	return false;
}

public:
	Card(int v, int s) : value(v), suit(s){}
	Card(){}
	/*~Card(void);*/
sf::Uint16 value;
sf::Uint16 suit;
};