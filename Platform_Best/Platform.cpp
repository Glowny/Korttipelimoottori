#include "Platform.h"


Platform::Platform(void)
{
}


Platform::~Platform(void)
{
}

void Platform::setUp()
{
	for(int i = 0; i < _dealer.deck.hand.size(); i++)
	{
		for(int j = 0; j < _players.size(); j++)
		{
			_players[j].addCards(_dealer.deal(1));
		}
	}

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,_players[i].getHand());
	}
}

void Platform::setUp(int startingHandSize)
{
	for(int i = 0; i < _players.size(); i++)
	{
		_players[i].addCards(_dealer.deal(startingHandSize));
		_server.send(i,_players[i].getHand());
	}
}

void Platform::processTurn()
{
	_server.giveTurn(_currentPlayerIndex);

	Hand temp;

	temp = _server.receive(_currentPlayerIndex);

	_currentPlayerIndex++;

	if(_currentPlayerIndex == _players.size())
		_currentPlayerIndex = 0;
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