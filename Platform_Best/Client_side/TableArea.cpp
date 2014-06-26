#include "TableArea.h"
#include <sstream>


TableArea::TableArea(sf::FloatRect area,LINEUP_STYLE lineup)
{
	_area = area;
	_style = lineup;
	_cardFont = new sf::Font;
	_suitTexture = new sf::Texture;
	if((*_suitTexture).loadFromFile("suits_tilemap.png"))
		std::cout << "suits loaded succesfully" << std::endl;
	_cardFont->loadFromFile("comic.ttf");
}

void TableArea::lineUp()
{ 
	if(_style == POTATO)
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
				if(_area.top == 5)
				{
					_cardObjects[i].setRotation(180);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left+i*width,(_area.top+_cardObjects[i].getArea().height)));
				}
			}
		
		}
		else
		{
			height/=_cardObjects.size();

			for(int i = 0; i < _cardObjects.size();i++)
			{
			
				if(_area.left == 5)
					{
					_cardObjects[i].setRotation(90);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left+width,_area.top+i*height));
				
					}
				else
				{
					_cardObjects[i].setRotation(270);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left,_area.top+i*height));
				
				}
			}
		}
		}

	}
	else if(_style == PILE)
	{
		float centerx = _area.width*0.5f;
		float centery = _area.height*0.5f;
	
	

		if(_area.width > _area.height)
		{

			for(int i = 0; i < _cardObjects.size();i++)
			{
				_cardObjects[i].setPosition(sf::Vector2f(_area.left+centerx-0.5f*_cardObjects[i].getArea().width,_area.top/*+centery-0.5f*_cardObjects[i].getArea().height*/));
				if(_area.top == 0)
				{
					_cardObjects[i].setRotation(180);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left+centerx-0.5f*_cardObjects[i].getArea().width,(_area.top+_cardObjects[i].getArea().height)));
				}
			}
		
		}
		else
		{


			for(int i = 0; i < _cardObjects.size();i++)
			{
			
				if(_area.left == 0)
					{
					_cardObjects[i].setRotation(90);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left+centerx,_area.top+centery));
				
					}
				else
				{
					_cardObjects[i].setRotation(270);
					_cardObjects[i].setPosition(sf::Vector2f(_area.left,_area.top+0));
				
				}
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

void TableArea::removeCards(int cards)
{
	for(int i = 0; i < cards; i++)
	{
		_cardObjects.pop_back();
	}
	lineUp();
}

void TableArea::clearArea()
{
	_cardObjects.clear();
}

void TableArea::addCards(Hand cards, sf::RenderWindow &window)
{

	sf::Vector2f cardSize = sf::Vector2f(window.getSize().x,window.getSize().y);
	cardSize.x*=0.075f;
	cardSize.y*=0.15f;

	for(int i = 0; i < cards.hand.size();i++)
	{
		_cardObjects.push_back(CardObject(cards.hand[i],*_suitTexture,*_cardFont));
	}

	for(int i = 0; i < _cardObjects.size();i++)
	{

	if(_area.width > _area.height)
	{
	_cardObjects[i].setSize(cardSize);
	}

	else
	_cardObjects[i].setSize(cardSize);
	}

	lineUp();
}

void TableArea::addCards(int cards, sf::RenderWindow &window)
{
	sf::Vector2f cardSize = sf::Vector2f(window.getSize().x,window.getSize().y);
	cardSize.x*=0.0375f;
	cardSize.y*=0.075f;

	for(int i = 0; i < cards;i++)
	{
		_cardObjects.push_back(CardObject(Card(),*_suitTexture,*_cardFont));
	}

	for(int i = 0; i < _cardObjects.size();i++)
	{

	if(_area.width > _area.height)
	{
	_cardObjects[i].setSize(cardSize);
	}

	else
	_cardObjects[i].setSize(cardSize);
	}

	lineUp();
}

Hand TableArea::getCards()
{
	Hand tempH;

	for(int i = 0; i < _cardObjects.size(); i++)
	{
		tempH.hand.push_back(Card(_cardObjects[i].value, _cardObjects[i].suit));
	}

	return tempH;
}

TableArea::~TableArea(void)
{

}