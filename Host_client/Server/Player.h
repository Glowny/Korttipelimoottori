#pragma once
#include "PlayArea.h"
#include <vector>
#include <string>

class Player : public PlayArea
{
public:
	Player(std::string i):id(i){}
	std::string getID(){return id;}
	~Player(void);

private:
	std::string id;
};