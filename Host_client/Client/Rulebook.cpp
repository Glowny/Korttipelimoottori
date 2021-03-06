#include "Rulebook.h"


Rulebook::Rulebook(void)
{
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

void Rulebook::writeToFile(std::string name)
{

	std::fstream outputFile(name,std::ios::binary|std::ios::out|std::ifstream::trunc);
	if(outputFile)
	{

	int valueSize = _valueRules.size();
	outputFile.write((char*)&valueSize,sizeof(int));
	for(int i = 0;i < _valueRules.size();i++)
	{
		outputFile.write((char*)&_valueRules[i],sizeof(ValueComparison));
	}

	int amountSize = _amountRules.size();
	outputFile.write((char*)&amountSize,sizeof(int));
	for(int i = 0; i < _amountRules.size();i++)
	{
		outputFile.write((char*)&_amountRules[i],sizeof(AmountComparison));
	}

	outputFile.close();
	}
}

void Rulebook::readFromFile(std::string name)
{
	std::fstream inputFile(name,std::ios::binary|std::ios::in|std::ios::out);

	if(inputFile)
	{

	while(inputFile.peek() != EOF)
	{

	int valueSize;
	inputFile.read((char*)&valueSize,sizeof(int));

	for(int i = 0;i < valueSize;i++)
	{
		ValueComparison vc;
		inputFile.read((char*)&vc,sizeof(ValueComparison));
		_valueRules.push_back(vc);
	}

	int amountSize;
	inputFile.read((char*)&amountSize,sizeof(int));

	for(int i = 0; i < amountSize;i++)
	{
		AmountComparison ac;
		inputFile.read((char*)&ac,sizeof(AmountComparison));
		_amountRules.push_back(ac);
	}

	inputFile.close();
	}
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

Rulebook::~Rulebook(void)
{
}