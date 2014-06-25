#include "Table.h"


Table::Table(sf::RenderWindow &window):_window(window)
{
	sf::Vector2u size = _window.getSize();

	//KESKUSTA
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0.25f*size.y,0.49f*size.x,0.24f*size.y),PILE));

	_tableAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,0.575f*size.y-5,0.25f*size.x,0.175*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,5,0.25f*size.x,0.175*size.y),POTATO));
	_tableAreas.push_back(TableArea(sf::FloatRect(0.825f*size.x-5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	
	
}

void Table::addToTable(std::string player,Hand h)
{
	if(player.size() == 0)
		_tableAreas[0].addCards(h, _window);
	else
	{
		for(int i = 0; i < _players.size();i++)
		{
			if(player == _players[i])
				_tableAreas[i+1].addCards(h, _window);
		}
	}

}

void Table::removeFromTable(std::string player, Hand h)
{
	for(int i = 0; i < _players.size(); i++)
	{
		if(player == _players[i])
			_tableAreas[i+1].removeCards(h);
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