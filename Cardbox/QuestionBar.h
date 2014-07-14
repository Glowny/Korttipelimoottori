#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
class QuestionBar
{
public:
	void draw(sf::RenderWindow &window);
	QuestionBar(){}
	QuestionBar(std::string who, std::string what,sf::Vector2f pos);
	int checkClick(sf::Vector2i pos);
	void setPos(sf::Vector2f pos);
	~QuestionBar(void);
private:
	void arrange();
	sf::RectangleShape bar,yesbar,nobar;
	sf::Text question,yes,no;
};