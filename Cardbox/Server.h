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
	void receiveImageFile(std::string filename, int clientIndex, sf::Int16 amount,sf::Int16 x,sf::Int16 y);
	void writeImageFile(std::string filename, std::string data,  std::fstream* output);
	bool checkFileExistence(std::string filename);
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
	sf::Int16 _packetID;
	sf::Clock _receiveTimer, _sendTimer;
	std::vector<sf::Color> _playerColors;
	std::string tempFileName;
	int totalCards;
	sf::Int16 tempCardSizeY;
	sf::Int16 tempCardSizeX;
	sf::Int16 tempCardAmount;
	int _theSeed;
	//DialogueWindow* _dWindow;
};