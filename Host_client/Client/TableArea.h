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
	void addCards(int cards, sf::RenderWindow &window);
	void removeCards(Hand cards);
	void removeCards(int cards);
	void clearArea();
	void draw(sf::RenderWindow &window);
	sf::FloatRect _area;
	Hand getLastPlayed();
	Hand getCards();
private:
	LINEUP_STYLE _style;
	void lineUp();
	std::vector<CardObject>_cardObjects, _latestCards;
	sf::Font *_cardFont;
	sf::Texture *_suitTexture;
};