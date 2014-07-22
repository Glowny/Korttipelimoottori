#include "CardObject.h"


CardObject::CardObject(sf::Texture *texture,sf::IntRect textureRect)
{
	_sprite.setTexture(*texture);
	_sprite.setTextureRect(textureRect);
	_textureRect = textureRect;
	handed = false;
}

void CardObject::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
}

void CardObject::changeTexture(sf::IntRect textureRect)
{
	_sprite.setTextureRect(textureRect);
}

void CardObject::swapTexture()
{
	if(_sprite.getTextureRect() == _backRect)
	{
		_sprite.setTextureRect(_textureRect);
		faceDown = false;
	}
	else
	{
		_sprite.setTextureRect(_backRect);
		faceDown = true;
	}
}

void CardObject::inHand(bool isOwn)
{
	handed = true;

	if(isOwn)
		_sprite.setTextureRect(_textureRect);
	else
		_sprite.setTextureRect(_backRect);
}

void CardObject::remember()
{
	handed = false;

	if(faceDown)
		_sprite.setTextureRect(_backRect);
	else
		_sprite.setTextureRect(_textureRect);
}

CardObject::~CardObject(void)
{
}
