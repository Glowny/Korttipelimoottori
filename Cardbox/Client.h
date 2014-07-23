#pragma once
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
#include "DeckMaker.h"
#include "Enums.h"
#include "DialogueView.h"
#include "CardObject.h"
#include "AssetLoader.h"
#include "ToolMenu.h"
#include "DeckMenu.h"
#include <time.h>
#include <fstream>
#include "DeckObject.h"

class Client
{
public:

	Client(AssetLoader *al);
	~Client(void);
	void run();
	void connect(sf::IpAddress ip, int port, std::string id);

private:

	void connectionPhase();
	void handleStartPacket();
	void downloadPhase();
	void gamePhase();
	void sendMouse();
	void receiveTCP();
	void initPlayers();
	void checkInput();
	void sendImageFile(std::string filename);
	void receiveImageFile(std::string filename, sf::Int16 amount,sf::Int16 x,sf::Int16 y);
	void writeImageFile(std::string filename, std::string data, std::fstream* output);
	void makeDeck(std::string filename,int cardAmount, sf::Vector2f cardSize);
	void draw();
	sf::Int16 checkClick(sf::Vector2i mousepos);
	void zoomzoom(int delta);
	void correctView(sf::Vector2f viewSize);
	void putCardOnTop(int cardID);
	void checkCardOwnage(int cardID);
	void rotateCard(int cardID);
	void toolMenu();
	void dropCard();
	void checkToolMenu();
	void checkDeckMenu();
	void checkHandAreas(int cardID);
	void makeHandArea(int playerIndex, sf::FloatRect floatRect);
	bool checkBoundaries(sf::FloatRect floatRect);
	void smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos);
	void moveCard(sf::Int16 playerID, sf::Int16 cardID);
	void checkGameInput(sf::Event Event);
	void checkDownloadInput(sf::Event Event);
	void checkConnectionInput(sf::Event Event);
	void areaTool(sf::Event Event);
	void arrangeDecks();
	void deckmaker();

	//ominaisuudet : DDd

	ToolMenu tools;
	AssetLoader *assLoad;
	PHASE currentPhase;
	DeckMenu deckMenu;
	DeckMaker deckMaker;
	
	sf::RectangleShape tempRect;
	sf::TcpSocket TCPsocket;
	sf::IpAddress serverIP;
	sf::Packet packet;
	sf::Int16 packetID,posX,posY,playerCount,ownIndex,cardAmount,cardSizeY,cardSizeX,pickedCard;
	sf::RenderWindow window;
	sf::Clock _sendTimer;
	sf::Time deltaTime_time;
	sf::Clock deltaClock;
	sf::Vector2f distance;
	sf::FloatRect windowRect;
	sf::Clock clickTimer;

	bool toolMenuOn,makingArea,cardPicked,drawMode,deckMenuOn;
	unsigned short serverPort;
	float deltaTime;

	std::string ownName,fileName;
	std::vector<DeckObject>decks;
	std::vector<CardObject>cards;
	std::vector<int> pickers,pickings;
	std::vector<sf::RectangleShape> shapes;
	std::vector<std::string>playerNames;
	std::vector<sf::Color>playerColors;
	std::vector<sf::RectangleShape>handAreas;
	std::vector<sf::Vector2f> otherPlayersMousePos, otherPlayersMouseDist;
};