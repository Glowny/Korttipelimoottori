#pragma once
#include "Hand.h"
#include "CardObject.h"
#include "ButtonObject.h"
#include "PopUp.h"
#include "Table.h"
#include <SFML\Graphics.hpp>

enum SELECTION_AREA
{
	NOTHING=-1,
	TABLE_CENTER,
	SECONDARY_CARDS,
};

class UserInterface
{
public:
	UserInterface(sf::RenderWindow &window, Table &table);
	~UserInterface(void);

	void draw();
	void addCards(Hand cards);
	void removeCards(Hand cards);
	void addButton(std::string string);
	void addButton(std::string string, sf::Texture texture);
	bool checkInput();
	Hand getSelected();
	int getSelectedArea(){return _selectedArea;}
	void init(std::vector<sf::FloatRect>areas);
	void endScreen(std::string player,std::string message,bool victory);
private:
	int _selectedArea;
	void lineUpCards();
	void lineUpButtons();
	sf::Font *_cardFont;
	sf::RectangleShape _button;
	sf::RenderWindow &_window;
	sf::Texture *_suitTexture;
	std::vector<CardObject>_cardObjects;
	Hand _cards;
	std::vector<ButtonObject>_buttons;
	sf::FloatRect _cardArea,_buttonArea;
	std::vector<sf::RectangleShape> _borders;
	std::vector<PopUp> _popUps;
	Table &_table;
};