#include "AmountComparison.h"


AmountComparison::AmountComparison(COMPARISON_TYPE type)
{
	_type = type;
	_exception = EMPTY;
	_outcome = EMPTY;
	_min = 0;
	_max = 0;
}

AmountComparison::AmountComparison(int min, int max, COMPARISON_TYPE type)
{
	_min = min;
	_max = max;
	_type = type;
	_exception = EMPTY;
	_outcome = EMPTY;
}

AmountComparison::AmountComparison(int min, int max, COMPARISON_TYPE type, COMPARISON_TYPE exception, COMPARISON_TYPE outcome)
{
	_min = min;
	_max = max;
	_type = type;
	_exception = exception;
	_outcome = outcome;
}

AmountComparison::~AmountComparison(void)
{
}

bool AmountComparison::smaller(Hand selectedCards, Hand targetCards)
{
	if(selectedCards.size()<targetCards.size())
		return true;
	return false;
}


bool AmountComparison::bigger(Hand selectedCards,Hand targetCards)
{
	if(selectedCards.size()>targetCards.size())
		return true;
	return false;
}

bool AmountComparison::same(Hand selectedCards, Hand targetCards)
{
	if(selectedCards.size()==targetCards.size())
		return true;
	return false;
}

bool AmountComparison::smallerOrSame(Hand selectedCards, Hand targetCards)
{
	if(selectedCards.size()<=targetCards.size())
		return true;
	return false;
}

bool AmountComparison::biggerOrSame(Hand selectedCards, Hand targetCards)
{
	if(selectedCards.size()>=targetCards.size())
		return true;
	return false;
}

bool AmountComparison::checkRange(Hand selectedCards)
{
	bool onRange = true;

	for(int i = 0; i < selectedCards.size(); i++)
	{
		if( !(selectedCards.hand[i].value >= _min && selectedCards.hand[i].value <= _max) )
			onRange = false;
	}

	return onRange;
}

bool AmountComparison::checkException(Hand selectedCards, Hand targetCards)
{
	bool exception = true;
	if(targetCards.size() > 0)
	{
		switch(_exception)
		{
			case SAME:
				if(selectedCards.hand[0].value != targetCards.hand[0].value)
					exception = false;
				break;
		}
	}
	return exception;
}

bool AmountComparison::check(Hand selectedCards, Hand targetCards)
{
	bool passed = false, onRange = true;
	COMPARISON_TYPE tempType = _type;

	if(_min != 0)
		onRange = checkRange(selectedCards);

	if(onRange)
	{
		if(_exception != EMPTY)
		{
			if(checkException(selectedCards, targetCards))
				tempType = _outcome;
		}

		switch(tempType)
		{
			case ANY:
				return true;
				break;

			case SAME:
				passed = same(selectedCards, targetCards);
				break;

			case SMALLER:
				passed = smaller(selectedCards,targetCards);
				break;

			case BIGGER:
				passed = bigger(selectedCards, targetCards);
				break;

			case SMALLER_SAME:
				passed = smallerOrSame(selectedCards,targetCards);
				break;

			case BIGGER_SAME:
				passed = biggerOrSame(selectedCards,targetCards);
				break;

		};
		return passed;
	}
	return true;
}