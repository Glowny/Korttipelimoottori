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
	END,
};

enum SELECTION_AREA
{
	NOTHING,
	TABLE_CENTER,
	SECONDARY_CARDS,
};

enum MULTIPLAY_TYPE
{
	NO_MULTIPLAY,
	SAME_VALUE,
	SAME_SUIT,
};

class Server
{
public:
	Server(void);
	~Server(void);
	void initialize(int playercount);
	void setUp(int startingHand);
	void run();
	void reset();
	Card getTopCard(SELECTION_AREA area);
	Hand getPlayerHand(int playerNumber){return _players[playerNumber].getHand();}
	void setPlayableCards(SELECTION_AREA area, int cardlimit, Hand cards);
	void setMultiplayType(MULTIPLAY_TYPE type){_mptype = type;}
	void winner();
	void winner(std::string customMessage);
	std::vector<Player> getPlayers(){return _players;}
	Player getCurrentPlayer(){return _currentPlayer;}
private:
	sf::Uint16 _playerCount;
	sf::TcpListener _listener;
	sf::SocketSelector _selector;
	Dealer _dealer;
	std::vector<sf::TcpSocket*> _clients;
	std::vector<Player> _players;
	Player _currentPlayer;
	std::vector<PlayArea> _playAreas;
	std::vector<int> _allowedAreas;
	sf::Uint16 _cardLimit;
	Hand _tempHand;
	sf::Uint16 _packetID;
	sf::Packet _packet;
	int _port;
	int _startingHand;
	int _mptype;
};