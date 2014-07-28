#include "CardInfo.h"


CardInfo::CardInfo(std::string name, float cardWidth,float cardHeight, int cardAmount, int cards[]):_name(name),_cardWidth(cardWidth),_cardHeight(cardHeight),_cardAmount(cardAmount)
{
	_cards = new int[_cardAmount];
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
		_cards = new int[_cardAmount];
		for (int i = 0; i < _cardAmount; i++)
		{
			inputFile.read((char*) &_cards[i], sizeof(int)); 
		}
	}
	print(); // temp
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
void CardInfo::print()
{
	std::cout << "Card width:" << _cardWidth << "| Card height:" << _cardHeight << "| Different cards:" << _cardAmount << std::endl;
	std::cout << "| Cards and amount of them: " << std::endl;
	for (int i = 0; i <_cardAmount; i++)
	{
		std::cout<< i << ":" << _cards[i] << "| |"; 
	}
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
	int toIntW = _cardWidth;
	int toIntH = _cardHeight;
	std::ofstream outputFile(filename, std::ios::binary|std::ios::out);
	if (outputFile)
	{
		outputFile.write((char*)&toIntW, sizeof(int));
		outputFile.write((char*)&toIntH, sizeof(int));
		outputFile.write((char*)&_cardAmount, sizeof(int));
		for (int i = 0; i < _cardAmount; i++)
		{
			outputFile.write((char *) &_cards[i], sizeof(int));
		}
		outputFile.close();
	}
}