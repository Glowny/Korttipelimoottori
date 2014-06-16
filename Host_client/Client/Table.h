#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Hand.h"
#include "TableArea.h"

class Table
{
public:
	Table(sf::RenderWindow &window);
	~Table(void);
	void addToTable(std::string player,Hand h);
	void drawTable();
	void removeFromTable(std::string player,Hand h);
	void addPlayer(std::string player);
	std::vector<sf::RectangleShape> getCardRectangles(std::string player);
	void setRectColor(sf::Color color, int rectIndex){_tableAreas[0].setRectColor(color,rectIndex);}

private:
	std::vector<std::string>_players;
	std::vector<TableArea>_tableAreas;
	sf::RenderWindow &_window;

};

