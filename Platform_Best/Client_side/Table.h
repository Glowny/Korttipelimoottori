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
	void setToTable(std::string player,Hand h);
	void drawTable();
	void removeFromTable(std::string player,Hand h);
	void removeFromHand(std::string player, int cards);
	void addPlayer(std::string player);
	std::vector<sf::FloatRect> getAreas();
	std::vector<TableArea> getTableAreas(){return _tableAreas;}
	std::vector<std::string> getPlayers(){return _players;}
	void createAreas(int areaCount);
	void setCardAmounts(std::vector<int> cardAmounts, std::string id);

private:
	std::vector<std::string>_players;
	std::vector<TableArea>_tableAreas;
	std::vector<TableArea>_handAreas;
	sf::RenderWindow &_window;
	std::vector<int> _cardAmounts;
	int borderPixels;
};

