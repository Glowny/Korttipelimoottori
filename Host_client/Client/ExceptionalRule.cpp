#include "ExceptionalRule.h"



ExceptionalRule::~ExceptionalRule(void)
{
}

EXCEPTION_OUTCOME ExceptionalRule::check(Hand selectedCards)
{
	switch(_type)
	{
	case EMPTY_PLAY:
		if(selectedCards.size() == 0)
			return _outcome;
		break;
	case SPECIFIED_CARD:
		for(int i = 0; i < selectedCards.size(); i++)
		{
			if(_specifiedCard == selectedCards.hand[i])
				return _outcome;
		}
		break;
	default:
		return NOTHING;
		break;
	}
}