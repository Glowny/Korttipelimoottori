#pragma once
#include "PlayArea.h"
#include <vector>
#include <string>

class Player : public PlayArea
{

	friend bool operator ==(Player &a, Player &b)
	{
		if(a.getID() == b.getID())
			return true;
		return false;
	}

public:
	Player();
	Player(std::string i):id(i){}
	std::string getID(){return id;}
	~Player(void);

private:
	std::string id;
};