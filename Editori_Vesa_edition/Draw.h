#pragma once
#include <SFML\Graphics.hpp>
#include "MouseExplosion.h"
#include <vector>
class Draw
{
public:
	Draw(std::vector<sf::RectangleShape*>&sV, sf::RenderWindow &w, std::vector<MouseExplosion>&explosions);
	~Draw(void);
	void DrawStuff();
private:
	std::vector<sf::RectangleShape*> &shapeVector;
	sf::RenderWindow &window;
	std::vector<MouseExplosion>&_explosions;
};

