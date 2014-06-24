#pragma once
#include "SFML\Network.hpp"
#include "CardPacket.h"

enum PACKET_ID
{
	WAIT,
	CARDS,
	MESSAGE,
	TURN,
};

class Server
{
public:
	Server(void);
	~Server(void);
	std::vector<std::string> initialize(int playercount);
	std::vector<std::string> reset(int playercount);
	void send(std::string message);
	void send(CardPacket cards);
	void send(int i, CardPacket cards);
	void send(int i, std::string message);
	void giveTurn(int i);
	CardPacket receive(int i);
private:
	int _port;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	std::vector<sf::TcpSocket*> _clients;
	sf::Packet _packet;
	sf::Uint16 _packetID;
};