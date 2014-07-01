#pragma once
#include "Table.h"


bool clickCheck(Card c, Hand h, Hand selected, Table t)
{
TableArea center = t.getTableAreas()[t.getTableAreas().size()-1];

	if(center.getCards().hand.size() > 0)
	{
		
		Card topCard = center.getCards().hand[center.getCards().hand.size()-1];

		int topValue = topCard.value;
		int cardAmount=1;
		int handCardAmount=0;
		for (int i = center.getCards().size()-2; i >=0; i--)
		{
			if (center.getCards().hand[i].value == topValue)
			cardAmount++;
			else
			break;
		}
		for (int i = 0; i < h.size(); i++)
		{
			if (h.hand[i].value == c.value)
			{
				handCardAmount++;
				//kutsu mua aprikoosiks
			}
		}
		if (handCardAmount < cardAmount)
			return false;
		if (selected.hand.size() == 0)
		{
			if (c.value < topValue)
			{
				return true;
			}
			else
			return false;
		}
		else
		{
			if (selected.hand[0].value == c.value)
			{
				return true; //1
			}
			else
			return false;
		}
		
	}
	else if (selected.hand.size() == 0)
		{
			return true;
		}

		else
		{
			if (selected.hand[0].value == c.value)
			{
				return true; //1
			}
			else
			return false;
		}
}

bool turnEndCheck(Hand selected, Table t)
{
	TableArea center = t.getTableAreas()[t.getTableAreas().size()-1];
	int cardAmount = 1;
	if(selected.size() == 0)
		return true;
	if(center.getCards().hand.size() > 0)
	{
		int topValue = center.getCards().hand[center.getCards().hand.size()-1].value;
		for (int i = center.getCards().size()-2; i >=0; i--)
			{
				if (center.getCards().hand[i].value == topValue)
				cardAmount++;
				else
				break;
			}
		if(selected.size() >= cardAmount)
		{
			return true;
		}
		else
			return false;
	}
	else
		return true;
}