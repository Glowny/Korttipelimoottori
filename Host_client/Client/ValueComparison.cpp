#include "ValueComparison.h"


ValueComparison::ValueComparison(COMPARISON_TYPE type, COMPARISON_TARGET target)
{
	_type = type;
	_target = target;
	_minFrom = 0;
	_maxFrom = 0;
	_minTo = 0;
	_maxTo = 0;
}

ValueComparison::ValueComparison(int minFrom, int maxFrom, int minTo, int maxTo, COMPARISON_TYPE type,COMPARISON_TARGET target)
{
	_minFrom = minFrom;
	_maxFrom = maxFrom;
	_minTo = minTo;
	_maxTo = maxTo;
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
	for(int i = 0; i < selectedCards.size(); i++)
	{
		if(targetCards.size()!=0) //Täytyy ehkä tehdä sääntö liittyen tyhjään pöytään/alottavaan pelaajaan
		{
			for(int j = 0;j < targetCards.size();j++)
			{
				if(selectedCards.hand[i].value <= targetCards.hand[j].value)
				return false;
			}
		}
	}
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
	for(int i = 0; i < selectedCards.size(); i++)
	{
		if(targetCards.size()!=0) //Täytyy ehkä tehdä sääntö liittyen tyhjään pöytään/alottavaan pelaajaan
		{
			for(int j = 0;j < targetCards.size();j++)
			{
				if(selectedCards.hand[i].value > targetCards.hand[j].value)
				return false;
			}
		}
	}
	return true;
}

bool ValueComparison::biggerOrSame(Hand selectedCards,Hand targetCards)
{
	for(int i = 0; i < selectedCards.size(); i++)
	{
		if(targetCards.size()!=0) //Täytyy ehkä tehdä sääntö liittyen tyhjään pöytään/alottavaan pelaajaan
		{
			for(int j = 0;j < targetCards.size();j++)
			{
				if(selectedCards.hand[i].value < targetCards.hand[j].value)
					return false;
			}
		}
	}
	return true;
}

bool ValueComparison::checkFromRange(Hand selectedCards)
{	
	bool onRange = true;
	
	for(int i = 0; i < selectedCards.size(); i++)
	{
		if( !(selectedCards.hand[i].value >= _minFrom && selectedCards.hand[i].value <= _maxFrom) )
			onRange = false;
	}

	return onRange;
}

bool ValueComparison::checkToRange(Hand targetCards)
{
	bool onRange = true;

	for(int i = 0; i < targetCards.size(); i++)
	{
		if( !(targetCards.hand[i].value >= _minTo && targetCards.hand[i].value <= _maxTo) )
			onRange = false;
	}

	return onRange;
}

bool ValueComparison::check(Hand selectedCards,Hand targetCards)
{
	bool passed = false, onFromRange = true, onToRange = true;

	if(_minFrom != 0)
		onFromRange = checkFromRange(selectedCards);

	if(onFromRange)
	{
		if(_minTo != 0)
			onToRange = checkToRange(targetCards);

		if(onToRange)
		{
			switch(_type)
			{
				case ANY:
					passed = true;
					break;
				case SAME:
					if(_target == OWN)
						passed = same(selectedCards,selectedCards);
					else if(_target == OWN_TO_TABLE)
						passed = same(selectedCards, targetCards);
					break;
				case SMALLER:
					if(_target == OWN)
						passed = smaller(selectedCards, selectedCards);
					else if(_target == OWN_TO_TABLE)
						passed = smaller(selectedCards,targetCards);
					break;
				case BIGGER:
					if(_target == OWN)
						passed = bigger(selectedCards, selectedCards);
					else if(_target == OWN_TO_TABLE)
						passed = bigger(selectedCards,targetCards);
					break;
				case SMALLER_SAME:
					if(_target == OWN)
						passed = smallerOrSame(selectedCards, selectedCards);
					else if(_target == OWN_TO_TABLE)
						passed = smallerOrSame(selectedCards,targetCards);
					break;
				case BIGGER_SAME:
					if(_target == OWN)
						passed = biggerOrSame(selectedCards, selectedCards);
					else if(_target == OWN_TO_TABLE)
						passed = biggerOrSame(selectedCards,targetCards);
					break;

			};
			return passed;
		}
		return false;
	}
	return true;
}