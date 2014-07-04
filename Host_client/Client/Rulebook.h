#pragma once
#include "AmountComparison.h"
#include "ValueComparison.h"
#include <fstream>
#include <vector>
class Rulebook
{
public:
	Rulebook(void);
	~Rulebook(void);
	bool checkRules(Hand selectedCards, Hand targetCards);
	void push_back(AmountComparison rule);
	void push_back(ValueComparison rule);
	void writeToFile(std::string name);
	void readFromFile(std::string name);
private:	
	std::vector<ValueComparison> _valueRules;
	std::vector<AmountComparison> _amountRules;
};