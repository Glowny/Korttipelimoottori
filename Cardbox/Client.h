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
	void sendMouse();
	void sendUDP();
	void receiveTCP();
	void receiveUDP();
	void initPlayers();
	void checkInput();
	void sendImageFile(std::string filename);
	void receiveImageFile(std::string filename, sf::Int16 amount,sf::Int16 x,sf::Int16 y);
	void writeImageFile(std::string filename, std::string data, std::fstream* output);
	void makeDeck(std::string filename,int cardAmount, sf::Vector2f cardSize);
	void draw();
	void checkRoll(sf::Vector2i mousepos, int delta);
	sf::Int16 checkClick(sf::Vector2i mousepos);
	void zoomzoom(int delta);
	void correctView(sf::Vector2f viewSize);
	void putCardOnTop(int cardID);
	void checkCardOwnage(int cardID);
	void rotateCard(int cardID);
	

private:
	std::vector<sf::RectangleShape>boundaries;
	sf::Clock clickTimer;
	bool checkBoundaries(CardObject card);
	void smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos);
	void moveCard(sf::Int16 playerID, sf::Int16 cardID);
	std::vector<sf::Vector2f> otherPlayersMousePos;
	std::vector<sf::Vector2f> otherPlayersMouseDist;
	sf::TcpSocket TCPsocket;
	sf::UdpSocket UDPreceive, UDPsend;
	sf::IpAddress serverIP;
	std::vector<std::string>playerNames;
	unsigned short serverPort;
	sf::Packet packet;
	sf::Int16 packetID;
	sf::Int16 playerCount;
	sf::Int16 posX, posY;
	sf::RenderWindow window;
	sf::Clock _sendTimer;
	sf::Int16 ownIndex;
	std::vector<sf::RectangleShape> shapes;
	sf::Time deltaTime_time;
	sf::Clock deltaClock;
	float deltaTime;
	std::vector<sf::Color>playerColors;
	std::string ownName;
	std::string fileName;
	sf::Int16 cardAmount;
	sf::Int16 cardSizeY;
	sf::Int16 cardSizeX;
	PHASE currentPhase;
	std::vector<CardObject>cards;
	sf::Int16 pickedCard;
	sf::Vector2f distance;
	bool cardPicked;
	std::vector<int> pickers;
	std::vector<int> pickings;
	int lastScaled;
	//DialogueView* dView;
};