#pragma once
#include <iostream>
#include <algorithm>
#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "Interface.h"
#include "Enums.h"
#include "DialogueWindow.h"

class Server
{
public:
	Server(void);
	~Server(void);
	void connectionPhase();
	void dialoguePhase();
	void reset();
	void receiveTCP();
	void receiveUDP();
	void sendUDP(int clientIndex, sf::Packet packet);
	void update();
	void run();

private:
	PHASE _currentPhase;
	Interface _interface;
	unsigned short _port;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	std::vector<sf::TcpSocket*> _clients;
	sf::UdpSocket _UDPreceive, _UDPsend;
	sf::Packet _packet;
	sf::Uint16 _packetID;
	bool _gameOn;
	sf::Clock _receiveTimer, _sendTimer;
	std::vector<sf::Color> _playerColors;
	DialogueWindow* dWindow;
};