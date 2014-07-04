#pragma once
#include "Hand.h"

enum COMPARISON_TYPE{
	EMPTY = -1,
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
	TABLE_VALUE,
};

enum EXCEPTION_OUTCOME{
	NOTHING,
	CLEAR_TABLE,
	DRAW_TABLE,
	ADD_TO_TABLE,
};

enum BASICRULE_TYPE{
	DRAW_TO,
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