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
	bool checkInput();
	void initialize();
	void receiver();
	int _port;
	sf::RectangleShape _palikka;
	std::vector<int>_selections;
	sf::IpAddress _ip;
	std::string _id, _currentPlayer;
	sf::Packet _packet;
	sf::Uint16 _packetID;
	sf::TcpSocket _socket;
	sf::RenderWindow &_window;
	StartScreen _startScreen;
	sf::Uint16 _playerCount;
	Table _table;
	Hand _hand, _tempHand;
	sf::Clock _jumitusClock;
};