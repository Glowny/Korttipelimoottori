#include "Server.h"
#include "Client.h"
#include "StartScreen.h"
#include "AssetLoader.h"

int main()
{	
	AssetLoader assetLoader;
	StartScreen startscreen(assetLoader);


	startscreen.run();

	int option = startscreen.getOption();
	
	if(option == PLAY)
	{
		Client client(assetLoader);
		client.connect(startscreen.getIp(),2000,startscreen.getID());
		client.run();
	}
	else if(option == HOSTPLAY)
	{
		Server server;
		sf::Thread serverThread(&Server::run, &server);
		serverThread.launch();

		Client client(assetLoader);
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