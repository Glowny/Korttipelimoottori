#include "Editor.h"


Editor::Editor(void):window(sf::RenderWindow(sf::VideoMode(1600,1100), "Editor"))
{
	inputOn = 0;
	//luodaan napit
	sf::RectangleShape button;
	button.setSize(sf::Vector2f(150,50));
	button.setFillColor(sf::Color(200,100,40));
	button.setOutlineColor(sf::Color(150,22,77));
	for (int i = 0; i < 4; i++)
	{
		button.setPosition(window.getSize().x-150,200+100*i);
		buttons.push_back(button);
	}
	font.loadFromFile("Amble-Regular.ttf");
}


Editor::~Editor(void)
{
}

void Editor::run()
{
		//temporary//
		gridAmount.x = 6;
		gridAmount.y = 9;
		gridSize.x = 200;
		gridSize.y = 200;
		std::string filename = "vesa.png";
		bool keyPressed = 0;
		mousePressed = 0;
		//temporary//
	while (window.isOpen())
	{
		mousePos  = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));
		window.clear();
		draw();
		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (keyPressed == 0 )
				{
					setImage(filename);
					setGrid();
					keyPressed = 1;
				}
			}
			else
			keyPressed = 0;
			buttonActions();
		
			}
		}
	}
}
void Editor::save()
{

}

void Editor::setImage(std::string fileName)
{
	pictureTexture.loadFromFile(fileName);
	picture.setTexture(&pictureTexture);
	picture.setSize(sf::Vector2f(pictureTexture.getSize()));
	picture.setPosition(0,0);
	picture.setOutlineColor(sf::Color::Blue);
	picture.setOutlineThickness(2);
}
void Editor::resizeImage(float multiplier)
{
	picture.setSize(picture.getSize()*multiplier);
}
void Editor::draw()
{
	window.draw(picture);
	for (int i = 0; i < grid.size(); i++)
	{
		window.draw(grid[i]);
	}
	for (int i = 0; i < buttons.size(); i++)
	{
		window.draw(buttons[i]);
	}
	// button text drawing

}
void Editor::setGrid()
{
	sf::Vector2f imagePos = picture.getPosition();
	grid.clear();
	for (int i = 0; i <= gridAmount.x; i++)
	{
		sf::VertexArray tempVA(sf::Lines, 2);
		tempVA[0].color = sf::Color::Green;
		tempVA[1].color = sf::Color::Green;
		tempVA[0].position = sf::Vector2f(imagePos.x+gridSize.x*i,imagePos.y);	//alkupiste
		tempVA[1].position = sf::Vector2f(imagePos.x+gridSize.x*i, imagePos.y+gridAmount.y*gridSize.y);	// loppupiste
		grid.push_back(tempVA);
	}
	for (int j = 0; j <= gridAmount.y; j++)
	{
		sf::VertexArray tempVA(sf::Lines, 2);
		tempVA[0].color = sf::Color::Green;
		tempVA[1].color = sf::Color::Green;
		tempVA[0].position = sf::Vector2f(imagePos.x,imagePos.y+gridSize.y*j);	//alkupiste
		tempVA[1].position = sf::Vector2f(imagePos.x+gridAmount.x*gridSize.x, imagePos.y+gridSize.y*j);	// loppupiste
		grid.push_back(tempVA);
	}
}
void Editor::setGridAmount(sf::Vector2i amount)
{
	gridAmount = amount;
}
void Editor::setGridSize(sf::Vector2f size)
{
	gridSize = size;
}

void Editor::buttonActions()
{
	
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
	bool contains = 0;
	for (int i = 0; i < buttons.size(); i++)
	{
		
		if (buttons[i].getGlobalBounds().contains(mousePos))
		{
				if (mousePressed == 0)
				{
					inputTarget = i;
					inputOn = -1;
					mousePressed =1;
					contains = 1;
					if (i == 0)
					{
						numberInput = gridAmount.x;
					}
					else if (i == 1)
					{
						numberInput = gridAmount.y;
					}
					else if (i == 2)
					{
						numberInput = gridSize.x;
					}
					else if (i == 3)
					{
						numberInput = gridSize.y;
					}
				}
		}
		
	}
	if (contains == 0)
	{
		inputOn = 0;
	}


else
	{
		mousePressed = 0;
	}
	// jos muutoksia, päivitä gridi
	if (mousePressed == 1)
		setGrid();
}
}