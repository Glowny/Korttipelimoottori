#pragma once
#include "SFML\Graphics.hpp"
//#include <iostream>
#include <string>
#include "Explosion.h"
#include <vector>
class PopUp
{
public:
	PopUp(sf::Font font,std::string message,sf::Vector2f position,sf::Vector2f size,int time);
	bool draw(sf::RenderWindow &window);
	~PopUp(void);
private:
	std::vector<Explosion>_explosions;
	sf::RectangleShape _shape;
	sf::Text _text;
	sf::Font *_font;
	sf::Clock _timer;
	sf::Clock _timer2;
	bool wantsToDie;
	int trigger;
	float delay;
	int _time;
};
