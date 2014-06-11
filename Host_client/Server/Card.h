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

public:
	Card(int v, int s) : value(v), suit(s){}
	Card(){}
	/*~Card(void);*/
sf::Uint16 value;
sf::Uint16 suit;
};