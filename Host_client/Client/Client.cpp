#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window), _UI(window)
{
	_window.setActive(false);
	_window.setVisible(false);

	_port = 2000;
	initialize();
}

void Client::initialize()
{
	_socket.setBlocking(false);
	_startScreen.run();
	_ip = _startScreen.getIp();
	
	std::cout<<_ip.toString()<<std::endl;
	_id = _startScreen.getID();
	_window.setTitle(_id);

	_table.addPlayer(_id);

	_socket.connect(_ip, _port);

	_packet<<_id;

	_socket.send(_packet);

	_packet.clear();
	_window.setActive(true);
	_window.setVisible(true);
	_UI.addButton("End Turn");
}

void Client::run()
{
	receiver();
	draw();
}

void Client::draw()
{	
	_window.clear();
	_table.drawTable();
	_UI.draw();
	_window.display();
	
	
}

void Client::receiver()
{
	_packet.clear();

	_socket.receive(_packet);
	
	_packetID = WAIT;

	_packet>>_packetID;

	_UI.checkInput();

	switch (_packetID)
	{

	case WAIT:
		break;

			//Otetaan vastaan alkukäsi ja muut pelaajat.
		case GAME_START:
			_packet>>_tempHand>>_playerCount;

			for(int i = 0; i < _playerCount; i++)
			{
				std::string tempText;
				_packet>>tempText;
				std::cout<<tempText<<" joined"<<std::endl;
				if(tempText.size() > 0)
				_table.addPlayer(tempText);
			}

			_UI.addCards(_tempHand);

			std::cout<<"Your hand:"<<std::endl;

			for(int i=0; i<_tempHand.hand.size(); i++)
			{
				std::cout<<_tempHand.hand[i].suit<<" "<<_tempHand.hand[i].value<<std::endl;
			}
			break;

			//Pelataan vuoro ja lähetetään pelatut kortit.
		case CARD_PLAY:

			_tempHand.hand.clear();

			while(!_UI.checkInput())
			{
				draw();

			}
			_tempHand = _UI.getSelected();

			_packet.clear();

			_packet<<_tempHand;

			_socket.send(_packet);

			_table.addToTable(_id, _tempHand);

			break;

			//Otetaan vastaan toisen pelaajan pelatut kortit.
		case TABLE_UPDATE:
			_tempHand.hand.clear();

			_packet>>_tempHand;

			if(_tempHand.hand.size()>0)
				std::cout<<_currentPlayer<<" plays: "<<_tempHand.hand[0].suit<<" "<<_tempHand.hand[0].value<<std::endl;

			_table.addToTable(_currentPlayer, _tempHand);

			break;

			//Saadaan tieto kenen (toisen pelaajan) vuoro on.
		case TURN_UPDATE:
			_currentPlayer.clear();

			_packet>>_currentPlayer;
			
			std::cout<<_currentPlayer<<" turn"<<std::endl;

			break;
		}
}

Client::~Client(void)
{
}