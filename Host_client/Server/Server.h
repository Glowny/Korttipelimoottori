#pragma once
#include "SFML\Network.hpp"
#include "Dealer.h"
#include "Player.h"

enum PACKET_ID
{
	WAIT,
	GAME_START,
	CARD_PLAY,
	TABLE_UPDATE,
	TURN_UPDATE,
};

class Server
{
public:
	Server(void);
	~Server(void);
	void initialize();
	void setUp(int startingHand);
	void run();
	void reset();
private:
	sf::Uint16 _playerCount;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	Dealer _dealer;
	std::vector<sf::TcpSocket*> _clients;
	std::vector<Player> _players;
	sf::Uint16 _packetID;
	sf::Packet _packet;
	int _port;
	int _startingHand;
};