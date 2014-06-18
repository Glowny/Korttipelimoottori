#pragma once
#include "Hand.h"
class Permits
{
public:
	Permits(void);
	~Permits(void);

private:
	
	std::vector<Hand> _hands;
};