#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(1280,760), "Cardbox"))
{
	window.setFramerateLimit(60);
	UDPreceive.bind(sf::Socket::AnyPort);
	gameOn = false;
	std::srand(time(NULL));
}

void Client::run()
{
	while(true)
	{
		deltaTime = deltaClock.getElapsedTime().asMilliseconds();
		deltaClock.restart();

		checkInput();
		receiveTCP();
		if(gameOn)
		{
			sendPos();
			receiveUDP();
		}
		for(int i = 0; i < shapes.size(); i++)
		{
		smootheMouse(i, shapes[i].getPosition() ,otherPlayersMousePos[i]);
		}
		draw();
	}
}

void Client::connect(sf::IpAddress ip, int port, std::string id)
{
	serverIP = ip;
	serverPort = port;
	TCPsocket.connect(serverIP,port);
	sf::Uint16 udpReceivePort = UDPreceive.getLocalPort();
	packet<<id<<udpReceivePort;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
	UDPreceive.setBlocking(false);
	UDPsend.setBlocking(false);
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
			packet>>ownIndex>>playerCount;
			initPlayers();
			break;
	}
}

void Client::smootheMouse(int index, sf::Vector2f oldpos,sf::Vector2f newpos)
{
	sf::Vector2f homovector = newpos-oldpos;

	if(homovector.x != 0 && homovector.y != 0)
	{
		shapes[index].move(homovector*0.005f*deltaTime);
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
	for(int i = 0; i < playerCount-1; i++)
	{
		shapes.push_back(sf::RectangleShape(sf::Vector2f(10,10)));
		otherPlayersMousePos.push_back(sf::Vector2f());
		int red,green,blue;
		red = std::rand()%255;
		blue = std::rand()%255;
		green = std::rand()%75;

		sf::Color color(red,green,blue,255);

		shapes[i].setFillColor(color);

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
				std::cout<<"Mouse click X: "<<sf::Mouse::getPosition().x<<" Y: "<<sf::Mouse::getPosition().y<<std::endl;
			break;
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