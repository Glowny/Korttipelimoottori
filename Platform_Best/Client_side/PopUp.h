#pragma once
#include "SFML\Graphics.hpp"
//#include <iostream>
#include <string>
class PopUp
{
public:
	PopUp(sf::Font font,std::string message,sf::Vector2f position,sf::Vector2f size,int time);
	bool draw(sf::RenderWindow &window);
	~PopUp(void);
private:
	sf::RectangleShape _shape;
	sf::Text _text;
	sf::Font *_font;
	sf::Clock _timer;
	bool wantsToDie;
	int _time;
};
