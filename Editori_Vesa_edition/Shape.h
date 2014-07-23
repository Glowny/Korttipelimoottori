#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class Shape
{
public:
	Shape(sf::RectangleShape s, int t){rect = s; type = t;side = 1;}
	Shape(sf::RectangleShape s, int t, int n){rect = s; type = t;side = 1; number = n;}
	~Shape(void);
	sf::RectangleShape rect;
	int type;
	bool side;
	int number;
};

