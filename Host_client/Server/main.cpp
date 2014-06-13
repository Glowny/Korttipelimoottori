#include "Server.h"

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>


int main()
{
	Server server;
	server.initialize();
	server.setUp(7);

	while(true)
	{
		server.run();
	}

	return 0;
}