#pragma once
#include "SFML\Graphics.hpp"
#include <string>
class ButtonObject
{
public:
	ButtonObject(){_font = new sf::Font;};
	ButtonObject(sf::Font font,std::string string);
	ButtonObject(sf::Font font,std::string string, sf::Texture texture);
	~ButtonObject(void);
	
	void draw(sf::RenderWindow &window);
	void setText(sf::Text *text){_text = *text;_text.setColor(sf::Color::Black);arrange();}
	
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	sf::FloatRect getArea();
private:
	void arrange();
	sf::Text _text;
	sf::RectangleShape _shape;
	sf::Sprite _sprite;
	sf::Font* _font;
};
