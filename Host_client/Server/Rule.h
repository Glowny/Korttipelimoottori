#pragma once
#include "Hand.h"

enum COMPARISON_TYPE{
	ANY,
	SMALLER,
	BIGGER,
	SAME,
	SMALLER_SAME,
	BIGGER_SAME,
};

enum COMPARISON_TARGET{
	OWN,
	OWN_TO_TABLE
};

enum EXCEPTION_TYPE{
	EMPTY_PLAY,
	SPECIFIED_CARD,
};

enum EXCEPTION_OUTCOME{
	NOTHING,
	CLEAR_TABLE,
	DRAW_TABLE,
};

enum BASICRULE_TYPE{
	DRAW_TO_5,
};

enum BASICRULE_TRIGGER{
	EACH_TURN,
};


class Rule
{


public:
	Rule(void);
	virtual ~Rule(void);
	virtual bool check(Hand selectedCards, Hand tableCards) = 0;
};