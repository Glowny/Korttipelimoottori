#pragma once
#include "Player.h"

class Interface
{
public:
	Interface();
	~Interface(void);
	void addPlayer(std::string aleksi, sf::IpAddress ip);
	Player getPlayer(int index){return _players[index];}
private:
	std::vector<Player>_players;
};