#include <iostream>
#include "Draw.h"
#include "MouseExplosion.h"
enum Mode
	{
		SETPOS,
		SETSIZE,
		SELECTSETPOS,
	};
int main()
{
	std::vector<MouseExplosion>_explosions;
	std::vector<sf::RectangleShape*> ShapeVector;
	int selectedRect;
	int mode=0;
	bool mousePressed = 0;
	sf::Clock _timer;
	sf::RenderWindow window(sf::VideoMode(1000,1000), "TheNextCardGameEditor");
Draw draw(ShapeVector, window, _explosions);
	while (window.isOpen())
	{
			window.clear();
			draw.DrawStuff();
			for(int i = 0; i < _explosions.size();)
			{
				if(_explosions[i].update())
					i++;
				else
					_explosions.erase(_explosions.begin()+i);
			}
			window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			
			if (event.type == sf::Event::Closed)
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sf::RectangleShape *rect = new sf::RectangleShape(sf::Vector2f(100,200));
				rect->setPosition(100,100);
				rect->setFillColor(sf::Color::Green);
				ShapeVector.push_back(rect);
				selectedRect = ShapeVector.size()-1;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ShapeVector.size() != 0)
			{
				float x, y;
				std::cout << "Give new size(x)" << std::endl;
				std::cin  >> x;
				std::cout << "Give new size(y)" << std::endl;
				std::cin >> y;
				ShapeVector[selectedRect]->setSize(sf::Vector2f(x,y));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && ShapeVector.size() != 0)
			{
				float x, y;
				std::cout << "Give new position(x)" << std::endl;
				std::cin  >> x;
				std::cout << "Give new position(y)" << std::endl;
				std::cin >> y;
				ShapeVector[selectedRect]->setPosition(sf::Vector2f(x,y));
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)&& ShapeVector.size() != 0)
			{
				int index;
				std::cout << "Give current cardIndex (0-" << ShapeVector.size()-1 << ")" << std::endl;
				std::cin >> index;
				if (index < ShapeVector.size() && index >= 0)
				{
					selectedRect = index;
				}
				else
				{
				std::cout << "Sorry I made a mistake master";
				}
			}
			if(ShapeVector.size() != 0)
			{
	if (mode == SETPOS)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{

				if (mousePressed == 0)
				{
				if ((ShapeVector[selectedRect]->getGlobalBounds().contains((sf::Mouse::getPosition		(window).x),sf::Mouse::getPosition(window).y)))
						{
							mousePressed = 1;
						}
				}
				else
				{
						ShapeVector[selectedRect]->setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
				}
			}
		else
			mousePressed = 0;
	}
	if (mode == SELECTSETPOS)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (mousePressed == 0)
			{
				for (int i = 0; i < ShapeVector.size(); i++)
				{
					if ((ShapeVector[i]->getGlobalBounds().contains((sf::Mouse::getPosition(window).x),sf::Mouse::getPosition(window).y)))
					{
						selectedRect = i;
						mousePressed = 1;
						ShapeVector[selectedRect]->setOrigin(sf::Mouse::getPosition(window).x-ShapeVector[selectedRect]->getPosition().x,sf::Mouse::getPosition(window).y-ShapeVector[selectedRect]->getPosition().y);

						ShapeVector[selectedRect]->setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
						
						break;

					}
				}

			}
			else
			{
				ShapeVector[selectedRect]->setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
				if(_timer.getElapsedTime().asSeconds()>0.009)
  							{	
							_explosions.push_back(MouseExplosion(sf::Vector2f(sf::Mouse::getPosition(window)),sf::Color(255,255,255,20),sf::Color(255,255,255,20)));
  							_timer.restart();
  							}
			}
		}
		else
		{
		mousePressed = 0;
		ShapeVector[selectedRect]->setPosition(ShapeVector[selectedRect]->getPosition()-ShapeVector[selectedRect]->getOrigin());
		ShapeVector[selectedRect]->setOrigin(0,0);
		}

	}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			{
				if (mode < 3) // enumin eli modien määrä
				{
					mode++;
				}
				else
					mode = 0;
				std::cout << "Mode changed to" << mode << std::endl;
				mousePressed = 0;
			}
		}
	}
	return 0;
}