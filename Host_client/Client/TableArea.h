#pragma once
#include <SFML\Graphics.hpp>
#include "Hand.h"
#include "CardObject.h"

enum LINEUP_STYLE
{
	POTATO,
	PILE
};


class TableArea
{
public:
	TableArea(sf::FloatRect area,LINEUP_STYLE lineup);
	~TableArea(void);
	void addCards(Hand cards, sf::RenderWindow &window);
	void removeCards(Hand cards);
	void draw(sf::RenderWindow &window);
	sf::FloatRect _area;
private:
	LINEUP_STYLE _style;
	void lineUp();
	std::vector<CardObject>_cardObjects;
	sf::Font *_cardFont;
	sf::Texture *_suitTexture;
};