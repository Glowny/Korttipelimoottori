#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode;
	char buffer[2000];
	std::size_t received;
	std::string text = "Connected to: ";

	std::cout << "Enter (s) for server, Enter (c) for client: " << std::endl;
	cin >> connectionType;

	if(connectionType == 's')
	{
		std::cout<<ip<<std::endl;
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Server";
		mode = 's';
	}
	else if(connectionType == 'c')
	{
		std::string tempIP;
		std::cout<<"Gief ip"<<std::endl;
		std::cin>>tempIP;
		ip = tempIP;
		socket.connect(ip, 2000);
		text += "Client";
		mode = 'r';
	}

	socket.send(text.c_str(), text.length() +1);

	socket.receive(buffer, sizeof(buffer), received);

	std::cout << buffer << std::endl;

	bool done = false;

	while(!done)
	{
		if(mode == 's')
		{
			std::getline(cin, text);
			socket.send(text.c_str(), text.length() +1);
			mode = 'r';
		}
		if(mode = 'r')
		{
			socket.receive(buffer, sizeof(buffer), received);
			std::cout << "Received: " << buffer << std::endl;
			mode = 's';
		}
	}
	
}
