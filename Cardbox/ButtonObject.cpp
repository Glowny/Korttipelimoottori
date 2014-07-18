#include "ButtonObject.h"


ButtonObject::ButtonObject(sf::Font font,std::string string)
{
	_font = new sf::Font;
	*_font = font;
	_text.setFont(*_font);
	_text.setString(string);
	_text.setColor(sf::Color::Black);
}

ButtonObject::ButtonObject(sf::Font font,std::string string, sf::Texture texture)
{
	_font = new sf::Font;
	*_font = font;
	_text.setFont(*_font);
	_text.setString(string);
	_sprite.setTexture(texture);
	_text.setColor(sf::Color::Black);
}

ButtonObject::~ButtonObject(void)
{
}

void ButtonObject::draw(sf::RenderWindow &window)
{

	if(_sprite.getTexture() != NULL)
		window.draw(_sprite);
	else
		window.draw(_shape);

		window.draw(_text);
}

void ButtonObject::setPosition(sf::Vector2f position)
{
	_text.setOrigin(_text.getGlobalBounds().width*0.5f, _text.getGlobalBounds().height*0.5f);

	if(_sprite.getTexture() != NULL)
	{
		_sprite.setPosition(position);
		_text.setPosition(position.x + _sprite.getGlobalBounds().width*0.5f, position.y + _sprite.getGlobalBounds().height*0.5f);
	}
	else
	{
	_shape.setPosition(position);
	_text.setPosition(position.x + _shape.getSize().x*0.5f, position.y + _shape.getSize().y*0.5f);
	}
}

void ButtonObject::setSize(sf::Vector2f size)
{
	if(_sprite.getTexture() != NULL)
	{
		float scaleX = size.x/_sprite.getGlobalBounds().width;
		float scaleY = size.y/_sprite.getGlobalBounds().height;
		_sprite.setScale(scaleX,scaleY);
	}
	else
		_shape = sf::RectangleShape(size);
	_text.setCharacterSize(0.5f*size.y);
	_shape.setOutlineThickness(1.0f);
	_shape.setOutlineColor(sf::Color::Black);
}

sf::FloatRect ButtonObject::getArea()
{
	if(_sprite.getTexture() != NULL)
		return _sprite.getGlobalBounds();
	else
		return _shape.getGlobalBounds();
}