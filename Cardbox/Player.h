#pragma once
#include <iostream>
#include "SFML\Network.hpp"
class Player
{
public:
	Player(std::string id, sf::IpAddress ip, unsigned short udpport);
	~Player(void);

	sf::IpAddress IP;
	std::string ID;
	unsigned short UDPport;
};

