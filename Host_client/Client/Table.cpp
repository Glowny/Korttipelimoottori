#include "Table.h"


Table::Table(sf::RenderWindow &window):_window(window)
{
	borderPixels = 50;
	sf::Vector2u size = _window.getSize();

	_handAreas.push_back(TableArea(sf::FloatRect(0,0.25f*size.y,borderPixels,0.25*size.y),POTATO));
	_handAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,0,0.25f*size.x,borderPixels),POTATO));
	_handAreas.push_back(TableArea(sf::FloatRect(size.x-borderPixels,0.25f*size.y,borderPixels,0.25*size.y),POTATO));
}

Hand Table::getLastPlayed(int index)
{
	return _tableAreas[index].getLastPlayed();

}

void Table::createAreas(int areaCount)
{
	sf::Vector2u size = _window.getSize();
	std::vector<TableArea> possibleAreas;

	possibleAreas.push_back(TableArea(sf::FloatRect(borderPixels,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	possibleAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,borderPixels,0.25f*size.x,0.175*size.y),POTATO));
	possibleAreas.push_back(TableArea(sf::FloatRect(0.825f*size.x-borderPixels,0.25f*size.y,0.175f*size.x,0.25*size.y),POTATO));
	
	int j = 0;

	if(areaCount > 1)
	{
		for(int i = 0; i < areaCount -1; i++)
		{
			if(i == _ownIndex)
				_tableAreas.push_back(TableArea(sf::FloatRect(0.375f*size.x,0.575f*size.y-5,0.25f*size.x,0.175*size.y),POTATO));
			else
			{
			_tableAreas.push_back(possibleAreas[j]);
			j++;
			}
		}
	}

	//KESKUSTA
	_tableAreas.push_back(TableArea(sf::FloatRect(0.25f*size.x,0.25f*size.y,0.49f*size.x,0.24f*size.y),PILE));
}

void Table::addToTable(int index,Hand h)
{
	_tableAreas[index].addCards(h, _window);
}

void Table::setToTable(int index,Hand h)
{
	if(_tableAreas.size() == 1)
	{
		_tableAreas[0].clearArea();
		_tableAreas[0].addCards(h, _window);
	}
	else
	{
	_tableAreas[index].clearArea();
	_tableAreas[index].addCards(h, _window);
	}
}

void Table::removeFromTable(int index, Hand h)
{
	_tableAreas[index].removeCards(h);
}

void Table::removeFromHand(int playerIndex, int cards)
{
	int index = playerIndex;
	if(index > _ownIndex)
		index--;
	_handAreas[index].removeCards(cards);
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

void Table::setCardAmounts(std::vector<int> cardAmounts)
{
	int j = 0;

	for(int i = 0; i < cardAmounts.size(); i++)
	{
		if(i != _ownIndex)
		{
			_handAreas[j].addCards(cardAmounts[i], _window);
			j++;
		}
	}
}

void Table::drawTable()
{
	for(int i = 0; i < _tableAreas.size();i++)
	{
		_tableAreas[i].draw(_window);
	}
	for(int i = 0; i < _handAreas.size(); i++)
	{
		_handAreas[i].draw(_window);
	}
}

Table::~Table(void)
{
}