#include "Table.h"


Table::Table(sf::RenderWindow &window):_window(window)
{
	sf::Vector2u size = _window.getSize();

	_tableAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,0.575f*size.y-5,0.25f*size.x,0.175*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,5,0.25f*size.x,0.175*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.825f*size.x-5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	//KESKUSTA
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0.25f*size.y,0.49f*size.x,0.24f*size.y),PILE));
	
}

void Table::addToTable(std::string player,Hand h)
{
	if(player.size() == 0)
		_tableAreas[_tableAreas.size()-1].addCards(h, _window);


	for(int i = 0; i < _players.size();i++)
	{
		if(player == _players[i])
		{
			_tableAreas[i].addCards(h,_window);
		}
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

std::vector<sf::FloatRect> Table::getAreas()
{
	std::vector<sf::FloatRect>temp_vect;

	for(int i = 0; i < _tableAreas.size();i++)
	{
		temp_vect.push_back(_tableAreas[i]._area);
	}
	return temp_vect;
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