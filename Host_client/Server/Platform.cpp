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
		_ruleBook.push_back(ValueComparison(3,10,3,10,BIGGER_SAME,OWN_TO_TABLE));
		_ruleBook.push_back(ValueComparison(11,13,7,13,BIGGER_SAME,OWN_TO_TABLE));
		_ruleBook.push_back(ValueComparison(2,2,1,13,ANY,OWN_TO_TABLE));
		_ruleBook.push_back(ValueComparison(1,1,11,13,ANY,OWN_TO_TABLE));
		_ruleBook.push_back(ValueComparison(SAME, OWN));

		_ruleBook.push_back(AmountComparison(BIGGER_SAME));

		_ruleBook.push_back(BasicRule(DRAW_TO_5,EACH_TURN));

		_ruleBook.push_back(ExceptionalRule(EMPTY_PLAY, DRAW_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(10,0) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(10,1) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(10,2) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(10,3) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(1,0) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(1,1) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(1,2) ,CLEAR_TABLE));
		_ruleBook.push_back(ExceptionalRule(SPECIFIED_CARD,Card(1,3) ,CLEAR_TABLE));

		_ruleBook.writeToHostFile("vesa_host.dat");
		_ruleBook.writeToClientFile("vesa_client.dat");
		_ruleBook.clear();
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
	_areas.clear();
	_discard.clear();
	_server.reset();
}

void Platform::loadRulebook()
{
	_ruleBook.readFromHostFile("vesa_host.dat");

	std::fstream inputFile("vesa_client.dat",std::ios::binary|std::ios::in);

	_ruleBookData = "";

	while(inputFile.peek() != EOF)
	{
		char c;

		inputFile.read(&c,sizeof(char));
		_ruleBookData+=c;
	}

	_currentPlayerIndex = _ruleBook.init(_players);

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
		_server.send(i,1,_players[i].getHand(), playerIDs, _cardAmounts, _currentPlayerIndex);
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
		_server.send(i,areasAmount,_players[i].getHand(), playerIDs, _cardAmounts, _currentPlayerIndex);
	}
}

void Platform::setUp(int playerAmount,int startingHandSize)
{
	_dealer.shuffle();

	DEBUG_writeFunction();

	std::vector<std::string> playerIDs = _server.initialize(playerAmount);

	for(int i = 0; i < playerIDs.size(); i++)
	{
		_players.push_back(Player(playerIDs[i]));
	}

	_areas.push_back(PlayArea());

	loadRulebook();

	for(int i = 0; i < _players.size(); i++)
	{
		_players[i].addCards(_dealer.deal(startingHandSize));
	}

	std::vector<sf::Uint16> _cardAmounts;

	for(int i = 0; i < _players.size(); i++)
	{
		_cardAmounts.push_back(_players[i].getHand().size());
	}

	_server.sendRulebook(_ruleBookData);

	for(int i = 0; i < _players.size(); i++)
	{
		_server.send(i,1,_players[i].getHand(), playerIDs, _cardAmounts, _currentPlayerIndex);
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
		_server.send(i,areasAmount,_players[i].getHand(), playerIDs, _cardAmounts, _currentPlayerIndex);
	}
}

CardPacket Platform::processTurn()
{
	std::cout<<"Current player index number: "<<_currentPlayerIndex<<std::endl;

	_server.giveTurn(_currentPlayerIndex);

	CardPacket temp;

	temp = _server.receive(_currentPlayerIndex);

	_players[_currentPlayerIndex].removeCards(temp._cards);

	if(temp._area >= 0 && temp._area < _areas.size())
	{
		_areas[temp._area].addCards(temp._cards);

		for(int i = 0; i < _ruleBook.getBasicRules().size(); i++)
		{
			if(_ruleBook.getBasicRules()[i]._type == DRAW_TO_5)
			{
				if(_ruleBook.getBasicRules()[i]._trigger == EACH_TURN)
				{
					sf::Uint16 noArea = -1;
					int drawAmount = 5 - _players[_currentPlayerIndex].getHand().size();
					if(drawAmount > 0)
					{
						Hand drawn = _dealer.deal(drawAmount);
						_players[_currentPlayerIndex].addCards(drawn);
						_server.send(_currentPlayerIndex, CardPacket(noArea, drawn));

						std::cout<<_players[_currentPlayerIndex].getID()<<" draws "<<drawn.size()<<" cards"<<std::endl;
					}
				}
			}
		}

		EXCEPTION_OUTCOME exception = _ruleBook.checkExceptionRules(temp._cards);

		Hand emptyHand;
		CardPacket temp2;

		switch(exception)
		{
		case NOTHING:
			_server.send(_currentPlayerIndex, temp);

			_currentPlayerIndex++;
			if(_currentPlayerIndex == _players.size())
				_currentPlayerIndex = 0;
			break;
		case CLEAR_TABLE:
			for(int i = 0; i < temp._cards.size(); i++)
			{
			_discard.push_back(temp._cards.hand[i]);
			}
			for(int i = 0; i < _areas[temp._area].getHand().size(); i++)
			{
			_discard.push_back(_areas[temp._area].getHand().hand[i]);
			}
			_areas[temp._area].clear();
			_players[_currentPlayerIndex].removeCards(temp._cards);
			temp2 = CardPacket(temp._area, emptyHand);
			_server.sendReplacement(temp2);
			_server.send(_currentPlayerIndex, temp._cards.size());

			std::cout<<_players[_currentPlayerIndex].getID()<<" cleared table & played "<<temp._cards.size()<<std::endl;

			return temp2;
			break;
		case DRAW_TABLE:
			_players[_currentPlayerIndex].addCards(_areas[temp._area].getHand());
			sf::Uint16 noArea;
			temp2 = CardPacket(noArea,_areas[temp._area].getHand());
			_areas[temp._area].clear();
			_server.sendReplacement(temp);
			_server.send(_currentPlayerIndex,temp2);

			std::cout<<_players[_currentPlayerIndex].getID()<<" draws table cards"<<std::endl;

			_currentPlayerIndex++;
			if(_currentPlayerIndex == _players.size())
				_currentPlayerIndex = 0;
			break;
		}
	}
	return temp;
}

void Platform::createArea()
{
	_areas.push_back(PlayArea());
}

void Platform::addAreaCards(int i, Hand h)
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