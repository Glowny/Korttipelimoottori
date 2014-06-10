#include "Dealer.h"
#include "Player.h"

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>

//Server

int main()
{
	std::cout<<"Server Running"<<std::endl;

	int playerCount;

	std::cout<<"Enter the number of players: ";
	std::cin>>playerCount;

	sf::TcpListener listener;
	sf::SocketSelector selector;
	Dealer dealer;
	bool gameOn = false;
	std::vector<sf::TcpSocket*> clients;
	std::vector<Player> players;

	int port = 2000;

	listener.listen(port);
	selector.add(listener);

	while(!gameOn)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				sf::TcpSocket* socket = new sf::TcpSocket;
				listener.accept(*socket);
				sf::Packet packet;
				std::string id;
				if(socket->receive(packet) == sf::Socket::Done)
					packet>>id;
				players.push_back(Player(id));
				std::cout<<id<<" has connected to the chat room"<<std::endl;
				clients.push_back(socket);
				selector.add(*socket);
			}
		}
		if(clients.size() == playerCount)
		{
			dealer.shuffle();
			for(int i = 0; i < clients.size(); i++)
			{
				players[i].setHand(dealer.deal(2));
				
				sf::Packet cardPacket;
				bool turn = false;
				cardPacket<<players[i].getHand()<<turn;
				clients[i]->send(cardPacket);
			}
			gameOn = true;
		}
	}
	
	while(gameOn)
		{
			for(int i = 0; i < clients.size();)
			{

				sf::Packet sendPacket;

				std::string text;
				bool turn;

				turn = true;
				text = "SERVER:  YOUR TURN";

				sendPacket<<players[i].getHand()<<turn;

				clients[i]->send(sendPacket);

					std::cout<<players[i].getID()<<" turn"<<std::endl;
					if(selector.wait())
					{
						if(selector.isReady(*clients[i]))
						{
							sf::Packet packet;
							if(clients[i]->receive(packet) == sf::Socket::Done)
							{
								std::cout<<"Received packet from "<<players[i].getID()<<std::endl;
								std::string text2;
								packet >> text2;
								turn = false;
								sendPacket.clear();
								sendPacket << text2 << turn;
								for(int j = 0; j < clients.size(); j++)
								{
									if(i != j)
										clients[j]->send(sendPacket);
								}
								i++;
							}
						}
					}
			}
		}
	for(std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
		delete *it;

	return 0;
}