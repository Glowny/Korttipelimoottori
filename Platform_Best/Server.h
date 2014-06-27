#pragma once
#include "SFML\Network.hpp"
#include "CardPacket.h"

enum PACKET_ID
{
	WAIT,
	START,
	ADD_CARDS,
	SET_CARDS,
	MESSAGE,
	TURN,
};

class Server
{
public:
	Server(void);
	~Server(void);
	std::vector<std::string> initialize(int playercount);
	void reset();
	void send(std::string message);
	void send(CardPacket cards);
	void send(int i, CardPacket cards);
	void send(int i, std::string message);
	void send(int i, int areas, Hand cards, std::vector<std::string> playerIDs, std::vector<sf::Uint16> cardAmounts);
	void sendReplacement(CardPacket cards);
	void giveTurn(int i);
	CardPacket receive(int i);
	bool checkConnection(){return _connectionOK;}
private:
	int _port;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	std::vector<sf::TcpSocket*> _clients;
	sf::Packet _packet;
	sf::Uint16 _packetID;
	bool _connectionOK;
};