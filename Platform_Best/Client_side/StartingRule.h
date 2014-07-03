#pragma once
#include <time.h>
#include "Rule.h"
#include "Player.h"

class StartingRule
{
public:
	int choosePlayer(std::vector<Player> players);
	StartingRule(Card card);
	StartingRule();
	~StartingRule(void);
private:
	Card _specifiedCard;
};

