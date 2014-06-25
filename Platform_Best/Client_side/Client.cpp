#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window), _UI(window, _table)
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

	_socket.connect(_ip, _port);

	_packet<<_id;

	_socket.send(_packet);

	_packet.clear();
	_window.setActive(true);
	_window.setVisible(true);
	_UI.addButton("End Turn");
	_UI.init(_table.getAreas());
}

void Client::run()
{
	receiver();
	draw();
}

void Client::draw()
{	
	_window.clear(sf::Color(0,100,0,255));
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

	std::vector<int> allowedAreas;

	switch (_packetID)
	{

	case WAIT:
		break;

			//Otetaan vastaan alkukäsi ja muut pelaajat.
		case START:

			_tempHand.hand.clear();

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

			std::cout<<"Tota cards: "<<_tempHand.hand.size()<<std::endl;
			break;

			//Pelataan vuoro ja lähetetään pelatut kortit.
		case TURN:

			_tempCardPacket._cards.hand.clear();

			while(!_UI.checkInput())
			{
				draw();

			}
			_tempCardPacket._cards = _UI.getSelected();

			_UI.removeCards(_tempCardPacket._cards);

			_tempCardPacket._area = NOTHING;

			_tempCardPacket._area = _UI.getSelectedArea();

			_packet.clear();

			_packet<<_tempCardPacket;

			_socket.send(_packet);

			break;

			//Otetaan vastaan toisen pelaajan pelatut kortit.
		case CARDS:
			_tempCardPacket._cards.hand.clear();

			_packet>>_tempCardPacket;

			if(_tempCardPacket._cards.hand.size()>0)
			{
				std::cout<<_currentPlayer<<" plays: "<<_tempCardPacket._cards.hand[0].suit<<" "<<_tempCardPacket._cards.hand[0].value<<std::endl;
				if(_tempCardPacket._area == TABLE_CENTER)
					_table.addToTable("",_tempCardPacket._cards);
				else
					_table.addToTable(_table.getPlayers()[0], _tempCardPacket._cards);
			}

			break;

		//	//Saadaan tieto kenen (toisen pelaajan) vuoro on.
		//case TURN_UPDATE:
		//	_currentPlayer.clear();

		//	_packet>>_currentPlayer;
		//	
		//	std::cout<<_currentPlayer<<" turn"<<std::endl;

		//	break;

		//	//Saadan tieto voittajasta sekä halutut viestit
		//case END:
		//	std::string temp1,temp2;

		//	bool victory;

		//	_packet>>temp1>>temp2;

		//	if(temp1 == _id)
		//		victory = true;
		//	else
		//		victory = false;

		//	_UI.endScreen(temp1,temp2,victory);

		//	break;
		}
}

Client::~Client(void)
{
}