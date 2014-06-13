#include "Client.h"


Client::Client(sf::RenderWindow &window) : _window(window), _table(window)
{
	_window.setActive(false);
	_window.setVisible(false);

	_port = 2000;
	initialize();
	_palikka.setSize(sf::Vector2f(128,256));
	_palikka.setOrigin(_palikka.getSize().x*0.5f,_palikka.getSize().y*0.5f);
	_palikka.setPosition(_window.getSize().x*0.5f,_window.getSize().y*0.5f);
	_palikka.setFillColor(sf::Color::Magenta);
	
	
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
}

void Client::run()
{
	receiver();
	draw();
}

void Client::draw()
{
	_window.draw(_palikka);
	_table.drawTable();
	_window.display();
	_window.clear();
	
}

bool Client::checkInput()
{

	bool ready = false;
	sf::Event Event;
	while(_window.pollEvent(Event))
	{
		switch(Event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "something happens";
				for(int i = 0; i < _table.getCardRectangles(_id).size();i++)
				{
					if(_table.getCardRectangles(_id)[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
					{
						bool selected = false;
						for(int j = 0; j < _selections.size(); j++)
						{
							if(_selections[j] == i)
								selected = true;
						}
						if(!selected)
							{
								_selections.push_back(i);
								
							}

						if(_packetID == 2)
						_table.setRectColor(sf::Color::Yellow, i);
					
					}
				}

				if(_palikka.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
				{
					std::cout << "plaaksd";
					ready = true;
				}
			}
			draw();
			break;
			
		}
	}
	return ready;
}

void Client::receiver()
{
	_packet.clear();

	_socket.receive(_packet);
	
	_packetID = 0;
		
	_packet>>_packetID;

	checkInput();

	std::vector<Card> removables;

	switch (_packetID)
	{

	case 0:
		break;

			//Otetaan vastaan alkukäsi ja muut pelaajat.
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

			//Pelataan vuoro ja lähetetään pelatut kortit.
		case 2:

			_tempHand.hand.clear();

			_selections.clear();

			while(!checkInput())
			{
			
			}
			for(int i = 0; i < _selections.size();i++)
			{
			_tempHand.add(_hand.hand[_selections[i]]);
			std::cout << _tempHand.hand[i].suit << "  " <<_tempHand.hand[i].value << std::endl;
			}

			_packet.clear();

			_packet<<_tempHand;

			_socket.send(_packet);

			_table.removeFromTable(_id, _tempHand);


			for(int i = 0; i < _selections.size();i++)
			{
				removables.push_back(_hand.hand[_selections[i]]);
			}

			for(int i = 0; i < removables.size();i++)
			{
				for(int j = 0;j < _hand.hand.size();)
				{
					if(removables[i] == _hand.hand[j])
						_hand.hand.erase(_hand.hand.begin()+j);
					else
						j++;
				}
			}

			break;

			//Otetaan vastaan toisen pelaajan pelatut kortit.
		case 3:
			_tempHand.hand.clear();

			_packet>>_tempHand;

			if(_tempHand.hand.size()>0)
				std::cout<<_currentPlayer<<" plays: "<<_tempHand.hand[0].suit<<" "<<_tempHand.hand[0].value<<std::endl;

			_table.addToTable(_currentPlayer, _tempHand);

			break;

			//Saadaan tieto kenen (toisen pelaajan) vuoro on.
		case 4:
			_currentPlayer.clear();

			_packet>>_currentPlayer;
			
			std::cout<<_currentPlayer<<" turn"<<std::endl;

			break;
		}
}

Client::~Client(void)
{
}