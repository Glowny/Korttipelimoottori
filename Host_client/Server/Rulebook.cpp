#include "Rulebook.h"


Rulebook::Rulebook(void)
{
}

int Rulebook::init(std::vector<Player> players)
{
	int index = _startingRule.choosePlayer(players);
	return index;
}

bool Rulebook::checkRules(Hand selectedCards, Hand targetCards)
{
	if(selectedCards.size() != 0)
	{
		for(int i = 0; i < _amountRules.size();i++)
		{
			if(!_amountRules[i].check(selectedCards,targetCards))
				return false;
		}

		for(int i = 0; i < _valueRules.size();i++)
		{
			if(!_valueRules[i].check(selectedCards,targetCards))
				return false;
		}
	}

	return true;

}

EXCEPTION_OUTCOME Rulebook::checkExceptionRules(Hand playedCards)
{
	for(int i = 0;  i < _exceptionRules.size(); i++)
	{
		if(_exceptionRules[i].check(playedCards) != NOTHING)
			return _exceptionRules[i].check(playedCards);
	}
	return NOTHING;
}

void Rulebook::writeToFile(std::string name)
{

	std::fstream outputFile(name,std::ios::binary|std::ios::out|std::ifstream::trunc);

	for(int i = 0;i < _valueRules.size();i++)
	{
		_valueTable[i] = _valueRules[i];
	}
	for(int i = 0; i < _amountRules.size();i++)
	{
		_amountTable[i]= _amountRules[i];
	}
	for(int i = 0; i < _exceptionRules.size();i++)
	{
		_exceptionTable[i]= _exceptionRules[i];
	}

	if(outputFile)
	{
		
		outputFile.write((char*)&_valueTable,sizeof(_valueTable));
		outputFile.write((char*)&_amountTable,sizeof(_amountTable));
		outputFile.write((char*)&_exceptionTable, sizeof(_exceptionTable));
		outputFile.write((char*)&_startingRule,sizeof(_startingRule));

		outputFile.close();
	}
	_valueRules.clear();
	_amountRules.clear();
	_exceptionRules.clear();
	_startingRule = StartingRule();

}

void Rulebook::readFromFile(std::string name)
{
	std::fstream inputFile(name,std::ios::binary|std::ios::in|std::ios::out);

	if(inputFile)
	{

		while(inputFile.peek() != EOF)
		{
		inputFile.read((char*)&_valueTable,sizeof(_valueTable));
		inputFile.read((char*)&_amountTable,sizeof(_amountTable));
		inputFile.read((char*)&_exceptionTable, sizeof(_exceptionTable));
		inputFile.read((char*)&_startingRule,sizeof(_startingRule));
		
		}

		
		for(int i = 0; i < 100;i++)
		{
			if(_valueTable[i]._type != EMPTY_COMPARISON)
			_valueRules.push_back(_valueTable[i]);
		}
		for(int i = 0; i < 100;i++)
		{
			if(_amountTable[i]._type != EMPTY_COMPARISON)
				_amountRules.push_back(_amountTable[i]);
		}
		for(int i = 0; i < 100;i++)
		{
			if(_exceptionTable[i]._type != EMPTY_EXCEPTION)
				_exceptionRules.push_back(_exceptionTable[i]);
		}


		inputFile.close();
	}

}

void Rulebook::push_back(AmountComparison rule)
{
	_amountRules.push_back(rule);
}

void Rulebook::push_back(ValueComparison rule)
{
	_valueRules.push_back(rule);
}

void Rulebook::push_back(ExceptionalRule rule)
{
	_exceptionRules.push_back(rule);
}

void Rulebook::push_back(StartingRule rule)
{
	_startingRule = rule;
}

Rulebook::~Rulebook(void)
{
}