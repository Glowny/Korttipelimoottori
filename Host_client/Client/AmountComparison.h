#pragma once
#include "rule.h"
class AmountComparison
{
public:
	AmountComparison(COMPARISON_TYPE type);
	AmountComparison(int min, int max, COMPARISON_TYPE type);
	AmountComparison(int min, int max, COMPARISON_TYPE type, COMPARISON_TYPE exception, COMPARISON_TYPE outcome);
	AmountComparison(){};
	~AmountComparison();
	bool check(Hand selectedCards,Hand targetCards);
	COMPARISON_TYPE _type, _exception, _outcome;
	sf::Uint16 _min, _max;
private:
	bool smaller(Hand selectedCards,Hand targetCards);
	bool bigger(Hand selectedCards,Hand targetCards);
	bool same(Hand selectedCards,Hand targetCards);
	bool smallerOrSame(Hand selectedCards,Hand targetCards);
	bool biggerOrSame(Hand selectedCards,Hand targetCards);
	bool checkRange(Hand selectedCards);
	bool checkException(Hand selectedCards, Hand targetCards);
};