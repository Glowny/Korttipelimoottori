#pragma once
#include "CardPacket.h"
#include "Table.h"
#include "StartScreen.h"
#include "UserInterface.h"
#include "Editor.h"
#include "SoundManager.h"
#include <string>
#include <iostream>
#include <vector>

enum PACKET_ID
{
	WAIT,
	START,
	ADD_CARDS,
	REMOVE_CARDS,
	SET_CARDS,
	MESSAGE,
	TURN,
	RULES,
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
	std::string _id;
	sf::Packet _packet;
	sf::Uint16 _packetID, _currentArea;
	sf::TcpSocket _socket;
	sf::RenderWindow &_window;
	StartScreen _startScreen;
	sf::Uint16 _playerCount;
	Table _table;
	CardPacket _tempCardPacket;
	Hand _tempHand;
	UserInterface _UI;
	Editor _editor;
	std::vector<int> _cardAmounts;
	sf::Uint16 _currentPlayerIndex;
	sf::Uint16 _ownIndex;
	std::vector<std::string> _playerIDs;
	std::string _rulesData;
};