#pragma once
#include "Rule.h"
#include "AmountComparison.h"
#include "ValueComparison.h"
#include "ExceptionalRule.h"
#include "StartingRule.h"
#include "Player.h"
#include <fstream>
#include <vector>
class Rulebook
{
public:
	Rulebook(void);
	~Rulebook(void);
	bool checkRules(Hand selectedCards, Hand targetCards);
	EXCEPTION_OUTCOME checkExceptionRules(Hand playedCards);
	int init(std::vector<Player> players);
	void push_back(AmountComparison rule);
	void push_back(ValueComparison rule);
	void push_back(ExceptionalRule rule);
	void push_back(StartingRule rule);
	void writeToFile(std::string name);
	void readFromFile(std::string name);
private:	
	std::vector<ValueComparison> _valueRules;
	std::vector<AmountComparison> _amountRules;
	std::vector<ExceptionalRule> _exceptionRules;
	StartingRule _startingRule;
};