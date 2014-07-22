#pragma once
#include <string>
#include <fstream>
#include <iostream>
class Deck
{
public:
	Deck(){}
	Deck(std::string file,int amount,int sizex,int sizey);
	~Deck(void);
	void writeToFile(std::fstream &stream);
	void readFromFile(std::fstream &stream);
	std::string getName(){return filename;}
private:
	std::string filename;
	int cardAmount,sizeX,sizeY,stringSize;
};

