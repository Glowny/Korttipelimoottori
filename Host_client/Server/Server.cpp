#include "Server.h"


Server::Server(void)
{
	_port = 2000;
	_listener.listen(_port);
	_selector.add(_listener);
	_mptype = NO_MULTIPLAY;
}

void Server::initialize(int playercount)
{
	std::cout << "Initializing server.." << std::endl;
	int connections = 0;
	_playerCount = playercount;
	
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
	for(int i = 0; i <= _playerCount; i++)
	{
		_playAreas.push_back(PlayArea());
	}

}

void Server::reset()
{
	_packet.clear();
	_clients.clear();
	_players.clear();
	_dealer.initialize();
	_selector.clear();
	_selector.add(_listener);

	int connections = 0;

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
	setUp(_startingHand);
}

void Server::setUp(int startingHand)
{
		_startingHand = startingHand;
		std::cout << "Running setup.." << std::endl;
		_dealer.shuffle();

		for(int i = 0; i < _clients.size(); i++)
		{
			_players[i].setHand(_dealer.deal(startingHand));
			_packetID = GAME_START;
			sf::Uint16 otherPlayers = _playerCount-1, mptype = _mptype;

			_packet.clear();
			_packet<<_packetID<<_players[i].getHand()<<mptype<<otherPlayers;


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
		_currentPlayer = _players[0];
}

void Server::run()
{
	for(int i = 0; i < _clients.size();)
		{
			//L‰hetet‰‰n pelaajalle, jonka vuoro on, ett‰ sun vuoro on, sek‰ sallitut pelialueet ja kortit joita on mahdollista pelata ja pelattavien korttien m‰‰r‰
			_packet.clear();
			_packetID = CARD_PLAY;
			_packet<<_packetID;

			sf::Uint16 allowedAreasAmount = _allowedAreas.size();

			_packet<<allowedAreasAmount;
			

			for(int i = 0; i < _allowedAreas.size(); i++)
			{
				sf::Uint16 tempArea = _allowedAreas[i];
				_packet<<tempArea;
			}

			_packet<<_cardLimit<<_tempHand;

			_clients[i]->send(_packet);
			_currentPlayer = _players[i];

			//L‰hetet‰‰n muille, joiden vuoro ei ole, ett‰ sun vuoro ei ole
			//ja ett‰ kenen vuoro se nyt on
			_packet.clear();
			_packetID = TURN_UPDATE;
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
						std::cout<<"Received packet from "<<_players[i].getID()<<" --- ";
						Hand receivedHand;
						sf::Uint16 area;
						_packet >> area >> receivedHand;

						_players[i].removeCards(receivedHand);
						if(area == SECONDARY_CARDS)
						{
							_playAreas[i].addCards(receivedHand);
							std::cout<<"Added to the player's SECONDARY_CARDS:"<<std::endl;
						}
						else if(area == TABLE_CENTER)
						{
							_playAreas[_playerCount].addCards(receivedHand);
							std::cout<<"Added to TABLE_PILE:"<<std::endl;
						}

						for(int i=0; i<receivedHand.hand.size(); i++)
						{
							std::cout<<receivedHand.hand[i].suit<<" "<<receivedHand.hand[i].value<<std::endl;
						}

								
						//l‰hetet‰‰n muille pelaajille pelaajan x pelatut kortit
						_packet.clear();
						_packetID = TABLE_UPDATE;
						_packet << _packetID << area << receivedHand;
						for(int j = 0; j < _clients.size(); j++)
						{
							if(i != j)
								_clients[j]->send(_packet);
						}

						i++;
					}
					else
					reset();
				}
		
			}
			
		}
}

Card Server::getTopCard(SELECTION_AREA area)
{
	if(area == TABLE_CENTER)
		return _playAreas[_playerCount].getTopCard();
	else if(area == SECONDARY_CARDS)
	{
		for(int i = 0; i < _playerCount; i++)
		{
			if(_players[i] == _currentPlayer)
				return _playAreas[i].getTopCard();
		}

	}
		
}

void Server::setPlayableCards(SELECTION_AREA area, int cardlimit, Hand cards)
{
	_allowedAreas.push_back(area);
	_cardLimit = cardlimit;
	_tempHand.hand.clear();
	_tempHand = cards;
}

void Server::winner()
{
	_packet.clear();

	_packetID = END;

	std::string message = ":D:D:D:D::DDDD";

	_packet<<_packetID<<_currentPlayer.getID()<<message;

	for(int i = 0; i < _clients.size(); i++)
		{
			_clients[i]->send(_packet);
		}
}


Server::~Server(void)
{
	for(std::vector<sf::TcpSocket*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete *it;
}