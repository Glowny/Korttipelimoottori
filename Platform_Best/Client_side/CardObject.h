#pragma once
#include "Card.h"
#include "SFML\Graphics.hpp"
#include <sstream>
class CardObject : public Card
{
public:
	CardObject(Card card,sf::Texture texture,sf::Font font);
	~CardObject(void);
	void draw();
	void init();
	sf::FloatRect getArea(){return _shape.getGlobalBounds();}
	void select();
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setRotation(float angle);
	bool _selected;
	void draw(sf::RenderWindow &window);
private:
	sf::RectangleShape _shape;
	sf::Sprite _suitSprite;
	sf::Texture *_suitTexture;
	sf::Font *_font;
	sf::Text *_text;
};