#include "Table.h"


Table::Table(sf::RenderWindow &window):_window(window)
{
	sf::Vector2u size = window.getSize();
	
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0.75f*size.y,0.5f*size.x,0.25*size.y),size));
	_tableAreas.push_back(TableArea(sf::FloatRect(0,0.25f*size.y,0.25f*size.x,0.5*size.y),size));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0,0.5f*size.x,0.25*size.y),size));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.75f*size.x,0.25f*size.y,0.25f*size.x,0.5*size.y),size));
	
}

void Table::addToTable(std::string player,Hand h)
{
	for(int i = 0; i < _players.size();i++)
	{
		if(player == _players[i])
			_tableAreas[i].addCards(h);
	}
}

void Table::removeFromTable(std::string player, Hand h)
{
	for(int i = 0; i < _players.size(); i++)
	{
		if(player == _players[i])
			_tableAreas[i].removeCards(h);
	}
}

void Table::addPlayer(std::string player)
{
	_players.push_back(player);
	
}

void Table::drawTable()
{
	for(int i = 0; i < _tableAreas.size();i++)
	{
		_tableAreas[i].draw(_window);
	}
}




Table::~Table(void)
{
}
