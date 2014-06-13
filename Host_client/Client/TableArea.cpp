#include "TableArea.h"
#include <sstream>


TableArea::TableArea(sf::FloatRect area,sf::Vector2u windowsize)
{
	_area = area;
	_windowSize = windowsize;
	_suitTexture = new sf::Texture;
	if((*_suitTexture).loadFromFile("suits_tilemap.png"))
		std::cout << "suits loaded succesfully" << std::endl;
	_cardFont.loadFromFile("comic.ttf");
	_suitSprite.setTexture(*_suitTexture);
}

void TableArea::lineUp()
{ 
	float width = _area.width;
	float height = _area.height;

	if(_cardDisplay.hand.size()>0)
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
		sf::Text text;
		text.setFont(_cardFont);
		text.setCharacterSize(32);
		text.setPosition(_cardShapes[i].getPosition().x, _cardShapes[i].getPosition().y + 32.f);

		window.draw(_cardShapes[i]);
		if(_cardDisplay.hand[i].suit == Spades) //toimii :DDDDdd
		{
			_suitSprite.setTextureRect(sf::IntRect(0,0,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			text.setColor(sf::Color::Black);
		}
		else if(_cardDisplay.hand[i].suit == Hearts)
		{
			_suitSprite.setTextureRect(sf::IntRect(_suitTexture->getSize().x*0.5f,0,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			text.setColor(sf::Color::Red);
		}
		else if(_cardDisplay.hand[i].suit == Clubs)
		{
			_suitSprite.setTextureRect(sf::IntRect(0,_suitTexture->getSize().y*0.5f,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			text.setColor(sf::Color::Black);
		}
		else if(_cardDisplay.hand[i].suit == Diamonds)
		{
			_suitSprite.setTextureRect(sf::IntRect(_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			text.setColor(sf::Color::Red);
		}
		_suitSprite.setPosition(_cardShapes[i].getPosition());
		window.draw(_suitSprite);

		std::stringstream ss;
		ss<<_cardDisplay.hand[i].value;
		std::string cardValue = ss.str();
		text.setString(cardValue);
		window.draw(text);

		
	}
}

void TableArea::removeCards(Hand cards)
{
	bool erased;

	for(int i = 0; i < _cardDisplay.hand.size();)
	{
		erased = false;
		for(int j = 0; j < cards.hand.size();j++)
		{
			if(cards.hand[j] == _cardDisplay.hand[i])
			{
				std::cout << "Deleted: " << _cardDisplay.hand[i].suit << std::endl
						<<	_cardDisplay.hand[i].value << std::endl;
				_cardDisplay.hand.erase(_cardDisplay.hand.begin()+i);
				_cardShapes.erase(_cardShapes.begin()+i);
				erased = true;
			}
		}
		if(!erased)
			i++;
		
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