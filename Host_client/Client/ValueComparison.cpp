#include "ValueComparison.h"


ValueComparison::ValueComparison(COMPARISON_TYPE type, COMPARISON_TARGET target)
{
	_type = type;
	_target = target;

}


ValueComparison::~ValueComparison(void)
{
}

bool ValueComparison::smaller(Hand selectedCards,Hand targetCards)
{

	for(int i = 0; i < selectedCards.size(); i++)
	{
		if(targetCards.size()!=0) //Täytyy ehkä tehdä sääntö liittyen tyhjään pöytään/alottavaan pelaajaan
		{
			for(int j = 0;j < targetCards.size();j++)
			{
				if(selectedCards.hand[i].value >= targetCards.hand[j].value)
				return false;
			}
		}
	}
	return true;
}


bool ValueComparison::bigger(Hand selectedCards,Hand targetCards)
{
	return true;
}

bool ValueComparison::same(Hand selectedCards,Hand targetCards)
{
	for(int i = 0; i < selectedCards.size(); i++)
	{
		if(targetCards.size()!=0) //Täytyy ehkä tehdä sääntö liittyen tyhjään pöytään/alottavaan pelaajaan
		{
			for(int j = 0;j < targetCards.size();j++)
			{
				if(selectedCards.hand[i].value != targetCards.hand[j].value)
				return false;
			}
		}
	}
	return true;
}

bool ValueComparison::smallerOrSame(Hand selectedCards,Hand targetCards)
{
	return true;
}

bool ValueComparison::biggerOrSame(Hand selectedCards,Hand targetCards)
{
	return true;
}

bool ValueComparison::check(Hand selectedCards,Hand targetCards)
{
	bool passed = false;

	switch(_type)
	{
		case SAME:
			if(_target == OWN)
			{
				passed = same(selectedCards,selectedCards);
			}
			break;
		case SMALLER:
			if(_target == OWN_TO_TABLE)
			passed = smaller(selectedCards,targetCards);

			break;
		case BIGGER:
			break;
		case SMALLER_SAME:
			break;
		case BIGGER_SAME:
			break;

	};

	return passed;

}