#pragma once
#include "SFML\Graphics.hpp"
#include <string>
class ButtonObject
{
public:
	ButtonObject(sf::Font font,std::string string);
	ButtonObject(sf::Font font,std::string string, sf::Texture texture);
	~ButtonObject(void);

	void draw(sf::RenderWindow &window);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	sf::FloatRect getArea();
private:
	sf::Text _text;
	sf::RectangleShape _shape;
	sf::Sprite _sprite;
	sf::Font* _font;
};