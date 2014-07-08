#include "Interface.h"


Interface::Interface(void)
{
}

void Interface::addPlayer(std::string id, sf::IpAddress ip, int port)
{
	_players.push_back(Player(id,ip,port));
}



Interface::~Interface(void)
{
}
