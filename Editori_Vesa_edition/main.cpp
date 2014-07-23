#include <iostream>
#include "Shape.h"
#include "Draw.h"
#include "MouseExplosion.h"
#include "CardInfo.h"
#include <fstream>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

void printNumber(int n);
int myrandom (int i ) {return std::rand()%i;}
void GETOUT();
std::vector<sf::RectangleShape> createButtons(sf::Vector2f pos);
bool isInside(sf::RectangleShape c, sf::RectangleShape rs);
sf::Vector2f reverse(sf::Vector2f v);
void writeFile(std::string fileName, int cards[],int amount,float width, float height);
std::vector<sf::RectangleShape> createGrid(sf::RectangleShape,sf::Vector2f coords);
std::vector<int> amountVector;
int cardAmountX = 8;
int cardAmountY = 8;
float cardSizeX = 100;
float cardSizeY = 100;

enum Mode
	{
		MANIPULATE,
		SETSIZE,
		SELECTSETPOS,
		CREATECOUNTER,
		SELECTSETSIZEMOUSE,
		CREATESETSIZEMOUSE,
		CREATEIMAGE,
		CHOOSEAMOUNT,
	};
enum ShapeType
	{
		CARD,
		AREA,
		COUNTER,
		IMAGE,
		TOP
	};
int main()
{
	std::srand (unsigned (std::time(0) ) );
	std::vector<MouseExplosion>_explosions;
	std::vector<Shape*> ShapeVector;
	std::vector<sf::RectangleShape> topVector;
	int selectedRect;
	int mode=4;
	int number;
	bool k=0;
	bool mousePressed = 0;
	std::string input = "0";
	sf::Clock _timer;
	sf::Vector2f clickPoint;
	sf::RectangleShape deckArea(sf::Vector2f(300,300));
	sf::Texture texture;
	sf::Texture texture2;
	bool keyPressed = 0;
	sf::RenderWindow window(sf::VideoMode(1600,1100), "TheNextCardGameEditor");
	sf::View view(window.getDefaultView());
	//view.rotate(270);
	window.setView(view);
	if(!texture.loadFromFile("backside.png"))
	{}
	if(!texture2.loadFromFile("vesa.png"));
	{}
	sf::RectangleShape shape;
	float buttonPosX= 1300;
	float buttonPosY= 100;

	std::vector<sf::RectangleShape> buttons = createButtons(sf::Vector2f(buttonPosX,buttonPosY));
	deckArea.setPosition(350,350);


Draw draw(ShapeVector, window, _explosions);
	while (window.isOpen())
	{
			sf::Vector2f mousePos  = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));

			if(amountVector.size() < topVector.size())
			{
				amountVector.clear();
				for(int i = 0; i < topVector.size(); i++)
				{
					amountVector.push_back(1);
				}
			}
			window.clear();
			window.draw(deckArea);
			draw.DrawStuff();
			draw.DrawTop(topVector, amountVector);
			draw.DrawTop(buttons);

			std::string paska = "CardAmountX: ";
			draw.DrawTextNumber(paska,cardAmountX,sf::Vector2f(buttonPosX,buttonPosY));
			paska = "CardAmountY: ";
			draw.DrawTextNumber(paska, cardAmountY, sf::Vector2f(buttonPosX,buttonPosY+100));
			paska = "CardSizeX: ";
			draw.DrawTextNumber(paska, cardSizeX, sf::Vector2f(buttonPosX,buttonPosY+100*2));
			paska = "CardSizeY: ";
			draw.DrawTextNumber(paska, cardSizeY, sf::Vector2f(buttonPosX,buttonPosY+100*3));
	
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

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			{
				if(keyPressed == 0)
				{
					if (mode < 7) // enumin eli modien m‰‰r‰
					{
						mode++;
					}
					else
					{
						mode = 0;
					}
						printNumber(mode);
					keyPressed = 1;
				}
			}
			else
			keyPressed = 0;
			
			
			if (event.type == sf::Event::Closed)
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				sf::RectangleShape rect(sf::Vector2f(100,200));
				rect.setPosition(100,100);
				int color1 = myrandom(255);
				int color2 = myrandom(255);
				int color3 = myrandom(255);
				rect.setFillColor(sf::Color(color1,color2,color3));
				rect.setOutlineColor(sf::Color(color1,color2,color3));
				rect.setOutlineThickness(1);
				/*rect.setOutlineColor(sf::Color::Transparent);*/
				Shape *shape = new Shape(rect, 0);
				ShapeVector.push_back(shape);
				selectedRect = ShapeVector.size()-1;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ShapeVector.size() != 0)
			{
				float x, y;
				std::cout << "Give new size(x)" << std::endl;
				std::cin  >> x;
				std::cout << "Give new size(y)" << std::endl;
				std::cin >> y;
				ShapeVector[selectedRect]->rect.setSize(sf::Vector2f(x,y));
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && ShapeVector.size() != 0)
			{
				float x, y;
				std::cout << "Give new position(x)" << std::endl;
				std::cin  >> x;
				std::cout << "Give new position(y)" << std::endl;
				std::cin >> y;
				ShapeVector[selectedRect]->rect.setPosition(sf::Vector2f(x,y));
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
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)&& ShapeVector.size() != 0)
			{
				bool c = 0;
				std::vector<int> indexVector;
				for (int i = ShapeVector.size()-1; i >= 0; i--)
				{
					if (deckArea.getGlobalBounds().intersects(ShapeVector[i]->rect.getGlobalBounds()))
					{
						indexVector.push_back(i);
						ShapeVector[i]->rect.setPosition(deckArea.getPosition());
						c = 1;
					}
				}
				if (c)
				{
				std::random_shuffle(indexVector.begin(), indexVector.end(), myrandom);

				// !
				Shape *tempShape;
				for (int i = 0; i < indexVector.size()-1; i++)
				{
					tempShape = ShapeVector[indexVector[i]];
					ShapeVector[indexVector[i]] = ShapeVector[indexVector[i+1]];
					ShapeVector[indexVector[i+1]] = tempShape;
				}
				if (ShapeVector.size() != 0)
				{
					tempShape = ShapeVector[indexVector[0]];
					ShapeVector[indexVector[0]] = ShapeVector[indexVector[indexVector.size()-1]];
					ShapeVector[indexVector[indexVector.size()-1]] = tempShape;
				}
				}
			}


	
	if (mode == CREATESETSIZEMOUSE)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (mousePressed == 0)
			{
			sf::RectangleShape rect;
			int color1 = myrandom(255);
			int color2 = myrandom(255);
			int color3 = myrandom(255);
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(sf::Color(color1,color2,color3));
			rect.setOutlineThickness(2.0f);
			rect.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
			Shape *shape = new Shape(rect, 1);
			ShapeVector.push_back(shape);
			selectedRect = ShapeVector.size()-1;
			mousePressed = 1;
			}
			else
			{
				ShapeVector[selectedRect]->rect.setSize(sf::Vector2f(sf::Mouse::getPosition(window))-ShapeVector[selectedRect]->rect.getPosition());
				
			}
		}
		else
		{
			mousePressed = 0;

		}
	}
	if(ShapeVector.size() != 0)
	{
	if (mode == CREATEIMAGE)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (mousePressed == 0)
			{
				for (int i = 0;  i < ShapeVector.size(); i++)
				{
					if (ShapeVector[i]->type == IMAGE)
					{
						sf::RectangleShape rect = ShapeVector[i]->rect;
						if (rect.getGlobalBounds().contains(mousePos))
						{
							/*rect.setSize(sf::Vector2f(mousePos-rect.getPosition()));*/
							selectedRect = i;
							mousePressed = 1;
							break;
						}
					}
					
				}
				for ( int i=0; i <buttons.size(); i++)
				{
					if(buttons[i].getGlobalBounds().contains(mousePos))
					{
						number = i;
						k = 1;
						mousePressed = 1;
						break;
					}
				}
				
			}
			else
			{
				sf::RectangleShape tempRect = topVector[0];
				sf::Vector2f size(mousePos-tempRect.getPosition());
				tempRect.setSize(size);
				/*topVector[i].setSize(sf::Vector2f(mousePos-topVector[i].getPosition()));*/
				cardSizeX = tempRect.getSize().x;
				cardSizeY = tempRect.getSize().y;
				topVector = createGrid(tempRect, tempRect.getPosition());


			}
		}
		else
			mousePressed = 0;
		if(k)
		{
				if (number == 0)
				{
					if (event.type == sf::Event::TextEntered)
						{
							if (event.text.unicode < 128)
							{input.push_back(static_cast<char>(event.text.unicode));
							std::cout << input;}
						}
				}
				else if (number == 1)
				{
				
				}
				else if (number == 2)
				{
				
				}
				else if(number == 3)
				{
				
				}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if(keyPressed == 0)
			{
				sf::Vector2f textureSize = sf::Vector2f(texture2.getSize());
				sf::RectangleShape rect(sf::Vector2f(textureSize.x/2,textureSize.y/2));
				rect.setTexture(&texture2);
				Shape *shape = new Shape(rect,IMAGE);
				ShapeVector.push_back(shape);
				mousePressed = 1;

				// luodaan gridiki

				sf::RectangleShape rect2(sf::Vector2f(rect.getSize().x/8,rect.getSize().y/8));
				cardSizeX = rect2.getSize().x;
				cardSizeY = rect2.getSize().y;
				rect2.setFillColor(sf::Color::Transparent);
				rect2.setOutlineColor(sf::Color::Green);
				rect2.setOutlineThickness(1);
				rect2.setPosition(rect.getPosition());
				while (rect2.getPosition().y < rect.getSize().y)
				{
					while(rect2.getPosition().x < rect.getSize().x)
					{
						topVector.push_back(rect2);
						rect2.setPosition(rect2.getPosition().x+rect2.getSize().x,rect2.getPosition().y);
					}
					rect2.setPosition(rect.getPosition().x,rect2.getPosition().y+rect2.getSize().y);
				}
				keyPressed = 1;
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			float number1, number2;
			std::cout << "Give grid width" << std::endl;
			std::cin >> cardSizeX;
			std:: cout << "Give grid height" << std::endl;
			std::cin >> cardSizeY;
			std::cout << "Give amount of squares x" << std::endl;
			std::cin >> cardAmountX;
			std::cout << "Give amount of squares y" << std::endl;
			std::cin >> cardAmountY;
			cardSizeX=cardSizeX/2;
			cardSizeY=cardSizeY/2;
			sf::Vector2f tempV;
			for (int i = 0; i < ShapeVector.size(); i++)
			{
				if (ShapeVector[i]->type == IMAGE)
				{
					tempV == ShapeVector[i]->rect.getPosition();
				}
			}
			sf::RectangleShape tempRect(sf::Vector2f(cardSizeX,cardSizeY));
			topVector = createGrid(tempRect, tempV);
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cardSizeY=cardSizeY+0.5;
		// tyhm‰‰
		sf::Vector2f tempV(0.0f,0.0f); // siis sen kuvan sijainti
		sf::RectangleShape tempRect(sf::Vector2f(cardSizeX,cardSizeY));
		topVector = createGrid(tempRect, tempV);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cardSizeY=cardSizeY-0.5;
		sf::Vector2f tempV(0.0f,0.0f);
		sf::RectangleShape tempRect(sf::Vector2f(cardSizeX,cardSizeY));
		topVector = createGrid(tempRect, tempV);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cardSizeX=cardSizeX-0.5;
		sf::Vector2f tempV (0.0f,0.0f);
		sf::RectangleShape tempRect(sf::Vector2f(cardSizeX,cardSizeY));
		topVector = createGrid(tempRect, tempV);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cardSizeX=cardSizeX+0.5;
		sf::Vector2f tempV(0.0f,0.0f);
		sf::RectangleShape tempRect(sf::Vector2f(cardSizeX,cardSizeY));
		topVector = createGrid(tempRect, tempV);
	}

	if(mode == CHOOSEAMOUNT)
	{
		if(mousePressed == 0)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				for (int i = 0; i < topVector.size(); i++)
				{
					if (topVector[i].getGlobalBounds().contains(mousePos))
					{
						amountVector[i] = amountVector[i]++;
					}
				}
			}
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{	
				for (int i = 0; i < topVector.size(); i++)
				{
					if (topVector[i].getGlobalBounds().contains(mousePos))
					{
						amountVector[i] = amountVector[i]--;
					}
				}	
			}
			mousePressed = 1;
		}
		else
			mousePressed = 0;
	}

	if (mode == SELECTSETSIZEMOUSE)	
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			for(int i = 0; i < ShapeVector.size(); i++)
			{
				if (ShapeVector[i]->rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					selectedRect = i;
					Shape *tempShape = ShapeVector[selectedRect];
					ShapeVector.erase(ShapeVector.begin()+selectedRect);
					ShapeVector.push_back(tempShape);
					selectedRect = ShapeVector.size()-1;
					break;
				}
			}
			if ((ShapeVector[selectedRect]->rect.getGlobalBounds().contains((sf::Mouse::getPosition(window).x),sf::Mouse::getPosition(window).y)))
						{
							mousePressed = 1;
							ShapeVector[selectedRect]->rect.setSize(sf::Vector2f(sf::Mouse::getPosition(window))-ShapeVector[selectedRect]->rect.getPosition());
						}
		
		else
				{
					ShapeVector[selectedRect]->rect.setSize(sf::Vector2f(sf::Mouse::getPosition(window))-ShapeVector[selectedRect]->rect.getPosition());
				}
		}
		else
			mousePressed = 0;
	}

	if(mode == CREATECOUNTER)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if(mousePressed == 0)
				{
					sf::RectangleShape rect(sf::Vector2f(50,50));
					rect.setFillColor(sf::Color::Blue);
					rect.setPosition(mousePos);
					Shape *numCount = new Shape(rect, COUNTER,2);
					ShapeVector.push_back(numCount);
					mousePressed = 1;
				}
			}
			else
				mousePressed = 0;
		}

	if (mode == MANIPULATE)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (mousePressed == 0)
				{
				for(int i = 0; i < ShapeVector.size(); i++)
					{
						if (ShapeVector[i]->type == COUNTER)
						{
							sf::RectangleShape shape = ShapeVector[i]->rect;
							if (shape.getGlobalBounds().contains(mousePos))
								{
									mousePressed = 1;
									break;
								}
							shape.setPosition(shape.getPosition().x+shape.getSize().x,shape.getPosition().y);
							if (shape.getGlobalBounds().contains(mousePos))
								{
									mousePressed = 1;
									ShapeVector[i]->number = ShapeVector[i]->number++;
									break;
								}
							shape.setPosition(shape.getPosition().x-shape.getSize().x*2,shape.getPosition().y);
							if (shape.getGlobalBounds().contains(mousePos))
								{
									mousePressed = 1;
									ShapeVector[i]->number = ShapeVector[i]->number--;
									break;
								}
							shape.setPosition(shape.getPosition().x+shape.getSize().x,shape.getPosition().y+shape.getSize().y);
							if (shape.getGlobalBounds().contains(mousePos))
								{
									mousePressed = 1;
									std::cout << "alinta painettu" << std::endl;
									break;
								}
						
						}
						else
						{
							if (ShapeVector[i]->rect.getGlobalBounds().contains(mousePos))
							ShapeVector[i]->rect.setPosition(mousePos);
						}
					}
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

					for (int i = ShapeVector.size()-1; i >= 0; i--)
					{
						if(ShapeVector[i]->type != COUNTER)
						{
							if (ShapeVector[i]->rect.getGlobalBounds().contains(mousePos))
							{
								selectedRect = i;
								mousePressed = 1;
								if (ShapeVector[selectedRect]->type != AREA)
								{
								Shape *tempShape = ShapeVector[selectedRect];
								ShapeVector.erase(ShapeVector.begin()+selectedRect);
								ShapeVector.push_back(tempShape);
								selectedRect = ShapeVector.size()-1;
								}
								sf::RectangleShape *tshape = &ShapeVector[selectedRect]->rect;
								clickPoint=(mousePos-tshape->getPosition());
							
								tshape->setPosition(mousePos-(clickPoint));
								break;

							}
						
						}
						else
						{
							sf::RectangleShape tempShape1 = ShapeVector[i]->rect;
							sf::RectangleShape tempShape2 = tempShape1;
							sf::RectangleShape tempShape3 = tempShape1;

							tempShape3.setPosition(tempShape1.getPosition().x-tempShape1.getSize().x,tempShape1.getPosition().y);
							tempShape2.setPosition(tempShape1.getPosition().x+tempShape1.getSize().x,tempShape1.getPosition().y);
							tempShape1.setPosition(tempShape1.getPosition().x,tempShape1.getPosition().y+tempShape1.getSize().y);


							
							if(tempShape1.getGlobalBounds().contains(mousePos) || tempShape2.getGlobalBounds().contains(mousePos)||tempShape3.getGlobalBounds().contains(mousePos)||ShapeVector[i]->rect.getGlobalBounds().contains(mousePos))
							{
								selectedRect = i;
								mousePressed = 1;
								sf::RectangleShape *tshape = &ShapeVector[selectedRect]->rect;
								clickPoint=(mousePos-tshape->getPosition());
							
								tshape->setPosition(mousePos-(clickPoint));
							}
						}
				}

			}
			else
			{
							sf::RectangleShape *tshape = &ShapeVector[selectedRect]->rect;

							tshape->setPosition(mousePos-(clickPoint));

				if(_timer.getElapsedTime().asSeconds()>0.009)
  							{	
							_explosions.push_back(MouseExplosion(sf::Vector2f(mousePos),sf::Color(255,255,255,20),sf::Color(255,255,255,20)));
  							_timer.restart();
  							}
			}
			
		}
	
		else
			{
			mousePressed = 0;
			/*ShapeVector[selectedRect]->rect.setPosition(ShapeVector[selectedRect]->rect.getPosition()-ShapeVector[selectedRect]->rect.getSize());*/
			}

	}

			}


	}
	// tapahtumia
				if(ShapeVector.size() != 0)
			{
				for (int i = 0; i < ShapeVector.size(); i++)
				{
					for (int j = 0; j < ShapeVector.size(); j++)
					{
						if ( ShapeVector[i]->type == CARD && ShapeVector[i]->type != ShapeVector[j]->type && isInside(ShapeVector[i]->rect,ShapeVector[j]->rect))
						{
							ShapeVector[i]->side = 0;
							break;
						}
						else
							ShapeVector[i]->side = 1;
					}
				}

			}
				for (int i = 0; i < ShapeVector.size(); i++)
				{
					if(ShapeVector[i]->type != IMAGE)
					{
						if(ShapeVector[i]->side == 1)
						{
							ShapeVector[i]->rect.setTexture(0);
						}
						else
						{
							ShapeVector[i]->rect.setTexture(&texture);
						}
					}
				}

	}
	return 0;
}

bool isInside(sf::RectangleShape c, sf::RectangleShape a)
{
	sf::RectangleShape card = c;
	sf::RectangleShape area = a;

	if (area.getGlobalBounds().contains(card.getPosition()) && area.getGlobalBounds().contains(card.getPosition()+card.getSize()))
	{
		return true;
	}
	else
		return false;
}

sf::Vector2f reverse(sf::Vector2f v)
{
	sf::Vector2f vector = v;
	vector.x = vector.x*-1;
	vector.y = vector.y*-1;
	return vector;
}
void printNumber(int n)
{
	std::cout << "Current mode: ";
	if (n == 0)
	{
		std::cout << "Manipulate" << std::endl;
	}
	else if ( n == 1)
	{
		std::cout << "Set size" << std::endl;
	}
	else if ( n == 2)
	{
		std::cout << "Select & set position" << std::endl;
	}
	else if ( n == 3)
	{
		std::cout << "Create counter" << std::endl;
	}
	else if ( n == 4)
	{
		std::cout << "Select & set size" << std::endl;
	}
	else if ( n == 5)
	{
		std::cout << "Create & set size" << std::endl;
	}
	else
	{
		std::cout << "Unknown mode, add it to list" <<std::endl;
	}

}
std::vector<sf::RectangleShape> createGrid(sf::RectangleShape rs, sf::Vector2f coords)
{
sf::RectangleShape rect = rs;
std::vector<sf::RectangleShape> rectVect;
rect.setSize(sf::Vector2f(cardSizeX,cardSizeY));
rect.setPosition(coords);
rect.setFillColor(sf::Color::Transparent);
rect.setOutlineColor(sf::Color::Green);
rect.setOutlineThickness(1);
	for (int i = 0; i < cardAmountX; i++)
	{
		
		for (int j = 0; j <cardAmountY; j++)
		{
			rectVect.push_back(rect);
			rect.setPosition(rect.getPosition().x+rect.getSize().x,rect.getPosition().y);
		}
		rect.setPosition(coords.x,rect.getPosition().y+rect.getSize().y);
	}
	return rectVect;
}
std::vector<sf::RectangleShape> createButtons(sf::Vector2f pos)
{
	std::vector<sf::RectangleShape> s;
	for (int i = 0; i < 4; i++)
	{
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(250,50));
		shape.setPosition(pos.x,pos.y+i*100);
		shape.setFillColor(sf::Color(100,50,200));
		s.push_back(shape);
	}
	return s;
}
void writeFile(std::string fileName, int cards[],int amount,float width, float height)
{
	std::ofstream outputFile(fileName,std::ios::binary|std::ios::out);
	CardInfo cardinfo(width,height,amount);
	cardinfo.setCardAmount(cards);	// vois yhist‰‰ konstruktoriin.

	if(outputFile)
	{
		outputFile.write( (char*)&cardinfo,sizeof(CardInfo));
	}
	outputFile.close();
}