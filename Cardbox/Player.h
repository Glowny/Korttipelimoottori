#pragma once
#include <iostream>
#include "SFML\Network.hpp"
class Player
{
public:
	Player(std::string id, sf::IpAddress ip);
	~Player(void);
	
	std::string ID;
	sf::IpAddress IP;
};

