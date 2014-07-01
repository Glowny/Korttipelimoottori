#pragma once
#include "rule.h"
class AmountComparison
{
public:
	AmountComparison(COMPARISON_TYPE type);
	AmountComparison(){_type = EMPTY_COMPARISON;};
	~AmountComparison();
	bool check(Hand selectedCards,Hand tableCards);
	COMPARISON_TYPE _type;
private:
	bool smaller(Hand selectedCards,Hand tableCards);
	bool bigger(Hand selectedCards,Hand tableCards);
	bool same(Hand selectedCards,Hand tableCards);
	bool smallerOrSame(Hand selectedCards,Hand tableCards);
	bool biggerOrSame(Hand selectedCards,Hand tableCards);
	

};

