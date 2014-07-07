#include "Server.h"


Server::Server(void)
{
	_port = 2000;
	_listener.listen(_port);
	_selector.add(_listener);
	_gameOn = false;
}

void Server::connectionPhase()
{
	if(_selector.wait(sf::seconds(0.5f)))
	{
		if(_selector.isReady(_listener))
		{	
			std::string id;

			sf::TcpSocket* TCPsocket = new sf::TcpSocket;
			
			_listener.accept(*TCPsocket);
				
			_packet.clear();
			if(TCPsocket->receive(_packet) == sf::Socket::Done)
				_packet>>id;
			
			TCPsocket->setBlocking(false);

			sf::IpAddress ip = TCPsocket->getRemoteAddress();

			std::cout<<id<<" has connected to the session"<<std::endl;
			_interface.addPlayer(id,ip);
			_clients.push_back(TCPsocket);
			_selector.add(*TCPsocket);
			
		}
	}
}

void Server::reset()
{
	_packet.clear();
	_clients.clear();
	_selector.clear();
	_selector.add(_listener);
}

void Server::receive()
{
	for(int i = 0; i < _clients.size(); i++)
	{
		_packet.clear();

		_packetID = EMPTY;

		_clients[i]->receive(_packet);

		_packet>>_packetID;

		switch(_packetID)
		{
		case EMPTY:
			break;
		case START_GAME:
			_gameOn = true;
			break;
		case TURN_CARD:
			break;
		case PICK_UP_CARD:
			break;
		case RELEASE_CARD:
			break;
		case DRAW_FROM_DECK:
			break;
		case PUT_IN_DECK_TOP:
			break;
		case PUT_IN_DECK_BOT:
			break;
		case SHUFFLE:
			break;
		case MESSAGE:
			break;
		}
	}
}

void Server::update()
{
	if(!_gameOn)
		connectionPhase();

	receive();
}
void Server::run()
{
	while(true)
	{	
		update();
	}
}

Server::~Server(void)
{
	for(std::vector<sf::TcpSocket*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete *it;
}