#include "Server.h"
#include "Client.h"
#include "StartScreen.h"

int main()
{
	StartScreen startscreen;

	startscreen.run();

	int option = startscreen.getOption();
	
	if(option == PLAY)
	{
		Client client;
		client.connect(startscreen.getIp(),2000,startscreen.getID());
		client.run();
	}
	else if(option == HOSTPLAY)
	{
		Server server;
		sf::Thread serverThread(&Server::run, &server);
		serverThread.launch();

		Client client;
		client.connect(sf::IpAddress::getLocalAddress(), 2000, startscreen.getID());
		client.run();
	}
	else if(option == HOST)
	{
		Server server;
		server.run();
	}

	return 0;
}