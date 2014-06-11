#include "Dealer.h"
#include "Player.h"
#include "Hand.h"

#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>

//Server

int main()
{
	std::cout<<"Server Running"<<std::endl;

	sf::Uint16 playerCount;

	std::cout<<"Enter the number of players: ";
	std::cin>>playerCount;

	sf::TcpListener listener;
	sf::SocketSelector selector;
	Dealer dealer;
	bool gameOn = false;
	std::vector<sf::TcpSocket*> clients;
	std::vector<Player> players;

	sf::Uint16 packetID;

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
				packetID = 1;
				bool turn = false;
				sf::Uint16 other_playerCount = playerCount-1;
				cardPacket<<packetID<<players[i].getHand()<<other_playerCount;
				for(int j = 0; j < playerCount; j++)
				{
					if(i != j)
						cardPacket<<players[j].getID();
				}
				clients[i]->send(cardPacket);
			}
			gameOn = true;
		}
	}
	
	while(gameOn)
		{
			for(int i = 0; i < clients.size();)
			{

				sf::Packet startPacket;
				packetID = 2;

				startPacket<<packetID;

				clients[i]->send(startPacket);

				sf::Packet waitPacket;
				packetID = 4;

				waitPacket<<packetID<<players[i].getID();

				for(int j = 0; j < clients.size(); j++)
				{
					if(i != j)
						clients[j]->send(waitPacket);
				}

					std::cout<<players[i].getID()<<" turn"<<std::endl;
					if(selector.wait())
					{
						if(selector.isReady(*clients[i]))
						{
							sf::Packet packet;
							if(clients[i]->receive(packet) == sf::Socket::Done)
							{
								std::cout<<"Received packet from "<<players[i].getID()<<std::endl;
								Hand hand;
								packet >> hand;
								sf::Packet turnPacket;
								packetID = 3;
								turnPacket << packetID << players[i].getID() << hand;
								for(int j = 0; j < clients.size(); j++)
								{
									if(i != j)
										clients[j]->send(turnPacket);
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