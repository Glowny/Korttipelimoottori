#include "Deck.h"


Deck::Deck(std::string file,int amount,int sizex,int sizey)
{
	filename = file;
	cardAmount = amount;
	sizeX = sizex;
	sizeY = sizey;
	stringSize = file.size();
}

void Deck::writeToFile(std::fstream &stream)
{
	stream.write((char*)&stringSize,sizeof(int));
	for(int i = 0; i < stringSize;i++)
	{
		char temp;
		temp = filename[i];
		stream.write(&temp,1);
	}
	stream.write((char*)&cardAmount,sizeof(int));
	stream.write((char*)&sizeX,sizeof(int));
	stream.write((char*)&sizeY,sizeof(int));
}

std::string Deck::toString()
{
	std::string temp;

	temp+=filename;
	temp+="A:";
	temp+=convertInt(cardAmount);
	temp+="X:";
	temp+=convertInt(sizeX);
	temp+="Y:";
	temp+=convertInt(sizeY);

	return temp;
}


std::string Deck::convertInt(int number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}


void Deck::readFromFile(std::fstream &stream)
{
	stream.read((char*)&stringSize,sizeof(int));
	for(int i = 0; i < stringSize;i++)
	{
		char temp;
		stream.read(&temp,1);
		filename.push_back(temp);
	}
	stream.read((char*)&cardAmount,sizeof(int));
	stream.read((char*)&sizeX,sizeof(int));
	stream.read((char*)&sizeY,sizeof(int));

	std::cout<<std::endl<<"Read: "<<filename<<" "<<cardAmount<<" "<<sizeX<<" "<<sizeY<<std::endl;
}

Deck::~Deck(void)
{
}
