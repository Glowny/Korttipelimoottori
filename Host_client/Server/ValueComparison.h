#pragma once
#include "rule.h"
class ValueComparison
{
public:
	ValueComparison(COMPARISON_TYPE type,COMPARISON_TARGET target);
	ValueComparison(){}
	~ValueComparison(void);
	bool check(Hand selectedCards,Hand targetCards);
	COMPARISON_TYPE _type;
	COMPARISON_TARGET _target;
private:
	bool smaller(Hand selectedCards,Hand targetCards);
	bool bigger(Hand selectedCards,Hand targetCards);
	bool same(Hand selectedCards,Hand targetCards);
	bool smallerOrSame(Hand selectedCards,Hand targetCards);
	bool biggerOrSame(Hand selectedCards,Hand targetCards);
	
	
};	
