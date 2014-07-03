#pragma once
#include "rule.h"
class ValueComparison
{
public:
	ValueComparison(COMPARISON_TYPE type,COMPARISON_TARGET target);
	ValueComparison(int minFrom, int maxFrom, int minTo, int maxTo, COMPARISON_TYPE type,COMPARISON_TARGET target);
	ValueComparison(){}
	~ValueComparison(void);
	bool check(Hand selectedCards,Hand targetCards);
	COMPARISON_TYPE _type;
	COMPARISON_TARGET _target;
	sf::Uint16 _minFrom,_maxFrom, _minTo, _maxTo;
private:
	bool smaller(Hand selectedCards,Hand targetCards);
	bool bigger(Hand selectedCards,Hand targetCards);
	bool same(Hand selectedCards,Hand targetCards);
	bool smallerOrSame(Hand selectedCards,Hand targetCards);
	bool biggerOrSame(Hand selectedCards,Hand targetCards);
	bool checkFromRange(Hand selectedCards, Hand targetCards);
	bool checkToRange(Hand selectedCards, Hand targetCards);
};	