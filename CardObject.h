#pragma once
#include "SFML\Graphics.hpp"
class CardObject
{
public:
	CardObject(sf::Texture *texture,sf::IntRect textureRect);
	~CardObject(void);
	void draw(sf::RenderWindow &window);
	void changeTexture(sf::IntRect textureRect);
	void resetTexture(){_sprite.setTextureRect(_textureRect);}
	sf::Sprite _sprite;
private:
	bool faceDown;
	sf::IntRect _textureRect;
};

