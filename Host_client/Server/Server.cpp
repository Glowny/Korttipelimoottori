#include "Server.h"


Server::Server(void)
{
	_port = 2000;
	_listener.listen(_port);
	_selector.add(_listener);
}

std::vector<std::string> Server::initialize(int playercount)
{
	std::vector<std::string> playerIDs;
	std::cout << "Initializing server.." << std::endl;
	int connections = 0;
	
	std::cout << "Waiting for connections.." <<std::endl;
	while(connections < playercount)
	{
	if(_selector.wait())
		{
			if(_selector.isReady(_listener))
			{	
				std::string id;

				sf::TcpSocket* socket = new sf::TcpSocket;
				_listener.accept(*socket);
				
				_packet.clear();
				if(socket->receive(_packet) == sf::Socket::Done)
					_packet>>id;

				std::cout<<id<<" has connected to the session"<<std::endl;
				playerIDs.push_back(id);
				_clients.push_back(socket);
				_selector.add(*socket);

				connections++;
			}
		}
	}
	_connectionOK = true;
	return playerIDs;
}

void Server::reset()
{
	_packet.clear();
	_clients.clear();
	_selector.clear();
	_selector.add(_listener);
}

void Server::send(int currentPlayerIndex, CardPacket cp, int playedCardsAmount)
{
	_packet.clear();
	_packetID = ADD_CARDS;

	sf::Uint16 cPI = currentPlayerIndex, pCA = playedCardsAmount;
	_packet<<_packetID<<cPI<<cp<<pCA;

	for(int i = 0; i < _clients.size(); i++)
	{
	_clients[i]->send(_packet);
	}
}

void Server::send(int currentPlayerIndex, int playedCardsAmount)
{
	_packet.clear();
	_packetID = REMOVE_CARDS;

	sf::Uint16 cPI = currentPlayerIndex, pCA = playedCardsAmount;
	_packet<<_packetID<<cPI<<pCA;

	for(int i = 0; i < _clients.size(); i++)
	{
	_clients[i]->send(_packet);
	}
}

void Server::send(std::string message)
{
	_packet.clear();
	_packetID = MESSAGE;
	_packet<<_packetID<<message;

	for(int i = 0; i < _clients.size(); i++)
	{
	_clients[i]->send(_packet);
	}
}

void Server::send(int i, int areas, Hand cards, std::vector<std::string> playerIDs, std::vector<sf::Uint16> cardAmounts, int startingPlayerIndex)
{
	_packet.clear();
	_packetID = START;

	sf::Uint16 vectorSize = playerIDs.size();
	sf::Uint16 areasAmount = areas;
	sf::Uint16 cardAmountsSize = cardAmounts.size();

	_packet<<_packetID<<areasAmount<<cards<<vectorSize;

	for(int j = 0; j < vectorSize; j++)
	{
			_packet<<playerIDs[j];
	}

	_packet<<cardAmountsSize;

	for(int j = 0; j < cardAmounts.size(); j++)
	{
		_packet<<cardAmounts[j];
	}

	sf::Uint16 playerIndex, starterIndex;
	playerIndex = i;
	starterIndex = startingPlayerIndex;
	_packet<<playerIndex<<starterIndex;

	_clients[i]->send(_packet);
}

void Server::sendReplacement(CardPacket cp)
{
	_packet.clear();
	_packetID = SET_CARDS;
	_packet<<_packetID<<cp;

	for(int i = 0; i < _clients.size(); i++)
	{
	_clients[i]->send(_packet);
	}
}

void Server::sendRulebook(std::string rulesData)
{
	_packet.clear();
	_packetID = RULES;
	_packet<<_packetID<<rulesData;

	for(int i = 0; i < _clients.size(); i++)
	{
	_clients[i]->send(_packet);
	}
}

CardPacket Server::receive(int i)
{
	CardPacket temp;

	if(_selector.wait())
	{
		if(_selector.isReady(*_clients[i]))
		{
			_packet.clear();
			if(_clients[i]->receive(_packet) == sf::Socket::Done)
			{
				_packet>>temp;
			}
			else
				_connectionOK = false;
		}
	}

	return temp;
}

void Server::giveTurn(int i)
{
	_packet.clear();
	_packetID = TURN;
	_packet<<_packetID;

	_clients[i]->send(_packet);
}

Server::~Server(void)
{
	for(std::vector<sf::TcpSocket*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete *it;
}