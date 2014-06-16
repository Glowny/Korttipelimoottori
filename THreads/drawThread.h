#pragma once
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"
class drawThread
{
public:
	drawThread(std::vector<sf::FloatRect> *v, std::vector<sf::Vector2i>& bv);
	~drawThread(void);
	void draw();
	bool checkCoords();
	int findObject();

private:
	sf::Window *wWindow;
	std::vector<sf::FloatRect> *drawVector;
	std::vector<sf::Vector2i> stateVector;
	sf::RectangleShape shape;
};

