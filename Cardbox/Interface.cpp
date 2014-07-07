#include "Interface.h"


Interface::Interface(void)
{
}

void Interface::addPlayer(std::string id, sf::IpAddress ip)
{
	_players.push_back(Player(id,ip));
}



Interface::~Interface(void)
{
}
