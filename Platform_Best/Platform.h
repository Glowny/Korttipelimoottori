#pragma once
#include "Server.h"
#include "Dealer.h"
#include "Player.h"
class Platform
{
public:
	Platform();
	Platform(Server &server);
	~Platform(void);
	void setUp(int playerAmount);
	void setUp(int playerAmount,int startingHandSize);
	CardPacket processTurn();
	void createArea();
	void playCards(int i, Hand h);
	Hand getAreaCards(int i);
	void removeAreaCards(int i, Hand h);
	Hand drawCards(int i);
	Player getPlayer(int i);
	Player getCurrentPlayer(){return _players[_currentPlayerIndex];}

	
private:
	Server &_server;
	Dealer _dealer;
	std::vector<Player> _players;
	int _currentPlayerIndex;
	std::vector<PlayArea> _areas;

};