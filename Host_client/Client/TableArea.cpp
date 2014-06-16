#include "TableArea.h"
#include <sstream>


TableArea::TableArea(sf::FloatRect area)
{
	_area = area;
	_cardFont = new sf::Font;
	_suitTexture = new sf::Texture;
	if((*_suitTexture).loadFromFile("suits_tilemap.png"))
		std::cout << "suits loaded succesfully" << std::endl;
	_cardFont->loadFromFile("comic.ttf");
}

void TableArea::lineUp()
{ 
	if(_cardObjects.size()>0)
	{
	float width = _area.width;
	float height = _area.height;
	
	

	if(width > height)
	{
		width/=_cardObjects.size();

		for(int i = 0; i < _cardObjects.size();i++)
		{
			_cardObjects[i].setPosition(sf::Vector2f(_area.left+i*width,_area.top));
			if(_area.top == 0)
				_cardObjects[i].setRotation(180);
		}
		
	}
	else
	{
		height/=_cardObjects.size();

		for(int i = 0; i < _cardObjects.size();i++)
		{
			_cardObjects[i].setPosition(sf::Vector2f(_area.left+width,_area.top+i*height));
			if(_area.left == 0)
				_cardObjects[i].setRotation(90);
			else
				_cardObjects[i].setRotation(270);
		}
	}
	}
}



void TableArea::draw(sf::RenderWindow &window)
{
	for(int i = 0; i < _cardObjects.size(); i++)
	{
		_cardObjects[i].draw(window);
	}
}

void TableArea::removeCards(Hand cards)
{
	bool erased;

	for(int i = 0; i < _cardObjects.size();)
	{
		erased = false;
		for(int j = 0; j < cards.hand.size();j++)
		{
			if(cards.hand[j] == _cardObjects[i])
			{
				std::cout << "Deleted: " << _cardObjects[i].suit << std::endl
						<<	_cardObjects[i].value << std::endl;
				_cardObjects.erase(_cardObjects.begin()+i);
				erased = true;
			}
		}
		if(!erased)
			i++;
		
	}
	lineUp();
}

void TableArea::addCards(Hand cards)
{
	for(int i = 0; i < cards.hand.size();i++)
	{
		_cardObjects.push_back(CardObject(cards.hand[i],*_suitTexture,*_cardFont));
	}

	for(int i = 0; i < _cardObjects.size();i++)
	{

	if(_area.width > _area.height)
	_cardObjects[i].setSize(sf::Vector2f(_area.height*0.5f,_area.height));

	else
	_cardObjects[i].setSize(sf::Vector2f(_area.width*0.5f,_area.width));
	}

	lineUp();
}

TableArea::~TableArea(void)
{

}