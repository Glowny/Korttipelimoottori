#include "SFML\Graphics.hpp"
#include "CardObject.h"
#include <fstream>
#include <iostream>
#include <algorithm>


int main2(){


	char buffer[1024];

	std::vector<CardObject>cardObjects;

	sf::RenderWindow window(sf::VideoMode(1280,760,32),"tesad");
	//window.setFramerateLimit(60);
	sf::Clock timer;

	sf::Texture *texture = new sf::Texture;
	texture->loadFromFile("170x340kortit.png");

	float cardSizey = 170;
	float cardSizex = 340;
	sf::Vector2f distanceFromOrigin;
	int cardAmount = 52;
	
	int xnumber = 2048/cardSizey;
	int ynumber = 2048/cardSizex;
	int selectedCard = -1;
	int hoveredCard = -1;
	bool brake = false;

	for(int y = 0; y < ynumber;y++)
	{


	for(int x = 0; x < xnumber;x++)
		{
			cardObjects.push_back(CardObject(texture,sf::IntRect(x*cardSizex,cardSizey*y,cardSizex,cardSizey)));
			if(cardObjects.size() == 53)
			{
				brake = true;
				break;
			}
			//cardObjects[cardObjects.size()-1]._sprite.setPosition((sf::Vector2f(x*cardSizex,cardSizey*y)));

		}
	if(brake)
		break;

	}
	
	
	sf::IntRect backRect = cardObjects[0]._sprite.getTextureRect();
	cardObjects.erase(cardObjects.begin());
	std::cout<<cardObjects.size()<<std::endl;

	for(int i= 0; i < cardObjects.size();i++)
	{
		cardObjects[i].changeTexture(backRect);
	}

	
	
	sf::Time deltaTime;
	sf::Clock clickTimer;
	float dt;
	int size = cardObjects.size();
	bool broken;
	bool firstHover = false;
	while(true)
	{
		
		deltaTime = timer.restart();
		dt = deltaTime.asMilliseconds();
		//std::cout<<dt<<std::endl;

	

	

	
	broken = false;
	
			
	

	if(clickTimer.getElapsedTime().asMilliseconds()>100)
		{

		hoveredCard = -1;
		firstHover = false;
		for(int i = 0; i < size;i++)
		{
				if(cardObjects[i]._sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{ 
					if(firstHover == false)
					{
						firstHover = true;
						hoveredCard = i;
					}
						

					if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedCard == -1)
					{
		
						std::cout<<i<<std::endl;
						distanceFromOrigin = sf::Vector2f(sf::Mouse::getPosition(window))-cardObjects[i]._sprite.getPosition();
						
						selectedCard = i;
						CardObject temp = cardObjects[i];
						cardObjects.erase(cardObjects.begin()+i);
						cardObjects.insert(cardObjects.begin(),temp);
						selectedCard = 0;
						hoveredCard = i;
						broken = true;
						break;
					}
					if(broken)
						break;
				}
				if(broken)
					break;
			
		}
		clickTimer.restart();
	}
	

		




		if(selectedCard != -1)
		cardObjects[selectedCard]._sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(window))-distanceFromOrigin);

		sf::Event Event;
		while(window.pollEvent(Event))
		{
			if(Event.type == sf::Event::MouseButtonReleased)
			{
				selectedCard = -1;
			}

			if(Event.type == sf::Event::MouseButtonPressed)
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					
					if(hoveredCard!=-1)
					{
						if(selectedCard != -1)
							hoveredCard = selectedCard;

						std::cout<<"jeh"<<std::endl;

						if(cardObjects[hoveredCard]._sprite.getTextureRect()!=backRect)
							cardObjects[hoveredCard].changeTexture(backRect);
							
						else
							cardObjects[hoveredCard].resetTexture();
					}
				}
			}
		}
		
			//for(int i = 0; i < cardObjects.size();i++)
			//{
			//	if(cardObjects[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			//	{
			//		cardObjects[i].scale(0.5f,0.5f);
			//	}
			//	}
			//}


	/*			for(int i = 0; i < cardObjects.size();i++)
				{
					if(cardObjects[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						cardObjects[i].setScale(1.f,1.f);
					}
					else
						cardObjects[i].setScale(0.75f,0.75f);
				}*/


				
			//}

		//}

		//}


	window.clear();
	for(int i = cardObjects.size()-1; i >= 0;i--)
	{
		window.draw(cardObjects[i]._sprite);
	}


		window.display();
	}

	}


