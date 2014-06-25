#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>

class DropDown
{
public:
	DropDown(sf::RenderWindow &window, std::string name,sf::Font &font, sf::Vector2f size, sf::Vector2f position);
	~DropDown(void);
	void pushOption(std::string name);
	void draw();
	sf::FloatRect getBounds(){return _shapes[0].getGlobalBounds();}
	sf::FloatRect getBounds(int index){return _shapes[index].getGlobalBounds();}
	void setActive(){_active = true;}
	void setPassive(){_active = false;}
	bool isActive(){return _active;}
	int size(){return _shapes.size();}
	void makeSelection(int index);
	void makeBlue(int index,bool hover);
private:
	bool _active;
	void arrange(sf::Text &text,sf::RectangleShape &shape);
	std::vector<sf::RectangleShape>_shapes;
	std::vector<std::string> _names;
	std::vector<sf::Text>_texts;
	sf::Font &_font;
	sf::RenderWindow &_window;
};
