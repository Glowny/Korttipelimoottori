#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window), _UI(window, _table)
{	
	//_font = new sf::Font;
	_window.setActive(false);
	_window.setVisible(false);
	//_font->loadFromFile("comic.ttf");

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
	
	std::cout<<_ip.toString()<<std::endl;
	_id = _startScreen.getID();
	_window.setTitle(_id);

	_socket.connect(_ip, _port);

	_packet<<_id;

	_socket.send(_packet);

	_packet.clear();
	_window.setActive(true);
	_window.setVisible(true);
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

			_currentPlayerIndex = 0;

			_tempHand.hand.clear();

			sf::Uint16 areasAmount;

			_packet>>areasAmount>>_tempHand>>_playerCount;

			for(int i = 0; i < _playerCount; i++)
			{
				std::string tempText;
				_packet>>tempText;
				std::cout<<tempText<<" joined"<<std::endl;
				if(tempText.size() > 0)
				_playerIDs.push_back(tempText);
			}

			sf::Uint16 cardAmountsSize;

			_packet>>cardAmountsSize;

			for(int i = 0; i < cardAmountsSize; i++)
			{
				sf::Uint16 temp;
				_packet>>temp;
				_cardAmounts.push_back(temp);
			}

			_packet>>_ownIndex;

			_table.setOwnIndex(_ownIndex);

			_table.setCardAmounts(_cardAmounts);

			_table.createAreas(areasAmount);

			_UI.init(_table.getAreas());

			_UI.addCards(_tempHand);

			std::cout<<"Your hand:"<<std::endl;

			for(int i=0; i<_tempHand.hand.size(); i++)
			{
				std::cout<<_tempHand.hand[i].suit<<" "<<_tempHand.hand[i].value<<std::endl;
			}

			std::cout<<"Tota cards: "<<_tempHand.hand.size()<<std::endl;

			_UI.gameStart();

			break;

			//Pelataan vuoro ja lähetetään pelatut kortit.
		case TURN:

			_UI.turnOn();

			_tempCardPacket._cards.hand.clear();

			_UI.popUp("Your turn",1);

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
		case ADD_CARDS:

			_tempCardPacket._cards.clear();

			_packet>>_tempCardPacket;

			if(_tempCardPacket._cards.size()>0)
			{
				std::cout<<_playerIDs[_currentPlayerIndex]<<" plays"<<std::endl;
				_table.addToTable(_tempCardPacket._area,_tempCardPacket._cards);
			}

			if(_currentPlayerIndex != _ownIndex)
				_table.removeFromHand(_currentPlayerIndex, _tempCardPacket._cards.size());

			_currentPlayerIndex++;
				if(_currentPlayerIndex == _playerCount)
					_currentPlayerIndex = 0;
			break;

			//Korvataan pelialueen kortit saaduilla
		case SET_CARDS:

			_tempCardPacket._cards.clear();

			_packet>>_tempCardPacket;

			_table.setToTable(_tempCardPacket._area,_tempCardPacket._cards);

			break;

		//Saadan viestiä
		case MESSAGE:

			std::string temp;

			_packet>>temp;

			_UI.popUp(temp,3);

			break;
		}
}

Client::~Client(void)
{
}