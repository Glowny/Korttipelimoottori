#pragma once
#include "SFML\Graphics.hpp"
#include "DropDown.h"
#include <iostream>
class Editor
{
public:
	Editor();
	~Editor(void);
	void draw();
	void run();
	void initialize();
	void checkMouseHover(sf::Vector2i mousepos);
	void checkMouseClick(sf::Vector2i mousepos);
private:
	sf::RenderWindow _window;
	std::vector<DropDown>_dropDowns;
	sf::Font *_font;
};
