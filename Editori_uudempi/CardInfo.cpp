#include "CardInfo.h"


CardInfo::CardInfo(std::string name, float cardWidth,float cardHeight, int cardAmount, int cards[]):_name(name),_cardWidth(cardWidth),_cardHeight(cardHeight),_cardAmount(cardAmount)
{
	for (int i = 0; i < _cardAmount; i++)
	{
		_cards[i] = cards[i];
	}
}
CardInfo::CardInfo(std::string filename)
{
	
	_name = filename+=".dat";
	std::ifstream inputFile(_name, std::ios::binary|std::ios::in);
	if(inputFile)
	{
		inputFile.read(( char*) &_cardWidth, sizeof(int));
		inputFile.read(( char*) &_cardHeight, sizeof(int));
		inputFile.read(( char*) &_cardAmount, sizeof(int));
		for (int i = 0; i < _cardAmount; i++)
		{
			inputFile.read((char*) &_cards[i], sizeof(int)); 
		}
	}
}


CardInfo::~CardInfo(void)
{
}
std::string CardInfo::getName()
{
	return _name;
}
int CardInfo::getCardAmount()
{
return _cardAmount;
}
int* CardInfo::getCards()
{
	return _cards;
}
void CardInfo::save()
{	
	std::string filename = _name+=".dat";
	/*filename.push_back('.');
	filename.push_back('d');
	filename.push_back('a');
	filename.push_back('t');*/
	std::ofstream outputFile(filename, std::ios::binary|std::ios::out);
	if (outputFile)
	{
		outputFile.write((char*)_cardWidth, sizeof(int));
		outputFile.write((char*)_cardHeight, sizeof(int));
		outputFile.write((char*)_cardAmount, sizeof(int));
		for (int i = 0; i < _cardAmount; i++)
		{
			outputFile.write((char *) &_cards[i], sizeof(int));
		}
		outputFile.close();
	}
}