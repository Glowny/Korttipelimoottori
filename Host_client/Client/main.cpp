//#include "Hand.h"
//#include "Card.h"
//#include "Table.h"
#include "Client.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>

//Client

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600,32), "Client");

	Client client(window);
	while(window.isOpen())
	{
	client.run();
	}

	//sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	//sf::TcpSocket socket;
	//std::string id;
	//std::string text = "";

	//std::cout<<"Enter online ID: ";
	//std::cin>>id;

	//int port = 2000;

	//socket.connect(ip, port);

	//sf::RenderWindow window(sf::VideoMode(800,600,32), "Chat");
	//std::vector<sf::Text> chat;

	//Table Table(window);

	//Table.addPlayer(id);

	//Hand hand, table;

	//sf::Uint16 packetID, playerCount;

	//sf::Packet IDPacket;
	//IDPacket << id;
	//socket.send(IDPacket);
	//socket.setBlocking(false);

	//window.setTitle(id);

	//sf::Font font;
	//font.loadFromFile("comic.ttf");


	//while(window.isOpen())
	//{
	//	sf::Event Event;
	//	while(window.pollEvent(Event))
	//	{

	//		switch(Event.type)
	//		{
	//		case sf::Event::Closed:
	//			window.close();
	//			break;
	//		case sf::Event::KeyPressed:
	//			if(Event.key.code == sf::Keyboard::Escape)
	//				window.close();
	//			/*else if(Event.key.code == sf::Keyboard::Return)
	//			{
	//				sf::Packet packet3;
	//				packet3 << id;
	//				socket.send(packet3);
	//				sf::Text displayText(text, font, 20);
	//				displayText.setColor(sf::Color::Green);
	//				chat.push_back(displayText);
	//				text = "";
	//			}
	//			else if(Event.key.code == sf::Keyboard::BackSpace)
	//			{
	//				text = "";
	//			}
	//			break;
	//		case sf::Event::TextEntered:
	//			text += Event.text.unicode;*/
	//			break;
	//		}
	//	}

	//	sf::Packet receivePacket;
	//	
	//	socket.receive(receivePacket);
	//	
	//	Hand sendHand;
	//	sf::Packet sendPacket;
	//	
	//	packetID = 0;
	//	
	//	receivePacket>>packetID;


	//	switch (packetID)
	//	{

	//	case 0:
	//		break;

	//	case 1:
	//		receivePacket>>hand>>playerCount;

	//		for(int i = 0; i < playerCount; i++)
	//		{
	//			std::string tempText;
	//			receivePacket>>tempText;
	//			std::cout<<tempText<<" joined"<<std::endl;
	//			Table.addPlayer(tempText);
	//		}


	//		Table.addToTable(id,hand);

	//		std::cout<<"Your hand:"<<std::endl;

	//		for(int i=0; i<hand.hand.size(); i++)
	//		{
	//			std::cout<<hand.hand[i].suit<<" "<<hand.hand[i].value<<std::endl;
	//		}
	//		break;
	//	case 2:
	//		
	//		std::cout << "===========================" << std::endl;
	//		std::cout << "Valitse pelattava kortti" << std::endl;
	//		for (int i = 0; i < hand.hand.size(); i++)
	//		{
	//			std::cout << i <<"="<< hand.hand[i].value << std::endl;
	//		}
	//		std::cout << "===========================" << std::endl;
	//		int selection;
	//		std::cin >> selection;

	//		sendHand.add(hand.hand[selection]);

	//		sendPacket<<sendHand;
	//		socket.send(sendPacket);

	//		Table.removeFromTable(id, sendHand);

	//		hand.hand.erase(hand.hand.begin()+selection);

	//		break;
	//	case 3:
	//		table.hand.clear();

	//		receivePacket>>text>>table;

	//		std::cout<<text<<" plays: "<<table.hand[0].suit<<" "<<table.hand[0].value<<std::endl;

	//		Table.addToTable(text, table);

	//		break;
	//	case 4:
	//		text.clear();
	//		receivePacket>>text;
	//		
	//		if(text.size()>0)
	//		{
	//		std::cout<<text<<" turn"<<std::endl;
	//		}
	//		break;
	//	}

	//	int i = 0;
	//	for(i; i < chat.size(); i++)
	//	{
	//		chat[i].setPosition(0,i*20);
	//		window.draw(chat[i]);
	//	}

	//	sf::Text drawText(text, font, 20);
	//	drawText.setColor(sf::Color::Magenta);
	//	drawText.setPosition(0, i*20);
	//	window.draw(drawText);
	//	Table.drawTable();
	//	window.display();
	//	window.clear(sf::Color(100,100,100,256));
	//}
	return 0;
}