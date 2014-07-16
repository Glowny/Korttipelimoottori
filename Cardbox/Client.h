#pragma once
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include "Enums.h"
#include "DialogueView.h"
#include "CardObject.h"
#include <time.h>
#include <fstream>

class Client
{
public:
	Client(void);
	~Client(void);
	void connectionPhase();
	void handleStartPacket();
	void dialoguePhase();
	void gamePhase();
	void run();
	void connect(sf::IpAddress ip, int port, std::string id);
	void sendUDP();
	void receiveTCP();
	void receiveUDP();
	void initPlayers();
	void checkInput();
	void sendImageFile(std::string filename);
	void receiveImageFile(std::string filename, sf::Uint16 amount,sf::Uint16 x,sf::Uint16 y);
	void writeImageFile(std::string filename, std::string data, std::fstream* output);
	void makeDeck(std::string filename,int cardAmount, sf::Vector2f cardSize);
	void draw();
	void checkRoll(sf::Vector2i mousepos, int delta);
	sf::Uint16 checkClick(sf::Vector2i mousepos);
	void zoomzoom(int delta);
	void correctView(sf::Vector2f viewSize);
	void putCardOnTop(int cardID);
	void checkCardOwnage(int cardID);
	

private:
	sf::Clock scaleTimer;
	void scaleCardsNormal();
	void smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos);
	void moveCard(sf::Uint16 playerID, sf::Uint16 cardID);
	std::vector<sf::Vector2f> otherPlayersMousePos;
	std::vector<sf::Vector2f> otherPlayersMouseDist;
	sf::TcpSocket TCPsocket;
	sf::UdpSocket UDPreceive, UDPsend;
	sf::IpAddress serverIP;
	std::vector<std::string>playerNames;
	unsigned short serverPort;
	sf::Packet packet;
	sf::Uint16 packetID;
	sf::Uint16 playerCount;
	sf::Uint16 posX, posY;
	sf::RenderWindow window;
	sf::Clock _sendTimer;
	sf::Uint16 ownIndex;
	std::vector<sf::RectangleShape> shapes;
	sf::Time deltaTime_time;
	sf::Clock deltaClock;
	float deltaTime;
	std::vector<sf::Color>playerColors;
	std::string ownName;
	std::string fileName;
	sf::Uint16 cardAmount;
	sf::Uint16 cardSizeY;
	sf::Uint16 cardSizeX;
	PHASE currentPhase;
	std::vector<CardObject>cards;
	sf::Uint16 pickedCard;
	sf::Vector2f distance;
	bool cardPicked;
	std::vector<int> pickers;
	std::vector<int> pickings;
	int lastScaled;
	//DialogueView* dView;
};