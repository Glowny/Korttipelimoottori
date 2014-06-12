#pragma once
#include "Hand.h"
#include "Card.h"
#include "Table.h"
#include "StartScreen.h"
#include <string>
#include <iostream>
#include <vector>

class Client
{
public:
	Client(sf::RenderWindow &window);
	~Client(void);
	void run();

private:
	void draw();
	void initialize();
	void receiver();
	int _port;
	sf::IpAddress _ip;
	std::string _id, _currentPlayer;
	sf::Packet _packet;
	sf::Uint16 _packetID;
	sf::TcpSocket _socket;
	sf::RenderWindow &_window;
	StartScreen _startScreen;
	int _playerCount;
	Table _table;
	Hand _hand, _tempHand;
};