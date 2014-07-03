#include "ExceptionalRule.h"



ExceptionalRule::~ExceptionalRule(void)
{
}

EXCEPTION_OUTCOME ExceptionalRule::check(Hand playedCards)
{
	switch(_type)
	{
	case EMPTY_PLAY:
		if(playedCards.size() == 0)
			return _outcome;
		break;
	case SPECIFIED_CARD:
		for(int i = 0; i < playedCards.size(); i++)
		{
			if(_specifiedCard == playedCards.hand[i])
				return _outcome;
		}
		break;
	}
	return NOTHING;
}