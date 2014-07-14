#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
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
	void sendStartPacket(int clienIndex);
	void sendUDP(int clientIndex, sf::Packet packet);
	void receiveImageFile(std::string filename, int clientIndex, sf::Uint16 amount,sf::Uint16 x,sf::Uint16 y);
	void writeImageFile(std::string filename, std::string data,  std::fstream* output);
	void update();
	void run();
	void sendImageFile(std::string filename, int index);

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
	sf::Clock _receiveTimer, _sendTimer;
	std::vector<sf::Color> _playerColors;
	std::string tempFileName;
	int totalCards;
	sf::Uint16 tempCardSizeY;
	sf::Uint16 tempCardSizeX;
	sf::Uint16 tempCardAmount;
	//DialogueWindow* _dWindow;
};