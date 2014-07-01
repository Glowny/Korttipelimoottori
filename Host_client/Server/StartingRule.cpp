#include "StartingRule.h"


StartingRule::StartingRule(void)
{
	srand(time(NULL));
}

StartingRule::StartingRule(Card card)
{
	srand(time(NULL));
	_specifiedCard = card;
}

int StartingRule::choosePlayer(std::vector<Player> players)
{
	if(_specifiedCard.suit != NULL)
	{
		for(int i = 0; i < players.size();i++)
		{
			for(int j = 0; j < players[i].getHand().size();j++)
			{
				if(players[i].getHand().hand[j]==_specifiedCard)
				{
					return i;
				}
			}
		}
	}
	int size = std::rand()%players.size();
	return size;
}

StartingRule::~StartingRule(void)
{
}
