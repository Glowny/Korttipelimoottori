#include "Platform.h"


Platform::Platform(Server &server):_server(server)
{
	_currentPlayerIndex = 0;
}


Platform::~Platform(void)
{
}

void Platform::DEBUG_writeFunction()
{
	std::ofstream outputFile("vesa.dat",std::ios::binary|std::ios::out|std::ifstream::trunc);

	if(outputFile)
	{
		_ruleBook.push_back(ValueComparison(SMALLER,OWN_TO_TABLE));
		_ruleBook.push_back(ValueComparison(SAME,OWN));
		_ruleBook.push_back(AmountComparison(BIGGER_SAME));

		outputFile.write((char*)&_ruleBook,sizeof(_ruleBook));

		outputFile.close();
	}
}

void Platform::DEBUG_readFunction()
{
	std::ifstream inputFile("vesa.dat",std::ios::binary|std::ios::in);

	if(inputFile)
	{
		while(inputFile.peek() != EOF)
		{
			inputFile.read((char*)&_ruleBook,sizeof(Rulebook));
		}
		
		inputFile.close();
	}

}

void Platform::reset()
{
	_dealer.initialize();
	_players.clear();
	_server.reset();
}

void Platform::loadRuleBook()
{
	//_ruleBook = tiedosto.dat
	_ruleBook.init(_players);

}
void Platform::setUp(int playerAmount)
{
	_dealer.shuffle();

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	_areas.push_back(PlayArea());

	int deckSize = _dealer.deck.hand.size();

	for(int i = 0; i < deckSize; i++)
	{
		for(int j = 0; j < _players.size(); j++)
		{
			_players[j].addCards(_dealer.deal(1));
		}
	}

	std::vector<sf::Uint16> _cardAmounts;

	for(int i = 0; i < _players.size(); i++)
	{
		_cardAmounts.push_back(_players[i].getHand().hand.size());
	}

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,1,_players[i].getHand(), playerIDs, _cardAmounts);
	}
}

void Platform::setUp(int playerAmount, bool frontAreas)
{
	_dealer.shuffle();

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	for(int i = 0; i <= _players.size(); i++)
	{
		_areas.push_back(PlayArea());
	}

	int deckSize = _dealer.deck.hand.size();

	for(int i = 0; i < deckSize; i++)
	{
		for(int j = 0; j < _players.size(); j++)
		{
			_players[j].addCards(_dealer.deal(1));
		}
	}

	std::vector<sf::Uint16> _cardAmounts;

	for(int i = 0; i < _players.size(); i++)
	{
		_cardAmounts.push_back(_players[i].getHand().hand.size());
	}

	int areasAmount;

	if(frontAreas)
		areasAmount = _players.size()+1;
	else
		areasAmount = 1;

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,areasAmount,_players[i].getHand(), playerIDs, _cardAmounts);
	}
}

void Platform::setUp(int playerAmount,int startingHandSize)
{
	_dealer.shuffle();

	DEBUG_writeFunction();
	DEBUG_readFunction();
	_ruleBook;

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	_areas.push_back(PlayArea());

	loadRuleBook();

	for(int i = 0; i < _players.size(); i++)
	{
		_players[i].addCards(_dealer.deal(startingHandSize));
	}

	std::vector<sf::Uint16> _cardAmounts;

	for(int i = 0; i < _players.size(); i++)
	{
		_cardAmounts.push_back(_players[i].getHand().hand.size());
	}

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,1,_players[i].getHand(), playerIDs, _cardAmounts);
	}
}

void Platform::setUp(int playerAmount,int startingHandSize, bool frontAreas)
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
	}

	for(int i = 0; i <= _players.size(); i++)
	{
		_areas.push_back(PlayArea());
	}

	std::vector<sf::Uint16> _cardAmounts;

	for(int i = 0; i < _players.size(); i++)
	{
		_cardAmounts.push_back(_players[i].getHand().hand.size());
	}

	int areasAmount;

	if(frontAreas)
		areasAmount = _players.size()+1;
	else
		areasAmount = 1;

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,areasAmount,_players[i].getHand(), playerIDs, _cardAmounts);
	}
}

CardPacket Platform::processTurn()
{
	_server.giveTurn(_currentPlayerIndex);

	CardPacket temp;

	temp = _server.receive(_currentPlayerIndex);

	_players[_currentPlayerIndex].removeCards(temp._cards);

	_areas[temp._area].addCards(temp._cards);

	EXCEPTION_OUTCOME exception = _ruleBook.checkExceptionRules(temp._cards);

	switch(exception)
	{
	case NOTHING:
	_currentPlayerIndex++;

	if(_currentPlayerIndex == _players.size())
		_currentPlayerIndex = 0;
		break;
	case CLEAR_TABLE:
		for(int i = 0; i < temp._cards.size(); i++)
		{
		_discard.push_back(temp._cards.hand[i]);
		}
		_areas[temp._area].clear();
		break;
	}

	

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
