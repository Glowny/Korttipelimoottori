#include "drawThread.h"


drawThread::drawThread(std::vector<sf::FloatRect> *v, std::vector<sf::Vector2i>& bv)
{

	drawVector = v;
	stateVector = bv;

}
void drawThread::draw()
{
	sf::RenderWindow window(sf::VideoMode(500,500),"Kakka kökkäre");	
	wWindow = &window;

	sf::Clock clock;

		sf::RectangleShape shape(sf::Vector2f(50,50));
		shape.setFillColor(sf::Color::Blue);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Black);
			sf::Time elapsed = clock.getElapsedTime();
			sf::Time limit = sf::milliseconds(10);
			if( elapsed>limit )
			{
				clock.restart();
				for(int i = 0; i <drawVector->size(); i++)
				{
					if (drawVector->at(i).height > 35 && drawVector->at(i).width > 35)
					{
						drawVector->at(i).height = drawVector->at(i).height-1;
						drawVector->at(i).width = drawVector->at(i).width-1;
					}
				}
			}


			for (int i = 0; i <drawVector->size(); i++)
			{
				shape.setPosition(drawVector->at(i).left,drawVector->at(i).top);
				shape.setSize(sf::Vector2f(drawVector->at(i).width,drawVector->at(i).height));
				window.draw(shape);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(checkCoords())
					{
						int location = findObject();
						drawVector->at(location).left=sf::Mouse::getPosition(window).x-25;
						drawVector->at(location).top=sf::Mouse::getPosition(window).y-25;
						drawVector->at(location).height = 50;
						drawVector->at(location).width = 50;
					}
			}
			window.display();
		}
	}

drawThread::~drawThread(void)
{
}

bool drawThread::checkCoords()
{
	float mouseX = sf::Mouse::getPosition(*wWindow).x;
	float mouseY = sf::Mouse::getPosition(*wWindow).y;

	std::cout << mouseY <<", " << mouseX << std::endl;
	for(int i = 0; i < drawVector->size(); i++)
	{
		float tempX = drawVector->at(i).left;
		float tempY = drawVector->at(i).top;
		float width = drawVector->at(i).width;
		float height = drawVector->at(i).height;

		if (mouseX < tempX+width && mouseY < tempY+height && mouseX > tempX && mouseY > tempY)
		{
			return 1;
		}
		
	}
return 0;
}

int drawThread::findObject()
{
	float mouseX = sf::Mouse::getPosition(*wWindow).x;
	float mouseY = sf::Mouse::getPosition(*wWindow).y;


	for(int i = 0; i < drawVector->size(); i++)
	{
		float tempX = drawVector->at(i).left;
		float tempY = drawVector->at(i).top;
		float width = drawVector->at(i).width;
		float height = drawVector->at(i).height;

		if (mouseX < tempX+width && mouseY < tempY+height && mouseX > tempX && mouseY > tempY)
		{
			return i;
		}
		
	}
	return 0; // ei pitäs koskaa tapahtua, tätä ei saa kutsua ennen kun checkcoords o
}