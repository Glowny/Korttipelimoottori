#include "Editor.h"


Editor::Editor(void):window(sf::RenderWindow(sf::VideoMode(1600,1100), "Editor"))
{
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
	text.setCharacterSize(17);
	text.setFont(font);
	text.setColor(sf::Color::Black);
	inputOn = 0;
	oldInputSize = input.size();
	drawMultiplier = 1;
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
		name = "ValtioValta";
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
					setImage(name);
					setGrid();
					int endVal = gridAmount.x*gridAmount.y-cardAmounts.size();
					for (int i = 0; i <endVal; i++)
						{
							cardAmounts.push_back(0);
						}
					keyPressed = 1;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if(keyPressed == 0)
				{
					save();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				if(keyPressed == 0)
				{
					load();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				if(keyPressed == 0)
				{
					drawMultiplier+= 0.01;
					resizeImage(drawMultiplier);
					setGrid();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				if(keyPressed == 0)
				{
					if (drawMultiplier > 0)
					{
						drawMultiplier-= 0.01;
						resizeImage(drawMultiplier);
						setGrid();
					}
				}
			}
			else
			keyPressed = 0;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				bool hits = 0;
				for (int i = 0; i < buttons.size(); i++)
				{
					if(mousePressed == 0)
					{
						if (buttons[i].getGlobalBounds().contains(mousePos))
						{
							input.clear();
							inputOn = 1;
							inputTarget = i;
							hits = 1;
						}
					}
				}
				if (!hits)
				{
					inputOn = 0;
					input.clear();
				}
				if (checkCoords() && cardAmounts.size() != 0)
				{
					cardAmounts[getIndexCoords()]++;
				}
				mousePressed = 1;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (checkCoords() && cardAmounts.size() != 0)
				{
					cardAmounts[getIndexCoords()]--;
				}
				mousePressed = 1;
			}
			else
				mousePressed = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				inputOn = 0;
				input.clear();
			}

			if (event.type == sf::Event::TextEntered && inputOn == 1)
			{
				if (event.text.unicode < 128)
					{
						input.push_back(static_cast<char>(event.text.unicode));
					}
			}


		if (inputOn == 1  && oldInputSize != input.size())
		{
			std::istringstream buffer(input);
			if (inputTarget == 0)
			{
				buffer >> gridAmount.x;
			}
			if (inputTarget == 1)
			{
				buffer >> gridAmount.y;
			}
			if (inputTarget == 2)
			{
				buffer >> gridSize.x;
			}
			if (inputTarget == 3)
			{
				buffer >> gridSize.y;
			}
			oldInputSize = input.size();
			int endVal = gridAmount.x*gridAmount.y-cardAmounts.size();
			for (int i = 0; i <endVal; i++)
			{
				cardAmounts.push_back(0);
			}
			setGrid();
		}
		}
	}
}

void Editor::setImage(std::string fileName)
{
	pictureTexture.loadFromFile(fileName+".png");
	picture.setTexture(&pictureTexture);
	picture.setSize(sf::Vector2f(pictureTexture.getSize()));
	picture.setPosition(100,150);
	picture.setOutlineColor(sf::Color::Blue);
	picture.setOutlineThickness(2);
}
void Editor::resizeImage(float multiplier)
{
	picture.setScale(multiplier,multiplier);

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

	// amount of cards;

	
	sf::Text newText = text;
	newText.setColor(sf::Color(100,111,30));
	newText.setCharacterSize(30);

	sf::Vector2f drawGridSize = gridSize;
	drawGridSize.x = drawGridSize.x*drawMultiplier;
	drawGridSize.y = drawGridSize.y*drawMultiplier;

	int paska=0;
	while (cardAmounts.size() > paska)
	{
		for (int j = 0; j < gridAmount.y; j++)
		{
		
			for (int i = 0; i < gridAmount.x; i++)
			{
				std::ostringstream convert;
				newText.setPosition(picture.getPosition().x+drawGridSize.x*i,picture.getPosition().y+drawGridSize.y*j);
				convert << cardAmounts[paska];
				newText.setString(convert.str());
				window.draw(newText);
				paska++;
			}
		}
		break;
	}		
	

	// button text drawing
	std::vector<std::string>texts;
	std::string a("Grid amount X:");
	texts.push_back(a);
	std::string b("Grid amount Y:");
	texts.push_back(b);
	std::string c("Grid size X:");
	texts.push_back(c);
	std::string d("Grid size Y:");
	texts.push_back(d);
	
	if (inputOn == 1)
	{

		for (int i = 0; i < buttons.size(); i++)
		{
			text.setPosition(buttons[i].getPosition());
			std::ostringstream convert;
			if (i != inputTarget)
			{
				if (i == 0 )
				{
					convert << gridAmount.x;
				}
				else if (i == 1)
				{
					convert << gridAmount.y;
				}
				else if (i == 2)
				{
					convert << gridSize.x;
				}
				else if (i == 3)
				{
				convert << gridSize.y;
				}
				text.setString(texts[i]+convert.str());
			}
			else
			{
				text.setString(texts[i]+input);
			}
			window.draw(text);
		}
	}
	else
	{
		for ( int i = 0; i < texts.size(); i++)
		{
				std::ostringstream convert;
				text.setPosition(buttons[i].getPosition());
				if (i == 0 )
				{
					convert << gridAmount.x;
				}
				else if (i == 1)
				{
					convert << gridAmount.y;
				}
				else if (i == 2)
				{
					convert << gridSize.x;
				}
				else if (i == 3)
				{
				convert << gridSize.y;
				}
				text.setString(texts[i]+convert.str());
			window.draw(text);
		}
	}

}
void Editor::setGrid()
{
	sf::Vector2f imagePos = picture.getPosition();
	sf::Vector2f drawGridSize = gridSize;
	drawGridSize.x = drawGridSize.x*drawMultiplier;
	drawGridSize.y = drawGridSize.y*drawMultiplier;
	grid.clear();
	for (int i = 0; i <= gridAmount.x; i++)
	{
		sf::VertexArray tempVA(sf::Lines, 2);
		tempVA[0].color = sf::Color::Green;
		tempVA[1].color = sf::Color::Green;
		tempVA[0].position = sf::Vector2f(imagePos.x+drawGridSize.x*i,imagePos.y);	//alkupiste
		tempVA[1].position = sf::Vector2f(imagePos.x+drawGridSize.x*i, imagePos.y+gridAmount.y*drawGridSize.y);	// loppupiste
		grid.push_back(tempVA);
	}
	for (int j = 0; j <= gridAmount.y; j++)
	{
		sf::VertexArray tempVA(sf::Lines, 2);
		tempVA[0].color = sf::Color::Green;
		tempVA[1].color = sf::Color::Green;
		tempVA[0].position = sf::Vector2f(imagePos.x,imagePos.y+drawGridSize.y*j);	//alkupiste
		tempVA[1].position = sf::Vector2f(imagePos.x+gridAmount.x*drawGridSize.x, imagePos.y+drawGridSize.y*j);	// loppupiste
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
void Editor::save()
{
	int size = gridAmount.x*gridAmount.y;
	int* cards;
	cards = new int[size];
	for (int i = 0; i <size;i++)
	{
		cards[i] = cardAmounts[i];
		std::cout << cards[i] << std::endl;
	}
	CardInfo cardInfo(name, gridSize.x,gridSize.y,gridAmount.x*gridAmount.y, cards);
	cardInfo.save();
}
void Editor::setCardAmounts(int* a, int size)
{
	cardAmounts.clear();
	int* tempArray = new int[size];
	tempArray = a;
	for (int i = 0; i < size; i++)
	{
		cardAmounts.push_back(tempArray[i]);	// saattaa olla virhe.
	}
	setGrid();
}
void Editor::load()
{
	setImage(name);
	CardInfo cardInfo(name);
	setCardAmounts(cardInfo.getCards(),cardInfo.getCardAmount());
	int endVal = gridAmount.x*gridAmount.y-cardAmounts.size();
	for (int i = 0; i <endVal; i++)
		{
			cardAmounts.push_back(0);
		}
	setGrid();

}
bool Editor::checkCoords()
{
	sf::Vector2f thisMousePos = mousePos-picture.getPosition();
	if ( thisMousePos.x < gridAmount.x*gridSize.x && thisMousePos.y < gridAmount.y*gridSize.y)
	{
		if ( mousePos.x > picture.getPosition().x && mousePos.y > picture.getPosition().y)
		{
			return true;	
		}
	}
	return false;
}
int Editor::getIndexCoords()
{
	sf::Vector2f thisMousePos = mousePos-picture.getPosition();
	float x = thisMousePos.x/gridSize.x;
	float y = thisMousePos.y/gridSize.y;
	int returnValue;
	int paska=-1;
	std::cout << x << ", " << y << std::endl;
	if (cardAmounts.size() != 0)
	{
		for (int j = 0; j < y; j++)
		{
			paska = gridAmount.x * j;
		}
		for (int i = 1; i< x; i++)
			{
				paska++;
			}
		returnValue = paska;
	}		

	std::cout << "Preessed index " << returnValue << std::endl;
	return returnValue;

}