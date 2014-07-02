#pragma once
#include "Server.h"
#include "Dealer.h"
#include "Player.h"
#include "Rulebook.h"
#include <fstream>
class Platform
{
public:
	Platform();
	Platform(Server &server);
	~Platform(void);
	void reset();
	void setUp(int playerAmount);
	void setUp(int playerAmount, bool frontAreas);
	void setUp(int playerAmount,int startingHandSize);
	void setUp(int playerAmount,int startingHandSize, bool frontAreas);
	void sendRulebook();
	CardPacket processTurn();
	void createArea();
	void loadRulebook();
	void playCards(int i, Hand h);
	Hand getAreaCards(int i);
	void removeAreaCards(int i, Hand h);
	Hand drawCards(int i);
	Player getPlayer(int i);
	int getCurrentPlayerIndex(){return _currentPlayerIndex;}
	void DEBUG_writeFunction();
	void DEBUG_readFunction();
	
private:
	Server &_server;
	Dealer _dealer;
	std::vector<Player> _players;
	int _currentPlayerIndex;
	std::vector<PlayArea> _areas;
	Hand _discard;
	Rulebook _ruleBook;
	std::string _ruleBookData;
};