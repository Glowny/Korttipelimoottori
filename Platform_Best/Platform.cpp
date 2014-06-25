#include "Platform.h"


Platform::Platform(Server &server):_server(server)
{
	_currentPlayerIndex = 0;
}


Platform::~Platform(void)
{
}

void Platform::setUp(int playerAmount)
{
	_dealer.shuffle();

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	int deckSize = _dealer.deck.hand.size();

	for(int i = 0; i < deckSize; i++)
	{
		for(int j = 0; j < _players.size(); j++)
		{
			_players[j].addCards(_dealer.deal(1));
		}
	}

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,_players[i].getHand(), playerIDs);
	}
}

void Platform::setUp(int playerAmount,int startingHandSize)
{
	_dealer.shuffle();

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	for(int i = 0; i < _players.size(); i++)
	{
		_players[i].addCards(_dealer.deal(startingHandSize));
		_server.send(i,_players[i].getHand(), playerIDs);
	}
}

CardPacket Platform::processTurn()
{
	_server.giveTurn(_currentPlayerIndex);

	CardPacket temp;

	temp = _server.receive(_currentPlayerIndex);

	_players[_currentPlayerIndex].removeCards(temp._cards);

	_currentPlayerIndex++;

	if(_currentPlayerIndex == _players.size())
		_currentPlayerIndex = 0;

	return temp;
}

void Platform::createArea()
{
	_areas.push_back(PlayArea());
}

void Platform::playCards(int i, Hand h)
{
	_areas[i].addCards(h);
}

Hand Platform::getAreaCards(int i)
{
	return _areas[i].getHand();
}

void Platform::removeAreaCards(int i, Hand h)
{
	_areas[i].removeCards(h);
}

Hand Platform::drawCards(int i)
{
	Hand temp;
	temp = _dealer.deal(i);
	return temp;
}

Player Platform::getPlayer(int i)
{
	return _players[i];
}
