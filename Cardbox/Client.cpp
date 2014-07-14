#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(1280,760), "Cardbox"))
{
	window.setFramerateLimit(60);
	UDPreceive.bind(sf::Socket::AnyPort);
	std::srand(time(NULL));

	currentPhase = CONNECTIONS;

	deltaTime_time = deltaClock.restart();
	mickeymouse = false;

	//dView = new DialogueView();
}

void Client::run()
{
	while(true)
	{
		deltaTime_time = deltaClock.restart();
		deltaTime = deltaTime_time.asMilliseconds();

		checkInput();

		switch(currentPhase)
		{
		case CONNECTIONS:
			connectionPhase();
			break;
		case DOWNLOADS:
			dialoguePhase();
			break;
		case GAME:
			gamePhase();
			break;
		}
		
		draw();
	}
}

void Client::connect(sf::IpAddress ip, int port, std::string id)
{
	ownName = id;
	serverIP = ip;
	serverPort = port;
	TCPsocket.connect(serverIP,port);
	sf::Uint16 udpReceivePort = UDPreceive.getLocalPort();
	packet<<id<<udpReceivePort;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
	UDPreceive.setBlocking(false);
	UDPsend.setBlocking(false);

	window.setTitle(ownName);
}

void Client::connectionPhase()
{
	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	switch(packetID)
	{
		case EMPTY:
			break;
		case CONTINUE:
			currentPhase = DOWNLOADS;
			std::cout<<"Client going to downloadsPhase"<<std::endl;
			break;
		case START:
			handleStartPacket();
			break;
	}
}

void Client::handleStartPacket()
{
	packet>>ownIndex>>playerCount;

	for(int i = 0; i <playerCount;i++)
	{
		std::string name;
		packet>>name;
				
		sf::Uint16 r,g,b;
		packet>>r>>g>>b;

		playerNames.push_back(name);
		playerColors.push_back(sf::Color(r,g,b));
	}

	initPlayers();
}

void Client::dialoguePhase()
{
	//dView->draw(window);

	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	/*std::string filename;
	int state = -1;*/

	switch(packetID)
	{
	case EMPTY:

		/*state = dView->checkQuestion(-1, sf::Vector2i(posX,posY));
		switch(state)
		{
		case -1:
			break;
		case 0:
			packet.clear();
			packetID = DECLINE_REQUEST;
			TCPsocket.send(packet);
			break;
		case 1:
			packet.clear();
			packetID = ACCEPT_REQUEST;
			TCPsocket.send(packet);
			break;
		}*/

		break;
	case CONTINUE:

		currentPhase = GAME;
		std::cout<<"Client going to gamePhase"<<std::endl;
		window.setMouseCursorVisible(false);
		//delete dView;
		break;
	case REQUEST_UPLOAD:
		packet>>fileName>>cardAmount>>cardSizeX>>cardSizeY;
		std::cout<<"Server sends request to upload "<<fileName<<"Amount: "<<cardAmount<<" X:"<<cardSizeX<<" Y:"<<cardSizeY<<std::endl;
	
		packet.clear();
		packetID = ACCEPT_REQUEST;
		packet<<packetID;
		TCPsocket.send(packet);

		receiveImageFile(fileName,cardAmount,cardSizeX,cardSizeY);
		/*packet>>filename;
		dView->addQuestion(-1 ,"SERVER", ("upload "+filename) );*/
		break;
	case ACCEPT_REQUEST:
		std::cout<<"Got server acceptance"<<std::endl;
		sendImageFile(fileName);
		break;
	case DECLINE_REQUEST:
		break;
	case UPLOAD:
		break;
	}
}

void Client::gamePhase()
{
	shapes[ownIndex].setPosition(posX, posY);

	sendUDP();
	receiveUDP();
	receiveTCP();

	for(int i = 0; i < shapes.size(); i++)
	{
		if(i != ownIndex)
		{
			if(i>ownIndex)
				smootheMouse(i, shapes[i].getPosition() ,otherPlayersMousePos[i-1]);
			else
				smootheMouse(i, shapes[i].getPosition() ,otherPlayersMousePos[i]);
		}
	}
}

void Client::sendUDP()
{
	if(_sendTimer.getElapsedTime().asMilliseconds()>5)
	{

	packet.clear();

	packetID = MOVE_SHIT;

	packet<<packetID<<ownIndex<<posX<<posY;

	UDPsend.send(packet,serverIP,serverPort);

	_sendTimer.restart();

	}
}

void Client::receiveTCP()
{
	packet.clear();

	packetID = EMPTY;

	TCPsocket.receive(packet);

	packet>>packetID;

	switch(packetID)
	{
		case EMPTY:
			break;
	}
}

void Client::smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos)
{
	sf::Vector2f homovector = newpos-oldpos;

	if(homovector.x != 0 && homovector.y != 0)
	{
		shapes[index].move(homovector*deltaTime*0.005f);
	}

}

void Client::receiveUDP()
{
	packet.clear();

	packetID = EMPTY;

	unsigned short tempPort = UDPreceive.getLocalPort();
	sf::IpAddress tempIP = serverIP;
	UDPreceive.receive(packet, tempIP, tempPort);
	
	packet>>packetID;

	switch(packetID)
	{
		case EMPTY:
			break;
		case MOVE_SHIT:
			
			sf::Uint16 playerIndex, tempX, tempY;
			packet>>playerIndex>>tempX>>tempY;

			std::cout<<"Client received: "<<playerIndex<<". X: "<<tempX<<" Y: "<<tempY<<std::endl;

			if(playerIndex > ownIndex)
				playerIndex--;

			otherPlayersMousePos[playerIndex] = sf::Vector2f(tempX,tempY);

			break;
	}
}

void Client::initPlayers()
{
		for(int i = 0; i < playerCount; i++)
		{
			if(i != ownIndex)
			{
			otherPlayersMousePos.push_back(sf::Vector2f());
			}
			shapes.push_back(sf::RectangleShape(sf::Vector2f(10,10)));
			shapes[i].setFillColor(playerColors[i]);
		}
}

void Client::checkInput()
{
	sf::Event Event;

	while(window.pollEvent(Event))
	{
		
		posX = sf::Mouse::getPosition(window).x;
		posY = sf::Mouse::getPosition(window).y;

		switch(Event.type)
		{

		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				window.close();
			if(Event.key.code == sf::Keyboard::Space && currentPhase != GAME)
			{
				packet.clear();
				packetID = CONTINUE;
				packet<<packetID;
				TCPsocket.send(packet);
				std::cout<<"Sending continue"<<std::endl;
			}
			if(Event.key.code == sf::Keyboard::Num1 && currentPhase == DOWNLOADS)
			{
				std::cout<<"Sending upload request"<<std::endl;
				fileName = "vesa";
				cardAmount = 10;
				cardSizeX = 170;
				cardSizeY = 340;
				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			if(Event.key.code == sf::Keyboard::Num2 && currentPhase == DOWNLOADS)
			{
				std::cout<<"Sending upload request"<<std::endl;
				sf::Uint16 cardAmount = 10;
				sf::Uint16 cardSizeX = 170;
				sf::Uint16 cardSizeY = 340;
				fileName = "karjalainen";
				packet.clear();
				packetID = REQUEST_UPLOAD;
				packet<<packetID<<fileName<<cardAmount<<cardSizeX<<cardSizeY;
				TCPsocket.send(packet);
			}
			break;
			
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout<<"Mouse click X: "<<sf::Mouse::getPosition().x<<" Y: "<<sf::Mouse::getPosition().y<<std::endl;
				packet.clear();
				packetID = PICK_UP_CARD;
				packet<<packetID;
				TCPsocket.send(packet);
				mickeymouse = true;
			}
			break;
		}
		
		if(mickeymouse == true)
		{
			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				packet.clear();
				packetID = RELEASE_CARD;
				packet<<packetID;
				TCPsocket.send(packet);
				mickeymouse = false;
			}
		}
	}
}

void Client::sendImageFile(std::string filename)
{
	std::fstream inputFile(filename+".png", std::ios::binary|std::ios::in);

	if(inputFile)
	{
		char buffer[16384];
		std::string sendString;
		bool done = false;
		int i;

		packetID = UPLOAD;

		while(!done)
		{
			packet.clear();
			packet<<packetID;

			i = 0;

			while(i < 16384 && inputFile.peek() != EOF)
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
			packet<<sendString;
			TCPsocket.send(packet);
			sendString.clear();
		}
		inputFile.close();
	}
	std::cout<<"Done sending stuff"<<std::endl;
	makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
	packet.clear();
	packetID = UPLOAD_DONE;
	packet<<packetID;
	TCPsocket.send(packet);
}

void Client::receiveImageFile(std::string filename,sf::Uint16 amount,sf::Uint16 x,sf::Uint16 y)
{
	sf::Clock uploadTime;

	std::fstream *outputFile = new std::fstream;

	*outputFile = std::fstream(filename+".png", std::ios::binary|std::ios::out);

	bool done = false;
	while(!done)
	{
		packet.clear();
		packetID = EMPTY;

		std::string data;
		
		TCPsocket.receive(packet);

		packet>>packetID;

		switch(packetID)
		{
		case UPLOAD:
			std::cout<<"Received upload packet"<<std::endl;
			packet>>data;
			writeImageFile(filename,data,outputFile);
			break;
		case UPLOAD_DONE:
			std::cout<<"Server says upload done, I believe"<<std::endl;
			std::cout<<uploadTime.getElapsedTime().asSeconds()<<std::endl;
			done = true;
			outputFile->close();
			makeDeck(filename,cardAmount,sf::Vector2f(cardSizeX,cardSizeY));
			break;
		}
	}
}

void Client::writeImageFile(std::string filename, std::string data, std::fstream* output)
{
	if(*output)
	{
		char buffer[16384];

		sf::Uint16 dataStringSize = data.size();

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

void Client::makeDeck(std::string filename, int cardAmount,sf::Vector2f cardSize)
{
	sf::Texture *texture = new sf::Texture;
	texture->loadFromFile(filename+".png");

	float cardSizeY = cardSize.y;
	float cardSizeX = cardSize.x;

	sf::Vector2f textureSize = sf::Vector2f(texture->getSize());

	int timesx = textureSize.x/cardSizeX;
	int timesy = textureSize.y/cardSizeY;
	bool brake = false;

	for(int y = 0; y < timesy;y++)
	{

	for(int x = 0; x < timesx;x++)
		{
			cards.push_back(CardObject(texture,sf::IntRect(x*cardSizeX,cardSizeY*y,cardSizeX,cardSizeY)));
			if(cards.size() == cardAmount)
			{
				brake = true;
				break;
			}
			//cardObjects[cardObjects.size()-1]._sprite.setPosition((sf::Vector2f(x*cardSizeX,cardSizeY*y)));

		}
	if(brake)
		break;

	}

	sf::IntRect backRect = cards[0]._sprite.getTextureRect();
	cards.erase(cards.begin());
	std::cout<<cards.size()<<std::endl;

	for(int i= 0; i < cards.size();i++)
	{
		cards[i].changeTexture(backRect);
	}



}

void Client::draw()
{
	window.clear(sf::Color(50,135,50,255));
	for(int i = 0; i < shapes.size(); i++)
	{
		window.draw(shapes[i]);
	}

	for(int i = 0; i < cards.size();i++)
	{
		cards[i].draw(window);
	}
	window.display();
}

Client::~Client(void)
{
}