#pragma once
#include "Player.h"

class Interface
{
public:
	Interface();
	~Interface(void);
	void addPlayer(std::string aleksi, sf::IpAddress ip);
private:
	std::vector<Player>_players;
};

