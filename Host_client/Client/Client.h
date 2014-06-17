#pragma once
#include "Hand.h"
#include "Card.h"
#include "Table.h"
#include "StartScreen.h"
#include "UserInterface.h"
#include <string>
#include <iostream>
#include <vector>

enum PACKET_ID
{
	WAIT,
	GAME_START,
	CARD_PLAY,
	TABLE_UPDATE,
	TURN_UPDATE,
};

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
	sf::Uint16 _packetID, _currentArea;
	sf::TcpSocket _socket;
	sf::RenderWindow &_window;
	StartScreen _startScreen;
	sf::Uint16 _playerCount;
	Table _table;
	Hand _tempHand;
	UserInterface _UI;
};