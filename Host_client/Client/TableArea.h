#pragma once
#include <SFML\Graphics.hpp>
#include "Hand.h"
class TableArea
{
public:
	TableArea(sf::FloatRect area,sf::Vector2u windowsize);
	~TableArea(void);
	void addCards(Hand handoftheking);
	void removeCards(Hand cards);
	void lineUp();
	void draw(sf::RenderWindow &window);
private:
	sf::FloatRect _area;
	Hand _cardDisplay;
	sf::Vector2u _windowSize;
	std::vector<sf::RectangleShape>_cardShapes;
	sf::Font _cardFont;
	sf::Texture *_suitTexture;
	sf::Sprite _suitSprite;
};

