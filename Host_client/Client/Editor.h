#pragma once
#include "SFML\Graphics.hpp"
#include "DropDown.h"
#include <iostream>
#include "ButtonObject.h"
#include "Explosion.h"
#include "MouseExplosion.h"
#include "CardObject.h"
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
	void newRule();
	void scrollDown(int amount);
	void scrollUp(int amount);
	sf::Vector2f getViewOffset();
	
private:
	sf::Vector2f _viewOffset;
	int rivit;
	sf::RenderWindow _window;
	std::vector<DropDown>_dropDowns;
	sf::Font *_font;
	void arrangeDropDowns();
	ButtonObject plusButton,minusButton;
	std::vector<ButtonObject>_minuses;
	sf::Text *_minus,*_plus;
};

