#include "Server.h"


Server::Server(void)
{
	//_dWindow = new DialogueWindow();
	//_dWindow->hide();
	int totalCards = 0;
	_port = 2000;
	_UDPreceive.bind(_port);
	_UDPreceive.setBlocking(false);
	_UDPsend.setBlocking(false);
	_listener.listen(_port);
	_selector.add(_listener);

	_theSeed = time(NULL);
	std::srand(_theSeed);

	_currentPhase = CONNECTIONS;

	for(int i = 0; i < 7;i++)
	{
		_playerColors.push_back(sf::Color(i*32,255,i*32,255));
	}

	for(int i = 0; i < 7;i++)
	{
		_playerColors.push_back(sf::Color(255,i*32,i*32,255));
	}

	for(int i = 0; i < 7;i++)
	{
		_playerColors.push_back(sf::Color(i*32,i*32,255,255));
	}

	std::random_shuffle(_playerColors.begin(), _playerColors.end());
}

void Server::connectionPhase()
{
	if(_selector.wait(sf::seconds(0.01f)))
	{
		if(_selector.isReady(_listener))
		{	
			std::string id;
			sf::Int16 clientUDPport;

			sf::TcpSocket* TCPsocket = new sf::TcpSocket;
			
			_listener.accept(*TCPsocket);
				
			_packet.clear();
			if(TCPsocket->receive(_packet) == sf::Socket::Done)
			{
				_packet>>id>>clientUDPport;
			}
			
			TCPsocket->setBlocking(false);

			sf::IpAddress ip = TCPsocket->getRemoteAddress();

			std::cout<<id<<" has connected to the session";
			std::cout<<" with ip: "<<ip.toString()<<" & port: "<<clientUDPport<<std::endl;
			_interface.addPlayer(id,ip,clientUDPport);
			_clients.push_back(TCPsocket);
			_selector.add(*TCPsocket);
			
		}
	}

	for(int i = 0; i < _clients.size(); i++)
	{
	_packet.clear();

	_packetID = EMPTY;

	_clients[i]->receive(_packet);

	_packet>>_packetID;

	switch(_packetID)
	{
	case EMPTY:
		break;
	case CONTINUE:

		for(int j = 0; j < _clients.size(); j++)
		{
			sendStartPacket(j);

			_packet.clear();
			_packetID = CONTINUE;
			_packet<<_packetID;
			_clients[j]->send(_packet);
			std::cout<<"Sending continue to "<<_interface.getPlayer(j).ID<<std::endl;
		}

		_currentPhase = DOWNLOADS;

		std::cout<<"Server going to downloadsPhase"<<std::endl;

		//_dWindow->show();
		break;
	}
	}
}

void Server::dialoguePhase()
{
	//k‰yd‰‰n dialogia

	for(int i = 0; i < _clients.size(); i++)
	{
		_packet.clear();

		_packetID = EMPTY;

		_clients[i]->receive(_packet);

		_packet>>_packetID;

		sf::Int16 playerIndex = i;
		//int state = -1;

		switch(_packetID)
		{
		case EMPTY:

			/*state = _dWindow->checkQuestion(i);
			switch(state)
			{
			case -1:
				break;
			case 0:
				_packet.clear();
				_packetID = DECLINE_REQUEST;
				_clients[i]->send(_packet);
				break;
			case 1:
				_packet.clear();
				_packetID = ACCEPT_REQUEST;
				_clients[i]->send(_packet);
				break;
			}*/

			break;
		case CONTINUE:

			for(int j = 0; j < _clients.size(); j++)
			{
				_packet.clear();
				_packetID = CONTINUE;
				_packet<<_packetID;
				_clients[j]->send(_packet);
				std::cout<<"Sending continue to "<<_interface.getPlayer(j).ID<<std::endl;
			}

			_currentPhase = GAME;

			std::cout<<"Server going to gamePhase"<<std::endl;

			//_dWindow->close();
			//delete _dWindow;
			break;
		case REQUEST_UPLOAD:
		
			_packet>>tempFileName>>tempCardAmount>>tempCardSizeX>>tempCardSizeY;
			totalCards+=tempCardAmount;
			std::cout<<_interface.getPlayer(playerIndex).ID<<" sends request to upload "<<tempFileName<<"Amount: "<<tempCardAmount<<" X:"<<tempCardSizeX<<" Y:"<<tempCardSizeY<<std::endl;

			if(checkFileExistence(tempFileName))
			{
				_packet.clear();
				_packetID = DECLINE_REQUEST;
				_packet<<_packetID;
				_clients[playerIndex]->send(_packet);

				_packet.clear();
				_packetID = REQUEST_UPLOAD;
				_packet<<_packetID<<tempFileName<<tempCardAmount<<tempCardSizeX<<tempCardSizeY;
				for(int i = 0; i < _clients.size(); i++)
				{
					if(i != playerIndex)
						_clients[i]->send(_packet);
				}
			}
			else
			{
			_packet.clear();
			_packetID = ACCEPT_REQUEST;
			_packet<<_packetID;
			_clients[playerIndex]->send(_packet);
			_clients[playerIndex]->setBlocking(true);

			receiveImageFile(tempFileName, playerIndex,tempCardAmount,tempCardSizeX,tempCardSizeY);
			}
			//_dWindow->addQuestion(playerIndex ,_interface.getPlayer(playerIndex).ID, ("upload "+filename) );
			break;
		case ACCEPT_REQUEST:
			_clients[playerIndex]->setBlocking(true);
			sendImageFile(tempFileName, playerIndex);
			break;
		case DECLINE_REQUEST:
			break;
		}		
	}
}

void Server::reset()
{
	_packet.clear();
	_clients.clear();
	_selector.clear();
	_selector.add(_listener);
}

void Server::receiveTCP()
{
	for(int i = 0; i < _clients.size(); i++)
	{
		_packet.clear();

		_packetID = EMPTY;

		_clients[i]->receive(_packet);

		sf::Int16 x,y,cardID,playerIndex = i;

		sf::Int16 seed = _theSeed;

		_packet>>_packetID;

		switch(_packetID)
		{
			case EMPTY:
				break;
			case ROTATE_CARD:
				_packet>>cardID>>x>>y;
				std::cout<<_interface.getPlayer(i).ID<<" rotateded cardID: "<<cardID<<std::endl;

				_packet.clear();
				_packetID = ROTATE_CARD;
				_packet<<_packetID<<playerIndex<<cardID<<x<<y;

				for(int j = 0; j < _clients.size(); j++)
				{
					if(j!=i)
						_clients[j]->send(_packet);
				}
				break;
			case TURN_CARD:
				_packet>>cardID;
				std::cout<<_interface.getPlayer(i).ID<<" turned cardID: "<<cardID<<std::endl;

				_packet.clear();
				_packetID = TURN_CARD;
				_packet<<_packetID<<playerIndex<<cardID;

				for(int j = 0; j < _clients.size(); j++)
				{
					if(j!=i)
						_clients[j]->send(_packet);
				}
				break;
			case PICK_UP_CARD:
				_packet>>cardID>>x>>y;
				std::cout<<_interface.getPlayer(i).ID<<" picked up cardID: "<<cardID<<std::endl;
				_packet.clear();
				_packetID = PICK_UP_CARD;
				_packet<<_packetID<<playerIndex<<cardID<<x<<y;
				
				for(int j = 0 ; j < _clients.size();j++)
				{
					if(j!= i)
						_clients[j]->send(_packet);
				}
				
				break;
			case RELEASE_CARD:
				_packet>>x>>y;
				std::cout<<_interface.getPlayer(i).ID<<" dropped that shit on X: "<<x<<" Y: "<<y<<std::endl;
				_packet.clear();
				_packetID = RELEASE_CARD;
				_packet<<_packetID<<playerIndex<<x<<y;

				for(int j = 0 ; j < _clients.size();j++)
				{
					if(j!= i)
						_clients[j]->send(_packet);
				}
				break;
			case MOVE_SHIT:
			sf::Int16 playerIndex, tempx, tempy;
			_packet>>playerIndex>>tempx>>tempy;
			//std::cout<<"SERVER: "<<i<<". Mouse X: "<<tempx<<" Y: "<<tempy<<std::endl;
			for(int j = 0; j < _clients.size(); j++)
			{
				if(j != playerIndex)
				{
					_packet.clear();
					_packetID = MOVE_SHIT;
					_packet<<_packetID<<playerIndex<<tempx<<tempy;
					//if(_sendTimer.getElapsedTime().asMilliseconds()>50)
						_clients[j]->send(_packet);
				}
			}
			//_sendTimer.restart();
			break;
			case SHUFFLE:
				_packet.clear();
				_packetID = SHUFFLE;

				_packet<<_packetID<<seed;

				for(int j = 0; j < _clients.size(); j++)
				{
					_clients[j]->send(_packet);
				}
				break;
			case MESSAGE:
				break;
		}
	}
}

void Server::receiveUDP()
{
	for(int i = 0; i < _clients.size(); i++)
	{
	_packet.clear();

	_packetID = EMPTY;

	if(_UDPreceive.receive(_packet, _clients[i]->getRemoteAddress(), _port) != sf::Socket::Done)
	{
	//	std::cout<<"Server UDP didn't receive sheet"<<std::endl;
	}

	_packet>>_packetID;

		switch(_packetID)
		{
		case EMPTY:
			break;
		case MOVE_SHIT:
			sf::Int16 playerIndex, tempx, tempy;
			_packet>>playerIndex>>tempx>>tempy;
			//std::cout<<"SERVER: "<<i<<". Mouse X: "<<tempx<<" Y: "<<tempy<<std::endl;
			for(int j = 0; j < _clients.size(); j++)
			{
				if(j != playerIndex)
				{
					_packet.clear();
					_packetID = MOVE_SHIT;
					_packet<<_packetID<<playerIndex<<tempx<<tempy;
					sendUDP(j, _packet);
				}
			}
			_sendTimer.restart();
			break;
		}
	}
}

void Server::sendStartPacket(int clientIndex)
{
	_packet.clear();

	_packetID = START;

	sf::Int16 playerIndex = clientIndex, playerCount = _clients.size();

	_packet<<_packetID<<playerIndex<<playerCount;

	for(int i = 0; i < playerCount;i++)
	{
		_packet<<_interface.getPlayer(i).ID;
		sf::Int16 r, g, b;
		r = _playerColors[i].r;
		g = _playerColors[i].g;
		b = _playerColors[i].b;
		_packet<<r<<g<<b;
	}

	_clients[clientIndex]->send(_packet);
}

void Server::sendUDP(int clientIndex, sf::Packet packet)
{
	if(_sendTimer.getElapsedTime().asMilliseconds()>5)
		_UDPsend.send(packet,_interface.getPlayer(clientIndex).IP, _interface.getPlayer(clientIndex).UDPport);
}

void Server::receiveImageFile(std::string filename, int clientIndex, sf::Int16 amount,sf::Int16 x,sf::Int16 y)
{
	sf::Clock uploadTime;
	int packetCounter = 0;

	std::fstream *outputFile = new std::fstream;

	*outputFile = std::fstream(filename, std::ios::binary|std::ios::out);

	bool done = false;
	while(!done)
	{
		_packet.clear();
		_packetID = EMPTY;

		std::string data;
		
		_clients[clientIndex]->receive(_packet);

		_packet>>_packetID;

		switch(_packetID)
		{
		case UPLOAD:
			std::cout<<"Received upload packet"<<std::endl;
			packetCounter++;
			_packet>>data;
			writeImageFile(filename,data,outputFile);
			break;
		case UPLOAD_DONE:
			std::cout<<"Client says upload done, I don't believe"<<std::endl;
			std::cout<<"Time: "<<uploadTime.getElapsedTime().asSeconds()<<std::endl;
			std::cout<<"Number of packets received: "<<packetCounter<<std::endl;
			done = true;
			outputFile->close();
			_clients[clientIndex]->setBlocking(false);
			
			_packet.clear();
			_packetID = REQUEST_UPLOAD;
			_packet<<_packetID<<tempFileName<<tempCardAmount<<tempCardSizeX<<tempCardSizeY;
			for(int i = 0; i < _clients.size(); i++)
			{
				if(i != clientIndex)
					_clients[i]->send(_packet);
			}
			break;
		}
	}
}

void Server::writeImageFile(std::string filename, std::string data, std::fstream* output)
{
	if(*output)
	{
		char buffer[61440];

		int dataStringSize = data.size();

		std::cout<<"Data string size: "<<dataStringSize<<std::endl;

		for(int i = 0; i < dataStringSize; i++)
		{
			buffer[i] = data[i];
		}

		for(int i = 0; i < dataStringSize; i++)
		{
			output->write(&buffer[i], 1);
		}
	}
}

void Server::sendImageFile(std::string filename,int index)
{
	int packetCounter = 0;
	std::fstream inputFile(filename, std::ios::binary|std::ios::in);

	if(inputFile)
	{
		
		char buffer[61440];
		std::string sendString;
		bool done = false;
		int i;

		_packetID = UPLOAD;

		while(!done)
		{
			_packet.clear();
			_packet<<_packetID;

			i = 0;

			while(i < 61440 && inputFile.peek() != EOF)
			{
				inputFile.read(&buffer[i], 1);

				i++;

				if(inputFile.peek() == EOF)
					done = true;
			}

			for(int j = 0; j < i; j++)
			{
				sendString.push_back(buffer[j]);
			}
			std::cout<<"Sending buffer"<<std::endl;
			packetCounter++;
			_packet<<sendString;
			_clients[index]->send(_packet);
			sendString.clear();
		}
		inputFile.close();
	}
	std::cout<<"Done sending stuff"<<std::endl;
	std::cout<<"Number of packets sent: "<<packetCounter<<std::endl;
	_packet.clear();
	_packetID = UPLOAD_DONE;
	_packet<<_packetID;
	_clients[index]->send(_packet);
	_clients[index]->setBlocking(false);
}

bool Server::checkFileExistence(std::string filename)
{
	std::fstream file(filename);
	if(file)
	{
		file.close();
		return true;
	}
	else
		return false;
}

void Server::update()
{
	switch(_currentPhase)
	{
	case CONNECTIONS:
		connectionPhase();
		break;
	case DOWNLOADS:
		dialoguePhase();
		break;
	case GAME:
		receiveTCP();
		//receiveUDP();
		break;
	}
}

void Server::run()
{
	while(true)
	{	
		update();
	}
}

Server::~Server(void)
{
	for(std::vector<sf::TcpSocket*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		delete *it;
}