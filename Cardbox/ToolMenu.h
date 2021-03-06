#pragma once
#include "SFML\Graphics.hpp"
#include "ButtonObject.h"
#include "AssetLoader.h"
#include <vector>
class ToolMenu
{
public:
	ToolMenu(AssetLoader &al,sf::Vector2u windowSize);
	virtual void draw(sf::RenderWindow &window);
	virtual int checkButtons(sf::Vector2i mousePos);
	virtual ~ToolMenu(void);
protected:
	sf::Font font;
	AssetLoader &assLoad;
	sf::RectangleShape area;
	std::vector<ButtonObject>buttons;
	void arrange(std::vector<ButtonObject>&butts, int placement);
};