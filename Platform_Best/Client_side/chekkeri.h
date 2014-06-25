#pragma once
#include "Table.h"


bool check(Card c, Hand h, Table t)
{
	if(t.getTableAreas()[0].getCards().hand.size() > 0)
	{
		if (c.value < t.getTableAreas()[0].getCards().hand[t.getTableAreas()[0].getCards().hand.size()-1].value)
		{
			return true;
		}
		else
			return false;
		}
	return true;
}