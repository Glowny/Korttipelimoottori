#pragma once
#include "Hand.h"
#include <SFML\Graphics.hpp>
class UserInterface
{
public:
	UserInterface(void);
	~UserInterface(void);
private:
	Hand _hand;
	std::vector<sf::RectangleShape>_cardShapes;
};

