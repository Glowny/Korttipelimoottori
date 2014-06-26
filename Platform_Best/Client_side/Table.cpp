#include "Table.h"


Table::Table(sf::RenderWindow &window):_window(window)
{
}

void Table::createAreas(int areaCount)
{
	sf::Vector2u size = _window.getSize();

	std::vector<TableArea> possibleAreas;

	possibleAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,0.575f*size.y-5,0.25f*size.x,0.175*size.y),POTATO));
	possibleAreas.push_back(TableArea(sf::FloatRect(5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	possibleAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,5,0.25f*size.x,0.175*size.y),POTATO));
	possibleAreas.push_back(TableArea(sf::FloatRect(0.825f*size.x-5,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	
	if(areaCount > 1)
	{
		for(int i = 0; i < areaCount -1; i++)
		{
			_tableAreas.push_back(possibleAreas[i]);
		}
	}

	//KESKUSTA
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0.25f*size.y,0.49f*size.x,0.24f*size.y),PILE));
}

void Table::addToTable(std::string player,Hand h)
{
	if(player.size() == 0)
		_tableAreas[_players.size()].addCards(h, _window);
	else
	{
		for(int i = 0; i < _players.size();i++)
		{
			if(player == _players[i])
				_tableAreas[i].addCards(h, _window);
		}
	}

}

void Table::setToTable(std::string player,Hand h)
{
	if(player.size() == 0)
	{
		_tableAreas[_players.size()].clearArea();
		_tableAreas[_players.size()].addCards(h, _window);
	}
	else
	{
		for(int i = 0; i < _players.size();i++)
		{
			if(player == _players[i])
			{
				_tableAreas[i].clearArea();
				_tableAreas[i].addCards(h, _window);
			}
		}
	}
}

void Table::removeFromTable(std::string player, Hand h)
{
	if(player.size() == 0)
		_tableAreas[_players.size()].removeCards(h);

	else
	{
		for(int i = 0; i < _players.size(); i++)
		{
			if(player == _players[i])
				_tableAreas[i].removeCards(h);
		}
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