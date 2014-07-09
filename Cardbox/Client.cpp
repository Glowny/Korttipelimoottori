#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(1280,760), "Cardbox"))
{
	window.setFramerateLimit(60);
	UDPreceive.bind(sf::Socket::AnyPort);
	gameOn = false;
	std::srand(time(NULL));

	deltaTime_time = deltaClock.restart();
	mickeymouse = false;
}

void Client::run()
{
	while(true)
	{
		deltaTime_time = deltaClock.restart();
		deltaTime = deltaTime_time.asMilliseconds();

		checkInput();
		receiveTCP();
		if(gameOn)
		{
			shapes[ownIndex].setPosition(posX, posY);
			sendPos();
			receiveUDP();
		}
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

void Client::sendPos()
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
		case START_GAME:
			gameOn = true;
			std::cout<<"gameOn = true"<<std::endl;
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
			window.setMouseCursorVisible(false);
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
			if(Event.key.code == sf::Keyboard::Space)
			{
				packet.clear();
				packetID = START_GAME;
				packet<<packetID;
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

void Client::draw()
{
	window.clear(sf::Color(50,135,50,255));
	for(int i = 0; i < shapes.size(); i++)
	{
		window.draw(shapes[i]);
	}
	window.display();
}

Client::~Client(void)
{
}