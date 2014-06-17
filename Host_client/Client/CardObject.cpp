#include "CardObject.h"


CardObject::CardObject(Card card,sf::Texture texture,sf::Font font)
{
	_suitTexture = new sf::Texture;
	_text = new sf::Text;
	*_suitTexture = texture;
	suit = card.suit;
	value = card.value;
	_suitSprite.setTexture(*_suitTexture);
	_font = new sf::Font;
	*_font = font;
	_text->setFont(*_font);
	init();
	_selected = false;
}

void CardObject::select()
{	
	if(!_selected)
	{
	_selected = true;
	_shape.setFillColor(sf::Color::Green);
	}
	else
	{
	_selected = false;
	_shape.setFillColor(sf::Color::White);
	}

}

void CardObject::setSize(sf::Vector2f size)
{
	_shape = sf::RectangleShape(size);
	_text->setCharacterSize(size.y*0.175f);
	float scale = (size.x*0.25f)/_suitSprite.getGlobalBounds().width;
	_suitSprite.scale(scale, scale);
}

void CardObject::setPosition(sf::Vector2f position)
{
	_shape.setPosition(position);
	_suitSprite.setPosition(position);

	if(_text->getRotation() == 0)
	_text->setPosition(position.x,position.y + _suitSprite.getGlobalBounds().height);

	else if(_text->getRotation() == 90)
		_text->setPosition(position.x-_suitSprite.getGlobalBounds().height,position.y);

	else if(_text->getRotation() == 180)
		_text->setPosition(position.x,position.y-_suitSprite.getGlobalBounds().height);

	else if(_text->getRotation() == 270)
		_text->setPosition(position.x + _suitSprite.getGlobalBounds().height,position.y);
}

void CardObject::setRotation(float angle)
{
	_shape.setRotation(angle);
	_suitSprite.setRotation(angle);
	_text->setRotation(angle);
}

void CardObject::init()
{
	_suitSprite.setPosition(_shape.getPosition());
	_text->setPosition(_shape.getPosition().x, _shape.getPosition().y + _suitSprite.getGlobalBounds().height);
	
	if(suit == SPADES) //: (
		{
			_suitSprite.setTextureRect(sf::IntRect(0,0,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			_text->setColor(sf::Color::Black);
		}
		else if(suit == HEARTS)
		{
			_suitSprite.setTextureRect(sf::IntRect(_suitTexture->getSize().x*0.5f,0,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			_text->setColor(sf::Color::Red);
		}
		else if(suit == CLUBS)
		{
			_suitSprite.setTextureRect(sf::IntRect(0,_suitTexture->getSize().y*0.5f,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			_text->setColor(sf::Color::Black);
		}
		else if(suit == DIAMONDS)
		{
			_suitSprite.setTextureRect(sf::IntRect(_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f,_suitTexture->getSize().x*0.5f,_suitTexture->getSize().y*0.5f));
			_text->setColor(sf::Color::Red);
		}

		std::stringstream ss;
		ss<<value;
		std::string cardValue = ss.str();
		_text->setString(cardValue);
}

void CardObject::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
	window.draw(_suitSprite);
	window.draw(*_text);
}

CardObject::~CardObject(void)
{
}