#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window)
{
	_window.setActive(false);
	_window.setVisible(false);

	_port = 2000;
	initialize();
}

void Client::initialize()
{
	_startScreen.run();
	_ip = _startScreen.getIp();
	std::cout<<_ip.toString()<<std::endl;
	_id = _startScreen.getID();

	_table.addPlayer(_id);

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
	_table.drawTable();
	_window.display();
	_window.clear();
}

void Client::receiver()
{
	_packet.clear();
		
	_socket.receive(_packet);
		
	_packetID = 0;
		
	_packet>>_packetID;


	switch (_packetID)
	{

	case 0:
		break;

		case 1:
			_packet>>_hand>>_playerCount;

			for(int i = 0; i < _playerCount; i++)
			{
				std::string tempText;
				_packet>>tempText;
				std::cout<<tempText<<" joined"<<std::endl;
				_table.addPlayer(tempText);
			}


			_table.addToTable(_id,_hand);

			std::cout<<"Your hand:"<<std::endl;

			for(int i=0; i<_hand.hand.size(); i++)
			{
				std::cout<<_hand.hand[i].suit<<" "<<_hand.hand[i].value<<std::endl;
			}
			break;

		case 2:
			
			std::cout << "===========================" << std::endl;
			std::cout << "Valitse pelattava kortti" << std::endl;
			for (int i = 0; i < _hand.hand.size(); i++)
			{
				std::cout << i <<"="<< _hand.hand[i].value << std::endl;
			}
			std::cout << "===========================" << std::endl;
			int selection;
			std::cin >> selection;

			_tempHand.add(_hand.hand[selection]);

			_packet.clear();

			_packet<<_tempHand;

			_socket.send(_packet);

			_table.removeFromTable(_id, _tempHand);

			_hand.hand.erase(_hand.hand.begin()+selection);

			break;
		case 3:
			_tempHand.hand.clear();

			_packet.clear();

			_packet>>_tempHand;

			std::cout<<_currentPlayer<<" plays: "<<_tempHand.hand[0].suit<<" "<<_tempHand.hand[0].value<<std::endl;

			_table.addToTable(_currentPlayer, _tempHand);

			break;
		case 4:
			_currentPlayer.clear();
			_packet.clear();

			_packet>>_currentPlayer;
			
			if(_currentPlayer.size()>0)
			{
			std::cout<<_currentPlayer<<" turn"<<std::endl;
			}
			break;
		}
}

Client::~Client(void)
{
}