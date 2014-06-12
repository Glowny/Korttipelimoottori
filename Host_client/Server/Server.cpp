#include "Server.h"


Server::Server(void)
{
	_port = 2000;
	_listener.listen(_port);
	_selector.add(_listener);

}


void Server::initialize()
{
	std::cout << "Initializing server.." << std::endl;
	int connections = 0;
	std::cout<<"Enter the number of players: ";
	std::cin>>_playerCount;
	
	std::cout << "Waiting for connections.." <<std::endl;
	while(connections < _playerCount)
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

				_players.push_back(Player(id));
				std::cout<<id<<" has connected to the session"<<std::endl;
				_clients.push_back(socket);
				_selector.add(*socket);

				connections++;
			}
		}
	}

}

void Server::setUp(int startingHand)
{
		std::cout << "Running setup.." << std::endl;
		_dealer.shuffle();

		for(int i = 0; i < _clients.size(); i++)
		{
			_players[i].setHand(_dealer.deal(startingHand));
			_packetID = 1;
			sf::Uint16 otherPlayers = _playerCount-1;

			_packet.clear();
			_packet<<_packetID<<_players[i].getHand()<<otherPlayers;


			//L‰hetet‰‰n toisten pelaajien IDt pelaajille
			for(int j = 0; j < _playerCount; j++)
			{
				if(i != j)
					_packet<<_players[j].getID();
			}

			//L‰hetet‰‰n pelaajalle paketti jossa pelaajan k‰si, muiden pelaajien lkm ja
			//muiden pelaajien IDt
			_clients[i]->send(_packet);
		}
}

void Server::run()
{
	for(int i = 0; i < _clients.size();)
		{
			//L‰hetet‰‰n pelaajalle, jonka vuoro on, ett‰ sun vuoro on
			_packet.clear();
			_packetID = 2;
			_packet<<_packetID;
			_clients[i]->send(_packet);

			//L‰hetet‰‰n muille, joiden vuoro ei ole, ett‰ sun vuoro ei ole
			//ja ett‰ kenen vuoro se nyt on
			_packet.clear();
			_packetID = 4;
			_packet<<_packetID<<_players[i].getID();

			for(int j = 0; j < _clients.size(); j++)
			{
				if(i != j)
					_clients[j]->send(_packet);
			}
				
			std::cout<<_players[i].getID()<<" turn"<<std::endl;


			//Venaa sit‰ kenen vuoro on, ett‰ tulee kamaa rˆˆriin
			if(_selector.wait())
			{
				if(_selector.isReady(*_clients[i]))
				{
					_packet.clear();
					if(_clients[i]->receive(_packet) == sf::Socket::Done)
					{
						//otetaan vastaan pelatut kortit pelaajalta
						std::cout<<"Received packet from "<<_players[i].getID()<<std::endl;
						Hand receivedHand;
						_packet >> receivedHand;
								
						//l‰hetet‰‰n muille pelaajille pelaajan x pelatut kortit
						_packet.clear();
						_packetID = 3;
						_packet << _packetID << receivedHand;
						for(int j = 0; j < _clients.size(); j++)
						{
							if(i != j)
								_clients[j]->send(_packet);
						}

						i++;
					}
				}
			}
		}
}


Server::~Server(void)
{
	for(std::vector<sf::TcpSocket*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete *it;
}
