#include "AmountComparison.h"


AmountComparison::AmountComparison(COMPARISON_TYPE type)
{
	_type = type;
}


AmountComparison::~AmountComparison(void)
{
}

bool AmountComparison::smaller(Hand selectedCards, Hand tableCards)
{
	if(selectedCards.size()<tableCards.size())
		return true;
	return false;
}


bool AmountComparison::bigger(Hand tableCards,Hand seletectedCards)
{
	return true;
}

bool AmountComparison::same(Hand selectedCards, Hand tableCards)
{
	return true;
}

bool AmountComparison::smallerOrSame(Hand selectedCards, Hand tableCards)
{
	if(selectedCards.size()<=tableCards.size())
		return true;
	return false;
}

bool AmountComparison::biggerOrSame(Hand selectedCards, Hand tableCards)
{
	if(selectedCards.size()>=tableCards.size())
		return true;
	return false;
}

bool AmountComparison::check(Hand selectedCards, Hand tableCards)
{
	bool passed = false;

	switch(_type)
	{
		case SAME:
			break;
		case SMALLER:
			passed = smaller(selectedCards,tableCards);
			break;

		case BIGGER:
			break;
		case SMALLER_SAME:
			passed = smallerOrSame(selectedCards,tableCards);
			break;
		case BIGGER_SAME:
			passed = biggerOrSame(selectedCards,tableCards);
			break;

	};

	return passed;

}