#include "Client.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600,32), "Client");

	Client client(window);
	while(window.isOpen())
	{
	client.run();
	}
	return 0;
}