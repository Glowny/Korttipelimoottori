#pragma once
#include <iostream>
#include "SFML\Network.hpp"
class Player
{
public:
	Player(std::string id, sf::IpAddress ip, unsigned short udpport);
	~Player(void);
	
	std::string ID;
	sf::IpAddress IP;
	unsigned short UDPport;
};

