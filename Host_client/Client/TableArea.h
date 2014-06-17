#pragma once
#include <SFML\Graphics.hpp>
#include "Hand.h"
#include "CardObject.h"

class TableArea
{
public:
	TableArea(sf::FloatRect area);
	~TableArea(void);
	void addCards(Hand cards, sf::RenderWindow &window);
	void removeCards(Hand cards);
	void draw(sf::RenderWindow &window);
private:
	void lineUp();
	sf::FloatRect _area;
	std::vector<CardObject>_cardObjects;
	sf::Font *_cardFont;
	sf::Texture *_suitTexture;
};