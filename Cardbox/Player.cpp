#include "Player.h"


Player::Player(std::string id, sf::IpAddress ip, unsigned short udpport)
{
	ID = id;
	IP = ip;
	UDPport = udpport;
}


Player::~Player(void)
{
}
