#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
class Deck
{
public:
	Deck(){}
	Deck(std::string file,int amount,int sizex,int sizey);
	~Deck(void);
	void writeToFile(std::fstream &stream);
	void readFromFile(std::fstream &stream);
	std::string getName(){return filename;}
	int getCardAmount(){return cardAmount;}
	int getSizeX(){return sizeX;}
	int getSizeY(){return sizeY;}
	std::string toString();
private:
	std::string filename;
	int cardAmount,sizeX,sizeY,stringSize;
	std::string convertInt(int number);
};

