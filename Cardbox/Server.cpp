#include "Server.h"


Server::Server(void)
{
	_port = 2000;
	_UDPreceive.bind(_port);
	_UDPreceive.setBlocking(false);
	_UDPsend.setBlocking(false);
	_listener.listen(_port);
	_selector.add(_listener);
	_gameOn = false;
}

void Server::connectionPhase()
{
	if(_selector.wait(sf::seconds(0.01f)))
	{
		if(_selector.isReady(_listener))
		{	
			std::string id;
			sf::Uint16 clientUDPport;

			sf::TcpSocket* TCPsocket = new sf::TcpSocket;
			
			_listener.accept(*TCPsocket);
				
			_packet.clear();
			if(TCPsocket->receive(_packet) == sf::Socket::Done)
			{
				_packet>>id>>clientUDPport;
			}
			
			TCPsocket->setBlocking(false);

			sf::IpAddress ip = TCPsocket->getRemoteAddress();

			std::cout<<id<<" has connected to the session"<<std::endl;
			_interface.addPlayer(id,ip,clientUDPport);
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

void Server::receiveTCP()
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
				for(int j = 0; j < _clients.size(); j++)
				{
					_packet.clear();

					_packetID = START_GAME;

					sf::Uint16 playerIndex = j, playerCount = _clients.size();

					_packet<<_packetID<<playerIndex<<playerCount;

					_clients[j]->send(_packet);
				}
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

void Server::receiveUDP()
{
	/*if(_receiveTimer.getElapsedTime().asSeconds()>0.01f)
	{*/
	for(int i = 0; i < _clients.size(); i++)
	{
	_packet.clear();

	_packetID = EMPTY;

	if(_UDPreceive.receive(_packet, _clients[i]->getRemoteAddress(), _port) != sf::Socket::Done)
	{
	//	std::cout<<"Server UDP didn't receive sheet"<<std::endl;
	}

	_packet>>_packetID;

		switch(_packetID)
		{
		case EMPTY:
			break;
		case MOVE_SHIT:
			sf::Uint16 playerIndex, tempx, tempy;
			_packet>>playerIndex>>tempx>>tempy;
			//std::cout<<"SERVER: "<<i<<". Mouse X: "<<tempx<<" Y: "<<tempy<<std::endl;
			for(int j = 0; j < _clients.size(); j++)
			{
				if(j != playerIndex)
				{
					_packet.clear();
					_packetID = MOVE_SHIT;
					_packet<<_packetID<<playerIndex<<tempx<<tempy;
					sendUDP(j, _packet);
				}
			}
			_sendTimer.restart();
			break;
		}
	}
	/*_receiveTimer.restart();
	}*/
}

void Server::sendUDP(int clientIndex, sf::Packet packet)
{
	if(_sendTimer.getElapsedTime().asMilliseconds()>5)
		_UDPsend.send(packet,_interface.getPlayer(clientIndex).IP, _interface.getPlayer(clientIndex).UDPport);
}

void Server::update()
{
	if(!_gameOn)
		connectionPhase();

	receiveTCP();
	receiveUDP();
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