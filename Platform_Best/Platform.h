#pragma once
#include "Server.h"
#include "Dealer.h"
#include "Player.h"
class Platform
{
public:
	Platform(void);
	~Platform(void);
	void setUp();
	void setUp(int startingHandSize);
	void processTurn();
	void createArea();
	void playCards(int i, Hand h);
	Hand getAreaCards(int i);
	void removeAreaCards(int i, Hand h);
	Hand drawCards(int i);
	
private:
	Server _server;
	Dealer _dealer;
	std::vector<Player> _players;
	int _currentPlayerIndex;
	std::vector<PlayArea> _areas;

};