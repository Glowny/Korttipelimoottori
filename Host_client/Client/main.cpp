#include "Hand.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <vector>

//Client

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	std::string id;
	std::string text = "";

	std::cout<<"Enter online ID: ";
	std::cin>>id;

	int port = 2000;

	socket.connect(ip, port);

	sf::RenderWindow window(sf::VideoMode(800,600,32), "Chat");
	std::vector<sf::Text> chat;

	sf::Packet packet;
	packet << id;
	socket.send(packet);
	socket.setBlocking(false);

	window.setTitle(id);

	sf::Font font;
	font.loadFromFile("comic.ttf");

	bool turn = false;

	while(window.isOpen())
	{
		sf::Event Event;
		while(window.pollEvent(Event))
		{

			switch(Event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if(Event.key.code == sf::Keyboard::Escape)
					window.close();
				else if(Event.key.code == sf::Keyboard::Return && turn)
				{
					sf::Packet packet3;
					packet3 << id;
					socket.send(packet3);
					sf::Text displayText(text, font, 20);
					displayText.setColor(sf::Color::Green);
					chat.push_back(displayText);
					text = "";
					turn = false;
				}
				else if(Event.key.code == sf::Keyboard::BackSpace)
				{
					text = "";
				}
				break;
			case sf::Event::TextEntered:
				text += Event.text.unicode;
				break;
			}
		}

		sf::Packet packet4;
		socket.receive(packet4);
		
		Hand hand;
		if(packet4 >> hand  >> turn)
		{
			std::cout<<hand.hand[0].suit<<" "<<hand.hand[0].value<<std::endl;
			std::cout<<hand.hand[1].suit<<" "<<hand.hand[1].value<<std::endl;
			std::string temptext = "";
			/*for(int i = 0; i < hand.hand.size(); i++)
			{
				if(hand.hand[i].suit == Hearts)
					temptext = "Hearts " + hand.hand[i].value;
				if(hand.hand[i].suit == Diamonds)
					temptext = "Diamonds " + hand.hand[i].value;
				if(hand.hand[i].suit == Clubs)
					temptext = "Clubs " + hand.hand[i].value;
				if(hand.hand[i].suit == Spades)
					temptext = "Spades" + hand.hand[i].value;
			}*/
			sf::Text displayText(temptext,font,20);
			displayText.setColor(sf::Color::Red);
			chat.push_back(displayText);
		}

		int i = 0;
		for(i; i < chat.size(); i++)
		{
			chat[i].setPosition(0,i*20);
			window.draw(chat[i]);
		}

		sf::Text drawText(text, font, 20);
		drawText.setColor(sf::Color::Magenta);
		drawText.setPosition(0, i*20);
		window.draw(drawText);
		window.display();
		window.clear();
	}
	return 0;
}