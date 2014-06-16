#pragma once
#include "Hand.h"
#include "CardObject.h"
#include "ButtonObject.h"
#include <SFML\Graphics.hpp>
class UserInterface
{
public:
	UserInterface(sf::RenderWindow &window);
	~UserInterface(void);

	void draw();
	void addCards(Hand cards);
	void removeCards(Hand cards);
	void addButton(std::string string);
	void addButton(std::string string, sf::Texture texture);
	bool checkInput();
	Hand getSelected();
private:
	void lineUpCards();
	void lineUpButtons();
	sf::Font *_cardFont;
	sf::RectangleShape _button;
	sf::RenderWindow &_window;
	sf::Texture *_suitTexture;
	std::vector<CardObject>_cardObjects;
	std::vector<ButtonObject>_buttons;
	sf::FloatRect _cardArea;
	sf::FloatRect _buttonArea;
};