#pragma once
#include "SFML\Graphics.hpp"
class CardObject
{
public:
	CardObject(sf::Texture *texture,sf::IntRect textureRect);
	~CardObject(void);
	void draw(sf::RenderWindow &window);
	void setBackRect(sf::IntRect backRect){_backRect = backRect;}
	void changeTexture(sf::IntRect textureRect);
	void swapTexture();
	void setID(int id){_id = id;}
	int getID(){return _id;}
	sf::Sprite _sprite;
private:
	bool faceDown;
	sf::IntRect _textureRect,_backRect;
	sf::Uint16 _id;
};

