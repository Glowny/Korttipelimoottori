#include "TableArea.h"


TableArea::TableArea(sf::FloatRect area,sf::Vector2u windowsize)
{
	_area = area;
	_windowSize = windowsize;
}

void TableArea::lineUp()
{ 
	float width = _area.width;
	float height = _area.height;
	width/=_cardDisplay.hand.size();

	for(int i = 0; i < _cardShapes.size();i++)
	{
		_cardShapes[i].setPosition(_area.left+i*width,_area.top+height*0.5f);
	}
}



void TableArea::draw(sf::RenderWindow &window)
{
	for(int i = 0; i < _cardShapes.size();i++)
	{
		window.draw(_cardShapes[i]);
	}
}

void TableArea::removeCards(Hand cards)
{
	for(int i = 0; i < _cardDisplay.hand.size();)
	{
		for(int j = 0; j < cards.hand.size();j++)
		{
			if(cards.hand[j] == _cardDisplay.hand[i])
			{
				_cardDisplay.hand.erase(_cardDisplay.hand.begin()+i);
				_cardShapes.erase(_cardShapes.begin()+i);
			}
			else
			i++;
		}
		
	}
	lineUp();
}

void TableArea::addCards(Hand nedstark)
{
	for(int i = 0; i < nedstark.hand.size();i++)
	{
		_cardDisplay.hand.push_back(nedstark.hand[i]);
		_cardShapes.push_back(sf::RectangleShape(sf::Vector2f(50,100)));
	}
	lineUp();
}

TableArea::~TableArea(void)
{

}
