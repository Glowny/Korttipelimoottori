#pragma once
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include "Enums.h"
#include <time.h>

class Client
{
public:
	Client(void);
	~Client(void);
	void run();
	void connect(sf::IpAddress ip, int port, std::string id);
	void sendPos();
	void receiveTCP();
	void receiveUDP();
	void initPlayers();
	void checkInput();
	void draw();

private:
	void smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos);
	std::vector<sf::Vector2f> otherPlayersMousePos;
	sf::TcpSocket TCPsocket;
	sf::UdpSocket UDPreceive, UDPsend;
	sf::IpAddress serverIP;
	unsigned short serverPort;
	sf::Packet packet;
	sf::Uint16 packetID;
	sf::Uint16 playerCount;
	sf::Uint16 posX, posY;
	sf::RenderWindow window;
	sf::Clock _sendTimer;
	sf::Uint16 ownIndex;
	bool gameOn;
	std::vector<sf::RectangleShape> shapes;
	sf::Clock deltaClock;
	float deltaTime;
};