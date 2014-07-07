#pragma once
#include <iostream>
#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "Interface.h"

enum PACKET_ID
{
	EMPTY,
	START_GAME,
	TURN_CARD,
	PICK_UP_CARD,
	RELEASE_CARD,
	DRAW_FROM_DECK,
	PUT_IN_DECK_TOP,
	PUT_IN_DECK_BOT,
	SHUFFLE,
	MESSAGE,
};

class Server
{
public:
	Server(void);
	~Server(void);
	void connectionPhase();
	void reset();
	void receive();
	void update();
	void run();

private:
	Interface _interface;
	int _port;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	std::vector<sf::TcpSocket*> _clients;
	sf::Packet _packet;
	sf::Uint16 _packetID;
	bool _gameOn;
};