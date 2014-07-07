#include "Client.h"
#include <iostream>

Client::Client(void) : window(sf::RenderWindow(sf::VideoMode(1280,760), "Cardbox"))
{
}

void Client::run()
{
	while(true)
	{
		draw();
	}
}

void Client::connect(sf::IpAddress ip, int port, std::string id)
{
	TCPsocket.connect(ip,port);
	packet<<id;
	TCPsocket.send(packet);
	TCPsocket.setBlocking(false);
}

void Client::draw()
{
	window.clear(sf::Color(50,135,50,255));

	window.display();
}

Client::~Client(void)
{
}