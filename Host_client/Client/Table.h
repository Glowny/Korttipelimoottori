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
	void addToTable(int index,Hand h);
	void setToTable(int index,Hand h);
	void drawTable();
	void removeFromTable(int index,Hand h);
	void removeFromHand(int playerIndex, int cards);
	void setOwnIndex(int i){_ownIndex = i;}
	std::vector<sf::FloatRect> getAreas();
	std::vector<TableArea> getTableAreas(){return _tableAreas;}
	void createAreas(int areaCount);
	void setCardAmounts(std::vector<int> cardAmounts);
	Hand getLastPlayed(int index);

private:
	int _ownIndex;
	std::vector<TableArea>_tableAreas;
	std::vector<TableArea>_handAreas;
	sf::RenderWindow &_window;
	std::vector<int> _cardAmounts;
	int borderPixels;
};

