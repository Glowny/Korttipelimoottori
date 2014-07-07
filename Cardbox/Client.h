#pragma once
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>
class Client
{
public:
	Client(void);
	~Client(void);
	void run();
	void connect(sf::IpAddress ip, int port, std::string id);
	void draw();
private:
	sf::TcpSocket TCPsocket;
	sf::Packet packet;
	sf::RenderWindow window;
};