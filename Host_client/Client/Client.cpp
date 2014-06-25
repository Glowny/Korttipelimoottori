#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window), _UI(window)
{
	_font = new sf::Font;
	_window.setActive(false);
	_window.setVisible(false);
	_font->loadFromFile("comic.ttf");

	_port = 2000;

	_startScreen.run();

	switch(_startScreen.getOption())
	{
	case EDITOR:
		//_editor.setFont(*_font);
		_editor.initialize();
		_editor.run();
		break;
	case PLAY:
		initialize();
		run();

	case HOST:
		break;
	}

}

void Client::initialize()
{	
	_socket.setBlocking(false);

	_ip = _startScreen.getIp();
	_id = _startScreen.getID();

	std::cout<<_ip.toString()<<std::endl;


	_window.setActive(true);
	_window.setVisible(true);

	_window.setTitle(_id);

	_table.addPlayer(_id);

	_socket.connect(_ip, _port);

	_packet<<_id;

	_socket.send(_packet);

	_packet.clear();
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
		case GAME_START:
			sf::Uint16 _mptype;

			_packet>>_tempHand>>_mptype>>_playerCount;

			for(int i = 0; i < _playerCount; i++)
			{
				std::string tempText;
				_packet>>tempText;
				std::cout<<tempText<<" joined"<<std::endl;
				if(tempText.size() > 0)
				_table.addPlayer(tempText);
			}
			_UI.setMultiplayType(_mptype);

			_UI.addCards(_tempHand);

			std::cout<<"Your hand:"<<std::endl;

			for(int i=0; i<_tempHand.hand.size(); i++)
			{
				std::cout<<_tempHand.hand[i].suit<<" "<<_tempHand.hand[i].value<<std::endl;
			}
			break;

			//Pelataan vuoro ja lähetetään pelatut kortit.
		case CARD_PLAY:

			sf::Uint16 allowedAreasCount, cardLimit;

			_packet>>allowedAreasCount;

			for(int i = 0; i < allowedAreasCount; i++)
			{
				sf::Uint16 tempArea;
				_packet>>tempArea;
				allowedAreas.push_back(tempArea);
			}

			_UI.setAllowedAreas(allowedAreas);

			_packet>>cardLimit;

			_UI.setCardLimit(cardLimit);

			_tempHand.hand.clear();

			_packet>>_tempHand;

			_UI.setPlayableCards(_tempHand);

			_tempHand.hand.clear();

			while(!_UI.checkInput())
			{
				draw();

			}
			_tempHand = _UI.getSelected();

			_UI.removeCards(_tempHand);

			_currentArea = NOTHING;

			_currentArea = _UI.getSelectedArea();

			_packet.clear();

			_packet<<_currentArea<<_tempHand;

			_socket.send(_packet);
			if(_currentArea == SECONDARY_CARDS)
				_table.addToTable(_id, _tempHand);
			else if(_currentArea == TABLE_CENTER)
				_table.addToTable("", _tempHand);

			break;

			//Otetaan vastaan toisen pelaajan pelatut kortit.
		case TABLE_UPDATE:
			_tempHand.hand.clear();

			_currentArea = NOTHING;

			_packet>>_currentArea>>_tempHand;

			if(_tempHand.hand.size()>0)
				std::cout<<_currentPlayer<<" plays: "<<_tempHand.hand[0].suit<<" "<<_tempHand.hand[0].value<<std::endl;
			if(_currentArea == SECONDARY_CARDS)
				_table.addToTable(_currentPlayer, _tempHand);
			else if(_currentArea == TABLE_CENTER)
				_table.addToTable("",_tempHand);

			break;

			//Saadaan tieto kenen (toisen pelaajan) vuoro on.
		case TURN_UPDATE:
			_currentPlayer.clear();

			_packet>>_currentPlayer;
			
			std::cout<<_currentPlayer<<" turn"<<std::endl;

			break;

			//Saadan tieto voittajasta sekä halutut viestit
		case END:
			std::string temp1,temp2;

			bool victory;

			_packet>>temp1>>temp2;

			if(temp1 == _id)
				victory = true;
			else
				victory = false;

			_UI.endScreen(temp1,temp2,victory);

			break;
		}
}

Client::~Client(void)
{
}
