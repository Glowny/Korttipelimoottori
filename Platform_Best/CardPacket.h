#pragma once
#include "Hand.h"
class CardPacket
{

friend sf::Packet& operator <<(sf::Packet& packet, const CardPacket& cardpacket)
{
	packet<<cardpacket._cards;

	packet<<cardpacket._area;

	return packet;
}

friend sf::Packet& operator >>(sf::Packet& packet, CardPacket& cardpacket)
{
	packet>>cardpacket._cards;

	packet>>cardpacket._area;

	return packet;
}

public:
	CardPacket(){}
	CardPacket(int area, Hand cards):_area(area),_cards(cards){}
	~CardPacket(void){}

	int _area;
	Hand _cards;
};