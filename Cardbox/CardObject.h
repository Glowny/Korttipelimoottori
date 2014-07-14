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
	void setID(int id){_id = id;}
	int getID(){return _id;}
	sf::Sprite _sprite;
private:
	bool faceDown;
	sf::IntRect _textureRect;
	sf::Uint16 _id;
};

