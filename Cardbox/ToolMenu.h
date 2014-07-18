#pragma once
#include "SFML\Graphics.hpp"
#include "ButtonObject.h"
#include "AssetLoader.h"
#include <vector>
class ToolMenu
{
public:
	ToolMenu(AssetLoader &al,sf::Vector2u windowSize);
	void draw(sf::RenderWindow &window);
	~ToolMenu(void);
private:
	sf::Font font;
	AssetLoader &assLoad;
	sf::RectangleShape area;
	std::vector<ButtonObject>buttons;

};


